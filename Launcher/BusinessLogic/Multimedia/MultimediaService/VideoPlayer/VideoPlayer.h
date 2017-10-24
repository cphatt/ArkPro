#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include "AVEngine/AVEngine.h"
#include "DeviceWatcher/DeviceWatcher.h"
#include <QObject>
#include <QProcess>
#include <QSharedPointer>

class VideoPlayerPrivate;
class VideoPlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayer)
#ifdef g_VideoPlayer
#undef g_VideoPlayer
#endif
#define g_VideoPlayer (VideoPlayer::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onVideoPlayerShowStatus(const int status) = 0;
        //    virtual void onVideoPlayerShowStatus(const VideoPlayerShowStatus status) = 0;
        virtual void onVideoPlayerPlayStatus(const int status) = 0;
        //    virtual void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status) = 0;
        virtual void onVideoPlayerFileNames(const int type, const QString &xml) = 0;
        //    virtual void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml) = 0;
        virtual void onVideoPlayerInformation(const QString &fileName, const int endTime) = 0;
        virtual void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal) = 0;
    };
    inline static VideoPlayer* instance() {
        static VideoPlayer videoPlayer;
        return &videoPlayer;
    }
    void videoPlayerRequestFileNames(const int type);
    //    void videoPlayerRequestFileNames(const DeviceWatcherType type);
    void videoPlayerSetPlayStatusToggle();
    void videoPlayerSetShowStatus(const int status);
    //    void videoPlayerSetShowStatus(const VideoPlayerShowStatus status);
    void videoPlayerSetPlayStatus(const int status);
    //    void videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status);
    void videoPlayerPlayListViewIndex(const int type, const int index, const int x, const int y, const int width, const int height);
//    void videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height);
    void videoPlayerPlayPreviousListViewIndex();
    void videoPlayerPlayNextListViewIndex();
    void videoPlayerSeekToMillesimal(const int millesimal);
signals:
    void onVideoPlayerShowStatus(const int status);
    //    void onVideoPlayerShowStatus(const VideoPlayerShowStatus status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerFileNames(const int type, const QString &xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerInformation(const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
protected slots:
    //DeviceWatcher::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //    virtual void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status) = 0;
    void onMusicFilePath(const QString &path, const int type);
    //    virtual void onMusicFilePath(const QString &path, const DeviceWatcherType type) = 0;
    void onImageFilePath(const QString &path, const int type);
    //    virtual void onImageFilePath(const QString &path, const DeviceWatcherType type) = 0;
    void onVideoFilePath(const QString &path, const int type);
    //    virtual void onVideoFilePath(const QString &path, const DeviceWatcherType type) = 0;
private slots:
    void onMplayerOutput();
    void onTimeout();
    void onStateChanged(QProcess::ProcessState state);
    void onError(QProcess::ProcessError error);
private:
    explicit VideoPlayer(QObject* parent = NULL);
    ~VideoPlayer();
    friend class VideoPlayerPrivate;
    QSharedPointer<VideoPlayerPrivate> m_Private;
};

#endif // VIDEOPLAYER_H
