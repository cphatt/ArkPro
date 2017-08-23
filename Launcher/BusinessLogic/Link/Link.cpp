#include "Link.h"
#include "BusinessLogic/Widget/Widget.h"
#include "MirrorLinkProxy.h"
#include "CarplayLinkProxy.h"
#include "CarlifeLinkProxy.h"
#include "Utility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "AudioService.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "RunnableThread.h"
#include "BusinessLogic/Audio/Audio.h"
#include <QDebug>

#define ArkMicroMirrorService         QString("com.arkmicro.mirror")
#define ArkMicroMirrorPath            QString("/com/arkmicro/mirror")
#define ArkMicroMirrorInterface       QString("Local.DbusServer.Mirror")
#define ArkMicroCarplayService        QString("com.arkmicro.carplay")
#define ArkMicroCarplayPath           QString("/com/arkmicro/carplay")
#define ArkMicroCarplayInterface      QString("Local.DbusServer.Carplay")
#define ArkMicroCarlifeService        QString("com.arkmicro.carlife")
#define ArkMicroCarlifePath           QString("/com/arkmicro/carlife")
#define ArkMicroCarlifeInterface      QString("Local.DbusServer.Carlife")

class LinkPrivate
{
public:
    explicit LinkPrivate(Link *parent);
    ~LinkPrivate();
    void initialize();
    void connectAllSlots();
    void linkExit(const AudioSource source);
    void requestMirrorHandler(const Link_STATUS status);
    void requestCarlifeHandler(const Link_STATUS status);
    void requestCarplayHandler(const Link_STATUS status);
    void mirrorSourceHandler(const Link_STATUS status);
    void carplaySourceHandler(const Link_STATUS status);
    void carlifeSourceHandler(const Link_STATUS status);

    HANDLER m_Callback;

    Local::DbusServer::Mirror* m_MirrorLinkProxy;
    Local::DbusServer::Carplay* m_CarplayLinkProxy;\
    Local::DbusServer::Carlife* m_CarlifeLinkProxy;
private:
    Link* m_Parent;
};

static void releaseMirrorSource(void* paramater)
{
    qDebug() << "releaseMirrorSource" << paramater;
    LinkPrivate* ptr = static_cast<LinkPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->linkExit(AS_Mirror);
    }
}

static void releaseCarplaySource(void* paramater)
{
    qDebug() << "releaseCarplaySource" << paramater;
    LinkPrivate* ptr = static_cast<LinkPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->linkExit(AS_Carplay);
    }
}

static void releaseCarlifeSource(void* paramater)
{
    qDebug() << "releaseCarlifeSource" << paramater;
    LinkPrivate* ptr = static_cast<LinkPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->linkExit(AS_Carlife);
    }
}

static void requestSourceCallback(void* parameter)
{
    qWarning() << "requestSourceCallback" << QThread::currentThread();
    int* ptr = (int*)parameter;
    if (NULL != ptr) {
        QDBusInterface interface(ArkMicroAudioService,
                                 ArkMicroAudioPath,
                                 ArkMicroAudioInterface,
                                 QDBusConnection::sessionBus());
        QDBusReply<void> reply = interface.call(ArkMicroAudioRequest, *ptr);
        if (reply.isValid()) {
            qWarning() << "requestSourceCallbakc::requestAudioSource ok!";
        } else {
            qWarning() << "requestSourceCallbakc::requestAudioSource fail!";
        }
        delete ptr;
        ptr = NULL;
    }
}

static void releaseSourceCallback(void* parameter)
{
    qDebug() << "releaseSourceCallback" << QThread::currentThread();
    QDBusInterface interface(ArkMicroAudioService,
                             ArkMicroAudioPath,
                             ArkMicroAudioInterface,
                             QDBusConnection::sessionBus());
    if (NULL != parameter) {
        int* ptr = (int*)parameter;
        QDBusReply<void> reply = interface.call(ArkMicroAudioRelease, *ptr);
        if (reply.isValid()) {
            qDebug() << "requestSourceCallbakc::ArkMicroAudioRelease ok!";
        } else {
            qDebug() << "requestSourceCallbakc::ArkMicroAudioRelease fail!";
        }
        delete ptr;
        ptr = NULL;
    }
}

