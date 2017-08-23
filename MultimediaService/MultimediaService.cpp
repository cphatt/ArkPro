#include "MultimediaService.h"
#include "AutoConnect.h"
#include "DeviceWatcher/DeviceWatcher.h"
#include "MusicPlayer/MusicPlayer.h"
#include "VideoPlayer/VideoPlayer.h"
#include "ImagePlayer/ImagePlayer.h"
#include "AudioService.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDBusConnection>

class MultimediaServicePrivate
{
    Q_DISABLE_COPY(MultimediaServicePrivate)
public:
    explicit MultimediaServicePrivate(MultimediaService* parent);
    ~MultimediaServicePrivate();
    void initialize();
    void connectAllSlots();
private:
    MultimediaService* m_Parent;
};

MultimediaService::MultimediaService(QObject *parent)
    : QObject(parent)
    , m_Private(new MultimediaServicePrivate(this))
{
}

MultimediaService::~MultimediaService()
{
}

#ifdef gcc
void MultimediaService::usbToggle(const int action)
{
    g_DeviceWatcher->usbToggle(action);
}

void MultimediaService::sdToggle(const int action)
{
    g_DeviceWatcher->sdToggle(action);
}
#endif

void MultimediaService::releaseAudioSource(const AudioSource source)
{
    qDebug() << "MultimediaService::releaseAudioSource" << source;
    switch (source) {
    case AS_Music: {
        g_MusicPlayer->releaseAudioSource(AS_Music);
        break;
    }
    case AS_Video: {
        g_VideoPlayer->releaseAudioSource(AS_Video);
        break;
    }
    default: {
        break;
    }
    }
}

void MultimediaService::synchronize()
{
    g_DeviceWatcher->synchronize();
}

void MultimediaService::deviceWatcherCheckStatus(const DeviceWatcherType type)
{
    g_DeviceWatcher->deviceWatcherCheckStatus(type);
}

void MultimediaService::musicPlayerRequestFileNames()
{
    g_MusicPlayer->musicPlayerRequestFileNames(DWT_USBDisk);
}

void MultimediaService::musicPlayerSetPlayModeToggle()
{
    g_MusicPlayer->musicPlayerSetPlayModeToggle();
}

void MultimediaService::musicPlayerSetPlayMode(const MusicPlayerPlayMode mode)
{
    g_MusicPlayer->musicPlayerSetPlayMode(mode);
}

void MultimediaService::musicPlayerSetPlayStatusToggle()
{
    g_MusicPlayer->musicPlayerSetPlayStatusToggle();
}

void MultimediaService::musicPlayerSetPlayStatus(const MusicPlayerPlayStatus status)
{
    g_MusicPlayer->musicPlayerSetPlayStatus(status);
}

void MultimediaService::musicPlayerPlayListViewIndex(const DeviceWatcherType type, const int index)
{
    g_MusicPlayer->musicPlayerPlayListViewIndex(type, index);
}

void MultimediaService::musicPlayerPlayPreviousListViewIndex()
{
    g_MusicPlayer->musicPlayerPlayPreviousListViewIndex();
}

void MultimediaService::musicPlayerPlayNextListViewIndex()
{
    g_MusicPlayer->musicPlayerPlayNextListViewIndex();
}

void MultimediaService::musicPlayerSeekToMillesimal(const int millesimal)
{
    g_MusicPlayer->musicPlayerSeekToMillesimal(millesimal);
}

void MultimediaService::musicPlayerExit()
{
    g_MusicPlayer->musicPlayerExit(DWT_USBDisk);
}

void MultimediaService::imagePlayerRequestFileNames(const DeviceWatcherType type)
{
    g_ImagePlayer->imagePlayerRequestFileNames(type);
}

void MultimediaService::imagePlayerPlayListViewIndex(const DeviceWatcherType type, const int index)
{
    g_ImagePlayer->imagePlayerPlayListViewIndex(type, index);
}

void MultimediaService::imagePlayerPlayPreviousListViewIndex()
{
    g_ImagePlayer->imagePlayerPlayPreviousListViewIndex();
}

void MultimediaService::imagePlayerPlayNextListViewIndex()
{
    g_ImagePlayer->imagePlayerPlayNextListViewIndex();
}

void MultimediaService::imagePlayerRotateImage()
{
    g_ImagePlayer->imagePlayerRotateImage();
}

void MultimediaService::imagePlayerZoomInImage()
{
    g_ImagePlayer->imagePlayerZoomInImage();
}

void MultimediaService::imagePlayerZoomOutImage()
{
    g_ImagePlayer->imagePlayerZoomOutImage();
}

void MultimediaService::imagePlayerSetPlayStatusToggle()
{
    g_ImagePlayer->imagePlayerSetPlayStatusToggle();
}

void MultimediaService::imagePlayerSetPlayStatus(const ImagePlayerPlayStatus status)
{
    g_ImagePlayer->imagePlayerSetPlayStatus(status);
}

void MultimediaService::imagePlayerExit()
{
    g_ImagePlayer->imagePlayerExit();
}

void MultimediaService::videoPlayerRequestFileNames(const DeviceWatcherType type)
{
    g_VideoPlayer->videoPlayerRequestFileNames(type);
}

void MultimediaService::videoPlayerSetPlayStatusToggle()
{
    g_VideoPlayer->videoPlayerSetPlayStatusToggle();
}

void MultimediaService::videoPlayerSetShowStatus(const VideoPlayerShowStatus status)
{
    g_VideoPlayer->videoPlayerSetShowStatus(status);
}

void MultimediaService::videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status)
{
    g_VideoPlayer->videoPlayerSetPlayStatus(status);
}

void MultimediaService::videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height)
{
    g_VideoPlayer->videoPlayerPlayListViewIndex(type, index, x, y, width, height);
}

void MultimediaService::videoPlayerPlayPreviousListViewIndex()
{
    g_VideoPlayer->videoPlayerPlayPreviousListViewIndex();
}

void MultimediaService::videoPlayerPlayNextListViewIndex()
{
    g_VideoPlayer->videoPlayerPlayNextListViewIndex();
}

void MultimediaService::videoPlayerSeekToMillesimal(const int millesimal)
{
    g_VideoPlayer->videoPlayerSeekToMillesimal(millesimal);
}

MultimediaServicePrivate::MultimediaServicePrivate(MultimediaService* parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}

MultimediaServicePrivate::~MultimediaServicePrivate()
{
}

void MultimediaServicePrivate::initialize()
{
    qDebug() << "MultimediaServicePrivate::initialize";
    bool ret(true);
    if (ArkMicroMultimediaService == qApp->applicationName()) {
        ret = QDBusConnection::sessionBus().registerService(ArkMicroMultimediaService);
    } else {
        qDebug() << "MultimediaService Register inner!";
    }
    ret = ret && QDBusConnection::sessionBus().registerObject(ArkMicroMultimediaPath,
                                                              m_Parent,
                                                              QDBusConnection::ExportNonScriptableSignals
                                                              | QDBusConnection::ExportNonScriptableSlots);
    if (!ret) {
        qCritical() << "MultimediaService Register QDbus failed!";
        exit(EXIT_FAILURE);
    }
    qDebug() << "MultimediaService Register QDbus ok!";
}

void MultimediaServicePrivate::connectAllSlots()
{
    connectSignalAndSignalByNamesake(g_MusicPlayer, m_Parent);
    connectSignalAndSignalByNamesake(g_ImagePlayer, m_Parent);
    connectSignalAndSignalByNamesake(g_VideoPlayer, m_Parent);
    connectSignalAndSignalByNamesake(g_DeviceWatcher, m_Parent);
}
