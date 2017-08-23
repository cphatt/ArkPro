#include "Setting.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "BusinessLogic/Widget/Widget.h"
#include "EventEngine.h"
#include "ArkApplication.h"
#include "SettingService.h"
#include "SettingPersistent.h"
#include <QProcess>
#include <QTranslator>
#include <QDBusServiceWatcher>
#include <QDebug>

class SettingPrivate
{
    Q_DISABLE_COPY(SettingPrivate)
public:
    explicit SettingPrivate(Setting* parent);
    ~SettingPrivate();
    void initialize();
    void connectAllSlots();
    void receiveAllCustomEvent();
    void onLanguageChange(const LanguageType language);
    QTranslator* m_Translator;
    SettingService* m_SettingService;
    Local::DbusServer::Setting* m_SettingServiceProxy;
private:
    Setting* m_Parent;
};

void Setting::setLanguage(const LanguageType language)
{
    if (NULL != m_Private->m_SettingService) {
        m_Private->m_SettingService->setLanguage(language);
    } else if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setLanguage(language);
#ifdef gcc
        reply.waitForFinished();
        qDebug() << "Dbus call Setting::setLanguage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Setting::setLanguage failed" << reply.error();
        }
#endif
    }
}

void Setting::setBrightness(const SettingType type, const int value)
{
    if (NULL != m_Private->m_SettingService) {
        m_Private->m_SettingService->setBrightness(type, value);
    } else if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setBrightness(type, value);
#ifdef gcc
        reply.waitForFinished();
        qDebug() << "Dbus call Setting::setBrightness" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Setting::setBrightness failed" << reply.error();
        }
#endif
    }
}

void Setting::setContrast(const SettingType type, const int value)
{
    if (NULL != m_Private->m_SettingService) {
        m_Private->m_SettingService->setContrast(type, value);
    } else if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setContrast(type, value);
#ifdef gcc
        reply.waitForFinished();
        qDebug() << "Dbus call Setting::setContrast" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Setting::setContrast failed" << reply.error();
        }
#endif
    }
}

void Setting::setHue(const SettingType type, const int value)
{
    if (NULL != m_Private->m_SettingService) {
        m_Private->m_SettingService->setHue(type, value);
    } else if (NULL != m_Private->m_SettingServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->setHue(type, value);
#ifdef gcc
        reply.waitForFinished();
        qDebug() << "Dbus call Setting::setHue" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Setting::setHue failed" << reply.error();
        }
#endif
    }
}

void Setting::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetConstructor: {
        onLanguageChange(SettingPersistent::getLanguage());
        emit onDateTimeChange(QDateTime::currentDateTime().toString(QString("yyyy-MM-dd")), QDateTime::currentDateTime().toString(QString("hh:mm")));
        break;
    }
    case CustomEventType::MainWidgetShow: {
        g_EventEngine->detachCustomEvent(this);
#ifdef gcc
        int count(4);
#else
        int count(3);
#endif
        if (count == ArkApp->arguments().size()) {
            if (NULL == m_Private->m_SettingServiceProxy) {
                m_Private->m_SettingServiceProxy = new Local::DbusServer::Setting(ArkMicroSettingService,
                                                                                  ArkMicroSettingPath,
                                                                                  QDBusConnection::sessionBus(),
                                                                                  qApp);
                connectSignalAndSignalByNamesake(m_Private->m_SettingServiceProxy, this);
                Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
                QObject::connect(m_Private->m_SettingServiceProxy, SIGNAL(onLanguageChange(const int)),
                                 this,                             SLOT(onLanguageChange(const int)),
                                 type);
                connectSignalAndSlotByNamesake(g_DbusService, this);
                onServiceUnregistered(ArkMicroSettingService);
            }
        } else {
            if (NULL == m_Private->m_SettingService) {
                m_Private->m_SettingService = new SettingService(this);
                connectSignalAndSignalByNamesake(m_Private->m_SettingService, this);
                Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
                QObject::connect(m_Private->m_SettingService, SIGNAL(onLanguageChange(const int)),
                                 this,                        SLOT(onLanguageChange(const int)),
                                 type);
                onServiceRegistered(ArkMicroSettingService);
            }
        }
        break;
    }
    default: {
        break;
    }
    }
    QObject::customEvent(event);
}