void Link::requestLinkStatus(const Link_Type type, const Link_STATUS status)
{
    qDebug() << "requestLinkStatus" << type << status;
    initializePrivate();
    switch (type) {
    case ANDROID_MIRROR: {
        m_Private->requestMirrorHandler(status);
        break;
    }
    case CARPLAY: {
        m_Private->requestCarplayHandler(status);
        break;
    }
    case CARLIFE: {
        m_Private->requestCarlifeHandler(status);
        break;
    }
    default: {
        qDebug() << "unsupport command:" << type << status;
    }
    }
}

void Link::requestTouchStatus(const Link_Type deviceType, const TouchType touchType, const QString &touchPointXml)
{
    qWarning() << "Link::requestTouchStatus" << deviceType << touchType << touchPointXml;
    initializePrivate();
    switch (deviceType) {
    case ANDROID_MIRROR: {
        QDBusPendingReply<> reply = m_Private->m_MirrorLinkProxy->requestTouchStatus(deviceType, touchType, touchPointXml);
        reply.waitForFinished();
        qWarning() << "requestTouchStatus" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call requestTouchStatus failed" << reply.error();
        }
        break;
    }
    case CARPLAY: {
        QDBusPendingReply<> reply = m_Private->m_CarplayLinkProxy->requestTouchStatus(deviceType, touchType, touchPointXml);
        reply.waitForFinished();
        qWarning() << "requestTouchStatus" << reply.isFinished();
        if (reply.isError()) {
            qWarning() << "method call requestTouchStatus failed" << reply.error();
        }
        break;
    }
    case CARLIFE: {
        QDBusPendingReply<> reply = m_Private->m_CarlifeLinkProxy->requestTouchStatus(deviceType, touchType, touchPointXml);
        reply.waitForFinished();
        qDebug() << "requestTouchStatus" << reply.isFinished();
        if (reply.isError()) {
           qDebug() << "method call requestTouchStatus failed" << reply.error();
        }
        break;
    }
    default: {
        break;
    }
    }
}

void Link::requestKeyValue(const LinkKeyValue type)
{
    qDebug() << "Link::requestKeyValue" << type;
    initializePrivate();
    QDBusPendingReply<> reply = m_Private->m_MirrorLinkProxy->requestKeyValue(type);
    reply.waitForFinished();
    qDebug() << "requestKeyValue" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call requestKeyValue failed" << reply.error();
    }
}

//void Link::releaseAudioSource(const int source)
//{
//    qDebug() << "Link::releaseAudioSource";
//}

void Link::onServiceRegistered(const QString &service)
{
    qDebug() << "Link::onServiceRegistered" << service;
}

void Link::onServiceUnregistered(const QString &service)
{
    qDebug() << "Link::onServiceUnregistered" << service;
    if (ArkMicroMirrorService == service) {
        g_DbusService->startService(ArkMicroMirrorService);
        //        QDBusPendingReply<> reply = m_Private->m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_START_PROCESS);
#ifdef gcc
        //        reply.waitForFinished();
        //        qDebug() << "m_Private->m_MirrorServer" << reply.isFinished();
        //        if (reply.isError()) {
        //            qDebug() << "method call customEvent failed" << reply.error();
        //        }
#endif
    } else if (ArkMicroCarplayService == service) {
        g_DbusService->startService(ArkMicroCarplayService);
        //        QDBusPendingReply<> reply = m_Private->m_CarplayLinkProxy->requestLinkStatus(CARPLAY, LINK_START_PROCESS);
#ifdef gcc
        //        reply.waitForFinished();
        //        qDebug() << "m_Private->m_MirrorServer" << reply.isFinished();
        //        if (reply.isError()) {
        //            qDebug() << "method call customEvent failed" << reply.error();
        //        }
#endif
    }else if (ArkMicroCarlifeService == service) {
        g_DbusService->startService(ArkMicroCarlifeService);
        //        QDBusPendingReply<> reply = m_Private->m_CarplayLinkProxy->requestLinkStatus(CARPLAY, LINK_START_PROCESS);
#ifdef gcc
        //        reply.waitForFinished();
        //        qDebug() << "m_Private->m_MirrorServer" << reply.isFinished();
        //        if (reply.isError()) {
        //            qDebug() << "method call customEvent failed" << reply.error();
        //        }
#endif
    }
}

