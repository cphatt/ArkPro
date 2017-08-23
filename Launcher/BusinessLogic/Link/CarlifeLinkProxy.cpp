#include "CarlifeLinkProxy.h"

/*
 * Implementation of interface class LocalDbusServerAndroidCarlifeInterface
 */

LocalDbusServerAndroidCarlifeInterface::LocalDbusServerAndroidCarlifeInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent)
    : QDBusAbstractInterface(service, path, staticInterfaceName(), connection, parent)
{
}

LocalDbusServerAndroidCarlifeInterface::~LocalDbusServerAndroidCarlifeInterface()
{
}

