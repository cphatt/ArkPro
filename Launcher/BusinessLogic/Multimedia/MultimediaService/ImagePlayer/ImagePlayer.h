#ifndef IMAGEPLAYER_H
#define IMAGEPLAYER_H

#include "DeviceWatcher/DeviceWatcher.h"
#include <QObject>
#include <QImage>
#include <QScopedPointer>

class ImagePlayerPrivate;
class ImagePlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ImagePlayer)
#ifdef g_ImagePlayer
#undef g_ImagePlayer
#endif
#define g_ImagePlayer (ImagePlayer::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        //ImagePlayer::Interface
        virtual void onImagePlayerFileNames(const int type, const QString &xml) = 0;
    //    virtual void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml) = 0;
        virtual void onImagePlayerPlayStatus(const int status) = 0;
    //        virtual void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status) = 0;
        virtual void onImagePlayerChange(const QString &fileName,const int width, const int height, const int format, const QByteArray &imageData) = 0;
    };
    inline static ImagePlayer* instance() {
        static ImagePlayer imagePlayer;
        return &imagePlayer;
    }
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
signals:
    //ImagePlayer::Interface
    void onImagePlayerFileNames(const int type, const QString &xml);
//    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onImagePlayerPlayStatus(const int status);
//        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerChange(const QString &fileName, const int width, const int height, const int format, const QByteArray &imageData);
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
    void onPlayTimerTimeout();
    void onAnimationTimerTimeout();
    //MusicPlayer::Interface
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    //VideoPlayer::Interface
    void onVideoPlayerPlayStatus(const int status);
    //    onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
private:
    explicit ImagePlayer(QObject *parent = NULL);
    ~ImagePlayer();
    //    void emitOnImageChange(const QString &fileName, const QImage &image);
    friend class ImagePlayerPrivate;
    QScopedPointer<ImagePlayerPrivate> m_Private;
};

#endif // IMAGEPLAYER_H