void Link::linkStatusChange(const int type, const int status) //收到服务处理
{
    qWarning() << "Link::linkStatusChange" << type << status;
    switch (type) {
    case ANDROID_MIRROR: {
        m_Private->mirrorSourceHandler(status);
        break;
    }
    case CARPLAY: {
        m_Private->carplaySourceHandler(status);
        break;
    }
    case CARLIFE: {
        m_Private->carlifeSourceHandler(status);
        break;
    }

    default: {
        break;
    }
    }
}

Link::Link(QObject *parent)
    : QObject(parent)
    , DbusService::Interface()
    , m_Private(NULL)
{
    g_DbusService->addWatchedService(ArkMicroMirrorService);
    connectSignalAndSlotByNamesake(g_DbusService, this);
}

Link::~Link()
{
}

void Link::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new LinkPrivate(this));
    }
}

LinkPrivate::LinkPrivate(Link *parent)
    : m_Parent(parent)
    , m_Callback(NULL)
    , m_MirrorLinkProxy(NULL)
    , m_CarplayLinkProxy(NULL)

{
    m_CarlifeLinkProxy = NULL;
    initialize();
    connectAllSlots();
}

LinkPrivate::~LinkPrivate()
{
}

void LinkPrivate::initialize()
{
    if (NULL == m_MirrorLinkProxy) {
        m_MirrorLinkProxy = new Local::DbusServer::Mirror(ArkMicroMirrorService,
                                                          ArkMicroMirrorPath,
                                                          QDBusConnection::sessionBus(),
                                                          m_Parent);
    }
    if (NULL == m_CarplayLinkProxy) {
        m_CarplayLinkProxy = new Local::DbusServer::Carplay(ArkMicroCarplayService,
                                                            ArkMicroCarplayPath,
                                                            QDBusConnection::sessionBus(),
                                                            m_Parent);
    }
    if (NULL == m_CarlifeLinkProxy) {
        m_CarlifeLinkProxy = new Local::DbusServer::Carlife(ArkMicroCarlifeService,
                                                            ArkMicroCarlifePath,
                                                            QDBusConnection::sessionBus(),
                                                            m_Parent);
    }
}

void LinkPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DbusService, m_Parent);
    if (NULL != m_MirrorLinkProxy) {
        connectSignalAndSignalByNamesake(m_MirrorLinkProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_MirrorLinkProxy, SIGNAL(onLinkStatusChange(int, int)),
                         m_Parent,          SLOT(linkStatusChange(int, int)),
                         type);
    }
    if (NULL != m_CarplayLinkProxy) {
        connectSignalAndSignalByNamesake(m_CarplayLinkProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_CarplayLinkProxy, SIGNAL(onLinkStatusChange(int, int)),
                         m_Parent,           SLOT(linkStatusChange(int, int)),
                         type);
    }
    if (NULL != m_CarlifeLinkProxy) {
        connectSignalAndSignalByNamesake(m_CarlifeLinkProxy, m_Parent);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
        QObject::connect(m_CarlifeLinkProxy, SIGNAL(onLinkStatusChange(int, int)),
                         m_Parent,           SLOT(linkStatusChange(int, int)),
                         type);
    }
#ifdef gcc
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          QString("Local.DbusServer.Mirror"),
                                          QString("onLinkStatusChange"),
                                          m_Parent,
                                          SIGNAL(onLinkStatusChange(const int, const int)));
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          QString("Local.DbusServer.Mirror"),
                                          QString("onLinkStatusChange"),
                                          m_Parent,
                                          SLOT(linkStatusChange(const int, const int)));
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          QString("Local.DbusServer.Carplay"),
                                          QString("onLinkStatusChange"),
                                          m_Parent,
                                          SIGNAL(onLinkStatusChange(const int, const int)));
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          QString("Local.DbusServer.Carplay"),
                                          QString("onLinkStatusChange"),
                                          m_Parent,
                                          SLOT(linkStatusChange(const int, const int)));
	QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          QString("Local.DbusServer.Carlife"),
                                          QString("onLinkStatusChange"),
                                          m_Parent,
                                          SIGNAL(onLinkStatusChange(const int, const int)));
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          QString("Local.DbusServer.Carlife"),
                                          QString("onLinkStatusChange"),
                                          m_Parent,
                                          SLOT(linkStatusChange(const int, const int)));
#endif
}

