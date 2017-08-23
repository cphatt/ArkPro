#include "DbusService.h"
#include <QDebug>
#include <QDBusServiceWatcher>
#include <QDBusReply>
#include <QDBusConnection>
#include <QDBusConnectionInterface>

class DbusServicePrivate
{
public:
    explicit DbusServicePrivate(DbusService* parent);
    ~DbusServicePrivate();
    void initialize();
    void connectAllSlots();
    QDBusServiceWatcher* m_DBusServiceWatcher;
private:
    DbusService* m_Parent;
};

bool DbusService::startService(const QString &service)
{
    bool flag(false);
    QDBusReply<void> reply = QDBusConnection::sessionBus().interface()->startService(service);
    if (!reply.isValid()) {
        qCritical() << "DbusService::startService:Error" << reply.error().message();
    } else {
        flag = true;
        m_Private->m_DBusServiceWatcher->addWatchedService(service);
        qDebug() << "DbusService::startService" << service << "success!";
    }
    return flag;
}

void DbusService::addWatchedService(const QString &service)
{
    m_Private->m_DBusServiceWatcher->addWatchedService(service);
}

bool DbusService::removeWatchedService(const QString &service)
{
    return m_Private->m_DBusServiceWatcher->removeWatchedService(service);
}

DbusService::DbusService(QObject *parent)
    : QObject(parent)
    , m_Private(new DbusServicePrivate(this))
{
}

DbusService::~DbusService()
{
}

DbusServicePrivate::DbusServicePrivate(DbusService *parent)
    : m_Parent(parent)
{
    m_DBusServiceWatcher = NULL;
    initialize();
    connectAllSlots();
}

DbusServicePrivate::~DbusServicePrivate()
{
}

void DbusServicePrivate::initialize()
{
    m_DBusServiceWatcher = new QDBusServiceWatcher(m_Parent);
    m_DBusServiceWatcher->setConnection(QDBusConnection::sessionBus());
}

void DbusServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_DBusServiceWatcher, SIGNAL(serviceRegistered(const QString &)),
                     m_Parent,             SIGNAL(onServiceRegistered(const QString &)),
                     type);
    QObject::connect(m_DBusServiceWatcher, SIGNAL(serviceUnregistered(const QString &)),
                     m_Parent,             SIGNAL(onServiceUnregistered(const QString &)),
                     type);
}
