#include "Multimedia.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "BusinessLogic/Widget/Widget.h"
#include "EventEngine.h"
#include "ArkApplication.h"
#include "MultimediaService.h"
#include "AutoConnect.h"
#include <QProcess>
#include <QDBusServiceWatcher>
#include <QFile>
#include <QDebug>
#include <unistd.h>

class MultimediaPrivate
{
    Q_DISABLE_COPY(MultimediaPrivate)
public:
    explicit MultimediaPrivate(Multimedia* parent);
    ~MultimediaPrivate();
    void initialize();
    void connectAllSlots();
    void receiveAllCustomEvent();
    MultimediaService* m_MultimediaService;
    Local::DbusServer::Multimedia* m_MultimediaServiceProxy;
private:
    Multimedia* m_Parent;
};

void Multimedia::deviceWatcherCheckStatus(const int type)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->deviceWatcherCheckStatus(type);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->deviceWatcherCheckStatus(type);
#ifdef gcc
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::deviceWatcherCheckStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::deviceWatcherCheckStatus failed" << reply.error();
        }
#endif
    }
}

void Multimedia::musicPlayerRequestFileNames()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerRequestFileNames();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerRequestFileNames();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerRequestFileNames" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerRequestFileNames failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayModeToggle()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerSetPlayModeToggle();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayModeToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayModeToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayModeToggle failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayMode(const int mode)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerSetPlayMode(mode);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayMode(mode);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayMode" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayMode failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayStatusToggle()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerSetPlayStatusToggle();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayStatusToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayStatusToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayStatusToggle failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSetPlayStatus(const int status)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerSetPlayStatus(status);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSetPlayStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSetPlayStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSetPlayStatus failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerPlayListViewIndex(const int type, const int index)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerPlayListViewIndex(type, index);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->musicPlayerPlayListViewIndex(type, index);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerPlayPreviousListViewIndex()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerPlayPreviousListViewIndex();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerPlayPreviousListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerPlayPreviousListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerPlayPreviousListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerPlayNextListViewIndex()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerPlayNextListViewIndex();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerPlayNextListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerPlayNextListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerPlayNextListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerSeekToMillesimal(const int millesimal)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerSeekToMillesimal(millesimal);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerSeekToMillesimal(millesimal);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerSeekToMillesimal" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerSeekToMillesimal failed" << reply.error();
        }
    }
}

void Multimedia::musicPlayerExit()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->musicPlayerExit();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->musicPlayerExit();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::musicPlayerExit" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::musicPlayerExit failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerRequestFileNames(const int type)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerRequestFileNames(type);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerRequestFileNames(type);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerRequestFileNames" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerRequestFileNames failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerPlayListViewIndex(const int type, const int index)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerPlayListViewIndex(type, index);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerPlayListViewIndex(type, index);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerPlayPreviousListViewIndex()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerPlayPreviousListViewIndex();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerPlayPreviousListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerPlayNextListViewIndex()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerPlayNextListViewIndex();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerPlayNextListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerPlayNextListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerPlayNextListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerRotateImage()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerRotateImage();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerRotateImage();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerRotateImage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerRotateImage failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerZoomInImage()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerZoomInImage();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerZoomInImage();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerZoomInImage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerZoomInImage failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerZoomOutImage()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerZoomOutImage();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->imagePlayerZoomOutImage();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::imagePlayerZoomOutImage" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::imagePlayerZoomOutImage failed" << reply.error();
        }
    }
}

void Multimedia::imagePlayerSetPlayStatusToggle()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerSetPlayStatusToggle();
    }
}

void Multimedia::imagePlayerSetPlayStatus(const int status)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerSetPlayStatus(status);
    }
}

void Multimedia::imagePlayerExit()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->imagePlayerExit();
    }
}

void Multimedia::videoPlayerRequestFileNames(const DeviceWatcherType type)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerRequestFileNames(type);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerRequestFileNames(type);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerRequestFileNames" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerRequestFileNames failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSetPlayStatusToggle()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerSetPlayStatusToggle();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSetPlayStatusToggle();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSetPlayStatusToggle" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSetPlayStatusToggle failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSetShowStatus(const VideoPlayerShowStatus status)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerSetShowStatus(status);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSetShowStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSetShowStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSetShowStatus failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerSetPlayStatus(status);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSetPlayStatus(status);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSetPlayStatus" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSetPlayStatus failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerPlayListViewIndex(type, index, x, y, width, height);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerPlayListViewIndex(type, index, x, y, width, height);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerPlayListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerPlayListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerPlayPreviousListViewIndex()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerPlayPreviousListViewIndex();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerPlayPreviousListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerPlayPreviousListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerPlayPreviousListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerPlayNextListViewIndex()
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerPlayNextListViewIndex();
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerPlayNextListViewIndex();
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerPlayNextListViewIndex" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerPlayNextListViewIndex failed" << reply.error();
        }
    }
}

