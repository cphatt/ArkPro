#ifndef MULTIMEDIASERVICE_H
#define MULTIMEDIASERVICE_H

#include "MultimediaServiceProxy.h"
#include <QObject>
#include <QScopedPointer>

#define MultimediaApplication                   QString("-multimedia")
#define ArkMicroMultimediaService               QString("com.arkmicro.multimedia")
#define ArkMicroMultimediaPath                  QString("/com/arkmicro/multimedia")
#define ArkMicroMultimediaInterface             QString("Local.DbusServer.Multimedia")

enum DeviceWatcherType {
    DWT_SDDisk = 0,
    DWT_USBDisk = 1,
};
#define DeviceWatcherType int

enum DeviceWatcherStatus {
    DWS_Empty = 0,
    DWS_Busy = 1,
    DWS_Ready = 2,
    DWS_Remove = 3,
};
#define DeviceWatcherStatus int

enum MusicPlayerPlayMode {
    MPPM_AllRepeat = 0,
    MPPM_Shuffle = 1,
    MPPM_RepeatOnce = 2,
};
#define MusicPlayerPlayMode int

enum MusicPlayerPlayStatus {
    MPPS_Start = 0,
    MPPS_Stop = 1,
    MPPS_Pause = 2,
    MPPS_Play = 3,
    MPPS_Exit = 4,
};
#define MusicPlayerPlayStatus int

enum ImagePlayerPlayStatus {
    IPPS_Start = 0,
    IPPS_Pause = 1,
    IPPS_Play = 2,
    IPPS_Browse = 3,
    IPPS_Exit = 4,
};
#define ImagePlayerPlayStatus int

enum VideoPlayerPlayStatus {
    VPPS_Start = 0,
    VPPS_Stop = 1,
    VPPS_Pause = 2,
    VPPS_Play = 3,
    VPPS_Exit = 4,
};
#define VideoPlayerPlayStatus int

enum VideoPlayerShowStatus {
    VPSS_Normal = 0,
    VPSS_FullScreen = 1,
};
#define VideoPlayerShowStatus int

class MultimediaServicePrivate;
class MultimediaService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MultimediaService)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Multimedia")
#ifdef g_MultimediaService
#undef g_MultimediaService
#endif
#define g_MultimediaService (MultimediaService::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        //    public slots:
        //DeviceWatcher::Interface
        virtual void deviceWatcherCheckStatus(const int type) = 0;
        //    void deviceWatcherCheckStatus(const DeviceWatcherType type);
        //MusicPlayer::Interface
        virtual void musicPlayerRequestFileNames() = 0;
        virtual void musicPlayerSetPlayModeToggle() = 0;
        virtual void musicPlayerSetPlayMode(const int mode) = 0;
        //    void musicPlayerSetPlayMode(const MusicPlayerPlayMode mode);
        virtual void musicPlayerSetPlayStatusToggle() = 0;
        virtual void musicPlayerSetPlayStatus(const int status) = 0;
        //    void musicPlayerSetPlayStatus(const MusicPlayerPlayStatus status);
        virtual void musicPlayerPlayListViewIndex(const int type, const int index) = 0;
        //    void MultimediaService::musicPlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
        virtual void musicPlayerPlayPreviousListViewIndex() = 0;
        virtual void musicPlayerPlayNextListViewIndex() = 0;
        virtual void musicPlayerSeekToMillesimal(const int millesimal) = 0;
        virtual void musicPlayerExit() = 0;
        //ImagePlayer::Interface
        virtual void imagePlayerRequestFileNames(const int type) = 0;
        //    void imagePlayerRequestFileNames(const DeviceWatcherType type);
        virtual void imagePlayerPlayListViewIndex(const int type, const int index) = 0;
        //    void ImagePlayer::imagePlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
        virtual void imagePlayerPlayPreviousListViewIndex() = 0;
        virtual void imagePlayerPlayNextListViewIndex() = 0;
        virtual void imagePlayerRotateImage() = 0;
        virtual void imagePlayerZoomInImage() = 0;
        virtual void imagePlayerZoomOutImage() = 0;
        virtual void imagePlayerSetPlayStatusToggle() = 0;
        virtual void imagePlayerSetPlayStatus(const int status) = 0;
        //    void imagePlayerSetPlayStatus(const ImagePlayerPlayStatus status);
        virtual void imagePlayerExit() = 0;
        //VideoPlayer::Interface
        virtual void videoPlayerRequestFileNames(const int type) = 0;
        //    void videoPlayerRequestFileNames(const DeviceWatcherType type);
        virtual void videoPlayerSetPlayStatusToggle() = 0;
        virtual void videoPlayerSetShowStatus(const int status) = 0;
        //    void videoPlayerSetShowStatus(const VideoPlayerShowStatus status);
        virtual void videoPlayerSetPlayStatus(const int status) = 0;
        //    void videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status);
        virtual void videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height) = 0;
        //    void videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height);
        virtual void videoPlayerPlayPreviousListViewIndex() = 0;
        virtual void videoPlayerPlayNextListViewIndex() = 0;
        virtual void videoPlayerSeekToMillesimal(const int millesimal) = 0;
        //    signals:
        //DeviceWatcher::Interface
        virtual void onDeviceWatcherStatus(const int type, const int status) = 0;
        //    void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
        virtual void onMusicFilePath(const QString &path, const int type) = 0;
        //    void onMusicFilePath(const QString &path, const DeviceWatcherType type);
        virtual void onImageFilePath(const QString &path, const int type) = 0;
        //    void onImageFilePath(const QString &path, const DeviceWatcherType type);
        virtual void onVideoFilePath(const QString &path, const int type) = 0;
        //    void onVideoFilePath(const QString &path, const DeviceWatcherType type);
        //MusicPlayer::Interface
        virtual void onMusicPlayerPlayMode(const int mode) = 0;
        //    virtual void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode) = 0;
        virtual void onMusicPlayerPlayStatus(const int status) = 0;
        //    virtual void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status) = 0;
        virtual void onMusicPlayerElapsedInformation(const int elapsedTime,
                                                     const int elapsedMillesimal) = 0;
        virtual void onMusicPlayerID3TagChange(const int index,
                                               const QString &fileName,
                                               const int endTime) = 0;
        virtual void onMusicPlayerFileNames(const int type, const QString &xml) = 0;
        //    virtual void onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml) = 0;
        //ImagePlayer::Interface
        virtual void onImagePlayerFileNames(const int type, const QString &xml) = 0;
        //    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
        virtual void onImagePlayerPlayStatus(const int status) = 0;
        //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
        virtual void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate) = 0;
        //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
        //VideoPlayer::Interface
        virtual void onVideoPlayerShowStatus(const int status) = 0;
        //    void onVideoPlayerShowStatus(const VideoPlayerShowStatus status);
        virtual void onVideoPlayerPlayStatus(const int status) = 0;
        //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
        virtual void onVideoPlayerFileNames(const int type, const QString& xml) = 0;
        //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
        virtual void onVideoPlayerInformation(const QString &fileName, const int endTime) = 0;
        virtual void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal) = 0;
    };
    explicit MultimediaService(QObject* parent = NULL);
    ~MultimediaService();