void LinkPrivate::linkExit(const AudioSource source)
{
    qDebug() << "LinkPrivate::linkExit" << source << m_Callback;
    qDebug() << "releaseMirrorSource == m_Callback" << (releaseMirrorSource == m_Callback);
    qDebug() << "releaseCarplaySource == m_Callback" << (releaseCarplaySource == m_Callback);
    qDebug() << "releaseMirrorSource == m_Callback" << (releaseMirrorSource == m_Callback);
    qDebug() << "releaseCarlifeSource == m_Callback" << (releaseCarlifeSource == m_Callback);
    qDebug() << "NULL == m_Callback" << (NULL == m_Callback);
    switch (source) {
    case AS_Mirror: {
        if (releaseMirrorSource == m_Callback) {
            m_Callback = NULL;
            g_Link->requestLinkStatus(ANDROID_MIRROR, LINK_EXITED);
        }
        break;
    }
    case AS_Carplay: {
        if (releaseCarplaySource == m_Callback) {
            m_Callback = NULL;
            g_Link->requestLinkStatus(CARPLAY, LINK_EXITED);
        }
        break;
    }
    case AS_Carlife: {
        if (releaseCarlifeSource == m_Callback) {
            m_Callback = NULL;
            g_Link->requestLinkStatus(CARLIFE, LINK_EXITED);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void LinkPrivate::requestMirrorHandler(const Link_STATUS status)
{
    qDebug() << "requestMirrorHandler" << status;
    QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, status);
    //    switch (status) {
    //    case LINK_STARTING: {
    //        QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_STARTING);
    //        //#ifdef gcc
    //        //        reply.waitForFinished();
    //        //        qDebug() << "requestMirrorHandler" << reply.isFinished();
    //        //        if (reply.isError()) {
    //        //            qDebug() << "method call requestMirrorHandler failed" << reply.error();
    //        //        }
    //        //#endif
    //        break;
    //    }
    //    case LINK_EXITING: {
    //        QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_EXITING);
    //        //#ifdef gcc
    //        //        reply.waitForFinished();
    //        //        qDebug() << "requestMirrorHandler" << reply.isFinished();
    //        //        if (reply.isError()) {
    //        //            qDebug() << "method call requestMirrorHandler failed" << reply.error();
    //        //        }
    //        //#endif
    //        break;
    //    }
    //    case LINK_EXITED: {
    //        QDBusPendingReply<> reply = m_MirrorLinkProxy->requestLinkStatus(ANDROID_MIRROR, LINK_EXITED);
    //        break;
    //    }
    //    default: {
    //        break;
    //    }
    //    }
}
void LinkPrivate::requestCarlifeHandler(const int status)
{
    qDebug() << "requestCarlifeHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, LINK_STARTING);
        break;
    }
    case LINK_EXITING: {
        QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, LINK_EXITING);
        break;
    }
    case LINK_EXITED: {
        QDBusPendingReply<> reply = m_CarlifeLinkProxy->requestLinkStatus(CARLIFE, LINK_EXITED);
        break;
    }
    default: {
        break;
    }
    }
}

void LinkPrivate::requestCarplayHandler(const Link_STATUS status)
{
    QDBusPendingReply<> reply = m_CarplayLinkProxy->requestLinkStatus(CARPLAY, status);
    //    switch (status) {
    //    case LINK_STARTING: {
    //        QDBusPendingReply<> reply = m_CarplayLinkProxy->requestLinkStatus(CARPLAY, LINK_STARTING);
    //        //#ifdef gcc
    //        //        reply.waitForFinished();
    //        //        qDebug() << "requestCarplayHandler" << reply.isFinished();
    //        //        if (reply.isError()) {
    //        //            qDebug() << "method call requestCarplayHandler failed" << reply.error();
    //        //        }
    //        //#endif
    //        break;
    //    }
    //    default: {
    //        break;
    //    }
    //    }
}

static void mirrorStarting(void* parameter)
{
//    int* type = new int(AS_Idle);
//    requestSourceCallback(static_cast<void*>(type));
//    qWarning() << "mirrorStarting" << QThread::currentThread();
//    QDBusInterface interface(ArkMicroBluetoothService,
//                             ArkMicroBluetoothPath,
//                             ArkMicroBluetoothInterface,
//                             QDBusConnection::sessionBus());
//    QDBusReply<void> reply = interface.call(QString("synchronize"));
//    if (reply.isValid()) {
//        qWarning() << "mirrorStarting::synchronize ok!";
//    } else {
//        qDebug() << "mirrorStarting::synchronize fail!";
//    }
}