void Multimedia::videoPlayerSeekToMillesimal(const int millesimal)
{
    if (NULL != m_Private->m_MultimediaService) {
        m_Private->m_MultimediaService->videoPlayerSeekToMillesimal(millesimal);
    } else if (NULL != m_Private->m_MultimediaServiceProxy) {
        QDBusPendingReply<void> reply = m_Private->m_MultimediaServiceProxy->videoPlayerSeekToMillesimal(millesimal);
        reply.waitForFinished();
        qDebug() << "Dbus call Multimedia::videoPlayerSeekToMillesimal" << reply.isFinished();
        if (reply.isError()) {
            qDebug() << "method call Multimedia::videoPlayerSeekToMillesimal failed" << reply.error();
        }
    }
}

void Multimedia::customEvent(QEvent *event)
{
    qDebug() << "Multimedia::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        g_EventEngine->detachCustomEvent(this);
#ifdef gcc
        int count(4);
#else
        int count(3);
#endif
        if (count == ArkApp->arguments().size()) {
            if (NULL == m_Private->m_MultimediaServiceProxy) {
                m_Private->m_MultimediaServiceProxy = new Local::DbusServer::Multimedia(ArkMicroMultimediaService,
                                                                                        ArkMicroMultimediaPath,
                                                                                        QDBusConnection::sessionBus(),
                                                                                        qApp);
                connectSignalAndSignalByNamesake(m_Private->m_MultimediaServiceProxy, this);
                connectSignalAndSlotByNamesake(m_Private->m_MultimediaServiceProxy, this);
                connectSignalAndSlotByNamesake(g_DbusService, this);
                onServiceUnregistered(ArkMicroMultimediaService);
            }
        } else {
            if (NULL == m_Private->m_MultimediaService) {
                m_Private->m_MultimediaService = new MultimediaService(this);
                connectSignalAndSignalByNamesake(m_Private->m_MultimediaService, this);
                onServiceRegistered(ArkMicroMultimediaService);
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

void Multimedia::onServiceRegistered(const QString &service)
{
    qDebug() << "Multimedia::onServiceRegistered" << service << m_Private->m_MultimediaService << m_Private->m_MultimediaServiceProxy;
    if (ArkMicroMultimediaService == service) {
        if (NULL != m_Private->m_MultimediaService) {
            m_Private->m_MultimediaService->synchronize();
        } else if (NULL != m_Private->m_MultimediaServiceProxy) {
            QDBusPendingReply<> reply = m_Private->m_MultimediaServiceProxy->synchronize();
            reply.waitForFinished();
            qDebug() << "Dbus call Multimedia::setLanguage" << reply.isFinished();
            if (reply.isError()) {
                qDebug() << "method call Multimedia::setLanguage failed" << reply.error();
            }
        }
    }
}

void Multimedia::onServiceUnregistered(const QString &service)
{
    qDebug() << "Multimedia::onServiceUnregistered" << service;
    if (ArkMicroMultimediaService == service) {
        //#ifdef gcc
        g_DbusService->addWatchedService(ArkMicroMultimediaService);
        QStringList cmd;
        cmd << QString("-t") << MultimediaApplication;
        bool ret = QProcess::startDetached(qApp->applicationFilePath(), cmd);
        qDebug() << "start" << ArkMicroMultimediaService << ret;
        //#else
        //        g_DbusService->startService(MULTIMEDIASERVICE);
        //#endif
    }
}

Multimedia::Multimedia(QObject *parent)
    : QObject(parent)
    , MultimediaService::Interface()
    , DbusService::Interface()
    , m_Private(new MultimediaPrivate(this))
{
}

Multimedia::~Multimedia()
{
}

MultimediaPrivate::MultimediaPrivate(Multimedia *parent)
    : m_Parent(parent)
{
    m_MultimediaService = NULL;
    m_MultimediaServiceProxy = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

MultimediaPrivate::~MultimediaPrivate()
{
    qDebug() << "MultimediaPrivate::~MultimediaPrivate";
    system("kill  `ps -elf | grep Launcher | grep multimedia | awk '{print $4}'`");
    system("kill -10 `ps -elf | grep mplayer | grep slave | grep quiet | grep ao | grep alsa | awk '{print $4}'`");
}

void MultimediaPrivate::initialize()
{
}

void MultimediaPrivate::connectAllSlots()
{
}

void MultimediaPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

