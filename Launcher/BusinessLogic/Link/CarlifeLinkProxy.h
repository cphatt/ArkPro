#ifndef CARLIFELINKPROXY_H_1502069718
#define CARLIFELINKPROXY_H_1502069718

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface Local.DbusServer.AndroidCarlife
 */
class LocalDbusServerAndroidCarlifeInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "Local.DbusServer.Carlife"; }

public:
    LocalDbusServerAndroidCarlifeInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~LocalDbusServerAndroidCarlifeInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<> onExitSignal()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QLatin1String("onExitSignal"), argumentList);
    }

    inline QDBusPendingReply<> requestKeyValue(int type)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type);
        return asyncCallWithArgumentList(QLatin1String("requestKeyValue"), argumentList);
    }

    inline QDBusPendingReply<> requestLinkStatus(int type, int status)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(type) << qVariantFromValue(status);
        return asyncCallWithArgumentList(QLatin1String("requestLinkStatus"), argumentList);
    }

    inline QDBusPendingReply<> requestTouchStatus(int deviceType, int touchType, const QString &touchPointXml)
    {
        QList<QVariant> argumentList;
        argumentList << qVariantFromValue(deviceType) << qVariantFromValue(touchType) << qVariantFromValue(touchPointXml);
        return asyncCallWithArgumentList(QLatin1String("requestTouchStatus"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void onLinkStatusChange(int type, int status);
};

namespace Local {
  namespace DbusServer {
    typedef ::LocalDbusServerAndroidCarlifeInterface Carlife;
  }
}
#endif