void Setting::onLanguageChange(const LanguageType language)
{
    qDebug() << "onLanguageChange" << language;
    m_Private->onLanguageChange(language);
}

void Setting::onServiceRegistered(const QString &service)
{
    qDebug() << "Setting::onServiceRegistered" << service;
    if (ArkMicroSettingService == service) {
        if (NULL != m_Private->m_SettingService) {
            m_Private->m_SettingService->synchronize();
        } else if (NULL != m_Private->m_SettingServiceProxy) {
            QDBusPendingReply<> reply = m_Private->m_SettingServiceProxy->synchronize();
#ifdef gcc
            reply.waitForFinished();
            qDebug() << "Dbus call m_SettingServiceProxy synchronize" << reply.isFinished();
            if (reply.isError()) {
                qDebug() << "method call synchronize failed" << reply.error();
            }
#endif
        }
    }
}

void Setting::onServiceUnregistered(const QString &service)
{
    qDebug() << "Setting::onServiceUnregistered" << service;
    if (ArkMicroSettingService == service) {
//#ifdef gcc
        g_DbusService->addWatchedService(ArkMicroSettingService);
        QStringList cmd;
        cmd << QString("-t") << SettingApplication;
        bool ret = QProcess::startDetached(qApp->applicationFilePath(), cmd);
        qDebug() << "start" << ArkMicroSettingService << ret;
//#else
//        g_DbusService->startService(ArkMicroSettingService);
//#endif
    }
}

Setting::Setting(QObject *parent)
    : QObject(parent)
    , SettingService::Interface()
    , DbusService::Interface()
    , m_Private(new SettingPrivate(this))
{
}

Setting::~Setting()
{
}

SettingPrivate::SettingPrivate(Setting *parent)
    : m_Parent(parent)
{
    m_Translator = NULL;
    m_SettingService = NULL;
    m_SettingServiceProxy = NULL;
    initialize();
    receiveAllCustomEvent();
}

SettingPrivate::~SettingPrivate()
{
    qDebug() << "SettingPrivate::~SettingPrivate";
    system("kill  `ps -elf | grep Launcher | grep setting | awk '{print $4}'`");
}

void SettingPrivate::initialize()
{
    m_Translator = new QTranslator(m_Parent);
}

void SettingPrivate::connectAllSlots()
{
}

void SettingPrivate::receiveAllCustomEvent()
{
    qDebug() << "SettingPrivate::receiveAllCustomEvent";
    g_EventEngine->attachCustomEvent(m_Parent);
}

void SettingPrivate::onLanguageChange(const int language)
{
    if (!m_Translator->isEmpty()) {
        ArkApplication::removeTranslator(m_Translator);
    }
    QString languagePath;
    languagePath.clear();
    switch (language) {
    case LT_Chinese: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_CN.qm");
        break;
    }
    case LT_Japaness: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_JP.qm");
        break;
    }
    case LT_Korean: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_KO.qm");
        break;
    }
    case LT_Spanish: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_SP.qm");
        break;
    }
    case LT_Portuguese: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_PO.qm");
        break;
    }
    case LT_Russian: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_RU.qm");
        break;
    }
    case LT_German: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_DE.qm");
        break;
    }
    case LT_French: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_FR.qm");
        break;
    }
    case LT_English:
    default: {
        languagePath = QString(":/Language/Resources/Languages/Launcher_EN.qm");
        break;
    }
    }
    if (m_Translator->load(languagePath)) {
        ArkApplication::installTranslator(m_Translator);
        emit m_Parent->onLanguageTranslateChange(language);
    } else {
        qDebug() << "QTranslator load" << language << languagePath << "fail!";
    }
}
