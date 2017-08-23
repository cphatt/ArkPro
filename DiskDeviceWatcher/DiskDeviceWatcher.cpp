#include "DiskDeviceWatcher.h"
#include <QSocketNotifier>
#include <QDebug>
#include <QByteArray>
#include <QRegExp>
#include <QBuffer>
#include <QCoreApplication>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/types.h>
#include <linux/netlink.h>
#include <errno.h>
#include <unistd.h>

#define UEVENT_BUFFER_SIZE      2048
#define UDEV_MONITOR_KERNEL     1

class DiskDeviceWatcherPrivate
{
    Q_DISABLE_COPY(DiskDeviceWatcherPrivate)
public:
    explicit DiskDeviceWatcherPrivate(DiskDeviceWatcher* parent);
    ~DiskDeviceWatcherPrivate();
    void initialize();
    void parseLine(const QByteArray& line);
    QSocketNotifier *m_SocketNotifier;
    QBuffer m_Buffer;
    int m_NetLinkSocket;
private:
    DiskDeviceWatcher* m_Parent;
};

DiskDeviceWatcher::DiskDeviceWatcher(QObject *parent)
    : QObject(parent)
    , m_Private(new DiskDeviceWatcherPrivate(this))
{
}

DiskDeviceWatcher::~DiskDeviceWatcher()
{
}

void DiskDeviceWatcher::onSocketNotifier()
{
    QByteArray data;
    data.resize(UEVENT_BUFFER_SIZE * 2);
    data.fill(0);
    size_t len = read(m_Private->m_SocketNotifier->socket(), data.data(), UEVENT_BUFFER_SIZE * 2);
    data.resize(len);
    data = data.replace(0, '\n').trimmed(); //In the original line each information is seperated by 0
    if (m_Private->m_Buffer.isOpen()) {
        m_Private->m_Buffer.close();
    }
    m_Private->m_Buffer.setBuffer(&data);
    if (m_Private->m_Buffer.open(QIODevice::ReadOnly)) {
        //    while (!m_Private->buffer.atEnd()) {
        while(m_Private->m_Buffer.canReadLine()) { //buffer.canReadLine() always false?
            m_Private->parseLine(m_Private->m_Buffer.readLine().trimmed());
        }
        m_Private->m_Buffer.close();
    }
}

DiskDeviceWatcherPrivate::DiskDeviceWatcherPrivate(DiskDeviceWatcher *parent)
    : m_Parent(parent)
{
    m_NetLinkSocket = -1;
    initialize();
}

DiskDeviceWatcherPrivate::~DiskDeviceWatcherPrivate()
{
}

void DiskDeviceWatcherPrivate::initialize()
{
    struct sockaddr_nl snl;
    const int buffersize = 16 * 1024 * 1024;
    int retval;

    memset(&snl, 0x00, sizeof(struct sockaddr_nl));
    snl.nl_family = AF_NETLINK;
    snl.nl_pid = getpid();
    snl.nl_groups = UDEV_MONITOR_KERNEL;

    m_NetLinkSocket = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    //netlink_socket = socket(PF_NETLINK, SOCK_DGRAM|SOCK_CLOEXEC, NETLINK_KOBJECT_UEVENT); //SOCK_CLOEXEC may be not available
    if (-1 == m_NetLinkSocket) {
        qWarning("error getting socket: %s", strerror(errno));
        exit(EXIT_FAILURE);
    }

    /* set receive buffersize */
    setsockopt(m_NetLinkSocket, SOL_SOCKET, SO_RCVBUFFORCE, &buffersize, sizeof(buffersize));
    retval = bind(m_NetLinkSocket, (struct sockaddr*) &snl, sizeof(struct sockaddr_nl));
    if (retval < 0) {
        qWarning("bind failed: %s", strerror(errno));
        close(m_NetLinkSocket);
        m_NetLinkSocket = -1;
        exit(EXIT_FAILURE);
    } else if (retval == 0) {
        //from libudev-monitor.c
        struct sockaddr_nl _snl;
        socklen_t _addrlen;
        /*
         * get the address the kernel has assigned us
         * it is usually, but not necessarily the pid
         */
        _addrlen = sizeof(struct sockaddr_nl);
        retval = getsockname(m_NetLinkSocket, (struct sockaddr *)&_snl, &_addrlen);
        if (0 == retval) {
            snl.nl_pid = _snl.nl_pid;
        }
    }
    m_SocketNotifier = new QSocketNotifier(m_NetLinkSocket, QSocketNotifier::Read, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_SocketNotifier, SIGNAL(activated(int)),
                     m_Parent, SLOT(onSocketNotifier()),
                     type); //will always active
    m_SocketNotifier->setEnabled(true);
}

void DiskDeviceWatcherPrivate::parseLine(const QByteArray &line)
{
#define USE_REGEXP 1
#if USE_REGEXP
    QRegExp rx("(\\w+)(?:@/.*/block/.*/)(\\w+)\\W*");
    //QRegExp rx("(add|remove|change)@/.*/block/.*/(\\w+)\\W*");
    if (rx.indexIn(line) == -1)
        return;
    QString action_str = rx.cap(1).toLower();
    QString dev = "/dev/" + rx.cap(2);
#else
    if (!line.contains("/block/")) //hotplug
        return;
    QString action_str = line.left(line.indexOf('@')).toLower();
    QString dev = "/dev/" + line.right(line.length() - line.lastIndexOf('/') - 1);
#endif //USE_REGEXP
    qDebug() << "action_str" << action_str << dev;
    DiskDeviceWatcher::Action action;
    if (QString("add") == action_str) {
           action = DiskDeviceWatcher::A_Add;
    } else if (QString("remove") == action_str) {
        action = DiskDeviceWatcher::A_Remove;
    }
    emit m_Parent->diskDeviceChange(dev, action);
    //    QDeviceChangeEvent *event = 0;

    //    if (action_str==QLatin1String("add")) {
    //        emitDeviceAdded(dev);
    //        event = new QDeviceChangeEvent(QDeviceChangeEvent::Add, dev);
    //    } else if (action_str==QLatin1String("remove")) {
    //        emitDeviceRemoved(dev);
    //        event = new QDeviceChangeEvent(QDeviceChangeEvent::Remove, dev);
    //    } else if (action_str==QLatin1String("change")) {
    //        emitDeviceChanged(dev);
    //        event = new QDeviceChangeEvent(QDeviceChangeEvent::Change, dev);
    //    }

    //    zDebug("%s %s", qPrintable(action_str), qPrintable(dev));

    //    if (event != 0 && !event_receivers.isEmpty()) {
    //        foreach(QObject* obj, event_receivers) {
    //            QCoreApplication::postEvent(obj, event, Qt::HighEventPriority);
    //        }
    //    }
}