#ifdef gcc
public slots:
    void usbToggle(const int action);
    void sdToggle(const int action);
#endif
public slots:
    void releaseAudioSource(const int source);
//    void releaseAudioSource(const AudioSource source);
    void synchronize();
    //DeviceWatcher::Interface
    void deviceWatcherCheckStatus(const int type);
    //    void deviceWatcherCheckStatus(const DeviceWatcherType type);
    //MusicPlayer::Interface
    void musicPlayerRequestFileNames();
    void musicPlayerSetPlayModeToggle();
    void musicPlayerSetPlayMode(const int mode);
    //    void musicPlayerSetPlayMode(const MusicPlayerPlayMode mode);
    void musicPlayerSetPlayStatusToggle();
    void musicPlayerSetPlayStatus(const int status);
    //    void musicPlayerSetPlayStatus(const MusicPlayerPlayStatus status);
    void musicPlayerPlayListViewIndex(const int type, const int index);
    //    void MultimediaService::musicPlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
    void musicPlayerPlayPreviousListViewIndex();
    void musicPlayerPlayNextListViewIndex();
    void musicPlayerSeekToMillesimal(const int millesimal);
    void musicPlayerExit();
    //ImagePlayer::Interface
    void imagePlayerRequestFileNames(const int type);
    //    void imagePlayerRequestFileNames(const DeviceWatcherType type);
    void imagePlayerPlayListViewIndex(const int type, const int index);
    //    void ImagePlayer::imagePlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
    void imagePlayerPlayPreviousListViewIndex();
    void imagePlayerPlayNextListViewIndex();
    void imagePlayerRotateImage();
    void imagePlayerZoomInImage();
    void imagePlayerZoomOutImage();
    void imagePlayerSetPlayStatusToggle();
    void imagePlayerSetPlayStatus(const int status);
    //    void imagePlayerSetPlayStatus(const ImagePlayerPlayStatus status);
    void imagePlayerExit();
    //VideoPlayer::Interface
    void videoPlayerRequestFileNames(const int type);
    //    void videoPlayerRequestFileNames(const DeviceWatcherType type);
    void videoPlayerSetPlayStatusToggle();
    void videoPlayerSetShowStatus(const int status);
    //    void videoPlayerSetShowStatus(const VideoPlayerShowStatus status);
    void videoPlayerSetPlayStatus(const int status);
    //    void videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status);
    void videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height);
    //    void videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
    void videoPlayerPlayPreviousListViewIndex();
    void videoPlayerPlayNextListViewIndex();
    void videoPlayerSeekToMillesimal(const int millesimal);
signals:
    //DeviceWatcher::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //    void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onMusicFilePath(const QString &path, const int type);
    //    void onMusicFilePath(const QString &path, const DeviceWatcherType type);
    void onImageFilePath(const QString &path, const int type);
    //    void onImageFilePath(const QString &path, const DeviceWatcherType type);
    void onVideoFilePath(const QString &path, const int type);
    //    void onVideoFilePath(const QString &path, const DeviceWatcherType type);
    //MusicPlayer::Interface
    void onMusicPlayerPlayMode(const int mode);
    //    void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode);
    void onMusicPlayerPlayStatus(const int status);
    //    void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerElapsedInformation(const int elapsedTime,
                                         const int elapsedMillesimal);
    void onMusicPlayerID3TagChange(const int index,
                                           const QString &fileName,
                                           const int endTime);
    void onMusicPlayerFileNames(const int type, const QString &xml);
    //    void onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    //ImagePlayer::Interface
    void onImagePlayerFileNames(const int type, const QString &xml);
    //    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
    //VideoPlayer::Interface
    void onVideoPlayerShowStatus(const int status);
    //    void onVideoPlayerShowStatus(const VideoPlayerShowStatus status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerFileNames(const int type, const QString& xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerInformation(const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
private:
    friend class MultimediaServicePrivate;
    QScopedPointer<MultimediaServicePrivate> m_Private;
};

#endif // MULTIMEDIASERVICE_H