void LinkPrivate::mirrorSourceHandler(const Link_STATUS status)
{
    qWarning() << " LinkPrivate::mirrorSourceHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        const HANDLER ptr = acquirePreemptiveResource(NULL, NULL);
//        if (NULL != ptr) {
//            g_Audio->requestAudioSource(AS_Idle);
//        }
        CustomRunnable* runnable = new CustomRunnable();
        runnable->setCallbackFunction(mirrorStarting, NULL);
        QThreadPool::globalInstance()->start(runnable);
        break;
    }
    case LINK_SUCCESS: {
        const HANDLER ptr = acquirePreemptiveResource(releaseMirrorSource, static_cast<void*>(this));
        if (releaseMirrorSource != ptr) {
            m_Callback = releaseMirrorSource;
            EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
            g_EventEngine->sendCustomEvent(event);
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Mirror);
            runnable->setCallbackFunction(requestSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    case LINK_EXITED: {
        if (releaseMirrorSource == m_Callback) {
            m_Callback = NULL;
            clearOwner();
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Mirror);
            runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    default: {
        break;
    }
    }
}

static void carplayStarting(void* parameter)
{
    int* type = new int(AS_Idle);
    requestSourceCallback(static_cast<void*>(type));
}

void LinkPrivate::carplaySourceHandler(const Link_STATUS status)
{
    qDebug() << " LinkPrivate::carplaySourceHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        const HANDLER ptr = acquirePreemptiveResource(NULL, NULL);
//        if (NULL != ptr) {
//            g_Audio->requestAudioSource(AS_Idle);
//        }
        CustomRunnable* runnable = new CustomRunnable();
        runnable->setCallbackFunction(carplayStarting, NULL);
        QThreadPool::globalInstance()->start(runnable);
        break;
    }
    case LINK_SUCCESS: {
        const HANDLER ptr = acquirePreemptiveResource(releaseCarplaySource, static_cast<void*>(this));
        if (releaseCarplaySource != ptr) {
            m_Callback = releaseCarplaySource;
            EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
            g_EventEngine->sendCustomEvent(event);
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carplay);
            runnable->setCallbackFunction(requestSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    case LINK_EXITED: {
        if (releaseCarplaySource == m_Callback) {
            m_Callback = NULL;
            clearOwner();
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carplay);
            runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    default: {
        break;
    }
    }
}
static void carlifeStarting(void* parameter)
{
    int* type = new int(AS_Idle);
    requestSourceCallback(static_cast<void*>(type));
}

void LinkPrivate::carlifeSourceHandler(const Link_STATUS status)
{
    qDebug() << " LinkPrivate::carlifeSourceHandler" << status;
    switch (status) {
    case LINK_STARTING: {
        const HANDLER ptr = acquirePreemptiveResource(NULL, NULL);
//        if (NULL != ptr) {
//            g_Audio->requestAudioSource(AS_Idle);
//        }
        CustomRunnable* runnable = new CustomRunnable();
        runnable->setCallbackFunction(carlifeStarting, NULL);
        QThreadPool::globalInstance()->start(runnable);
        break;
    }
    case LINK_SUCCESS: {
        const HANDLER ptr = acquirePreemptiveResource(releaseCarlifeSource, static_cast<void*>(this));
        if (releaseCarlifeSource != ptr) {
            m_Callback = releaseCarlifeSource;
            EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, NULL);
            g_EventEngine->sendCustomEvent(event);
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carlife);
            runnable->setCallbackFunction(requestSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    case LINK_EXITED: {
        if (releaseCarlifeSource == m_Callback) {
            m_Callback = NULL;
            clearOwner();
            CustomRunnable* runnable = new CustomRunnable();
            int* type = new int(AS_Carlife);
            runnable->setCallbackFunction(releaseSourceCallback, static_cast<void*>(type));
            QThreadPool::globalInstance()->start(runnable);
        }
        break;
    }
    default: {
        break;
    }
    }
}
void Link::Interface::onLinkStatusChange(const int type, const int status)
{
}
