#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "DeviceWatcher/DeviceWatcher.h"
#include <QObject>
#include <QImage>
#include <QScopedPointer>

class MusicPlayerPrivate;
class MusicPlayer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicPlayer)
#ifdef g_MusicPlayer
#undef g_MusicPlayer
#endif
#define g_MusicPlayer (MusicPlayer::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onMusicPlayerPlayMode(const int mode) = 0;
        //    virtual void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode) = 0;
        virtual void onMusicPlayerPlayStatus(const int status) = 0;
        //    virtual void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status) = 0;
        virtual void onMusicPlayerElapsedInformation(const int elapsedTime,
                                                     const int elapsedMillesimal) = 0;
        virtual void onMusicPlayerID3TagChange(const int type,
                                               const int index,
                                               const QString &fileName,
                                               const int endTime) = 0;
        virtual void onMusicPlayerFileNames(const int type, const QString &xml) = 0;
        //    virtual void onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml) = 0;
    };
    inline static MusicPlayer* instance() {
        static MusicPlayer* musicPlayer(new MusicPlayer(qApp));
        return musicPlayer;
    }
    void releaseAudioSource(const int source);
//    void releaseAudioSource(const AudioSource source);
    void musicPlayerRequestFileNames(const int type);
    //    void musicPlayerRequestFileNames(const DeviceWatcherType type);
    void musicPlayerSetPlayModeToggle();
    void musicPlayerSetPlayMode(const int mode);
    //    void musicPlayerSetPlayMode(const MusicPlayerPlayMode mode);
    void musicPlayerSetPlayStatusToggle();
    void musicPlayerSetPlayStatus(const int status);
    //    void musicPlayerSetPlayStatus(const MusicPlayerPlayStatus status);
    void musicPlayerPlayListViewIndex(const int type, const int index);
    //    void musicPlayerPlayListViewIndex(const DeviceWatcherType type, const int index);
    void musicPlayerPlayPreviousListViewIndex();
    void musicPlayerPlayNextListViewIndex();
    void musicPlayerSeekToMillesimal(const int millesimal);
    void musicPlayerExit(const int type);
    //    void musicPlayerExit(const DeviceWatcherType type);
signals:
    void onMusicPlayerPlayMode(const int mode);
    //    void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode);
    void onMusicPlayerPlayStatus(const int status);
    //    void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerElapsedInformation(const int elapsedTime,
                                         const int elapsedMillesimal);

    void onMusicPlayerID3TagChange(const int type,
                                   const int index,
                                   const QString &fileName,
                                   const int endTime);
    void onMusicPlayerFileNames(const int type, const QString &xml);
    //    void onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml);
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
    void onTimeout();
    void onStarted();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onError(QProcess::ProcessError error);
    void onStateChanged(QProcess::ProcessState state);
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
private:
    explicit MusicPlayer(QObject* parent = NULL);
    ~MusicPlayer();
    friend class MusicPlayerPrivate;
    QScopedPointer<MusicPlayerPrivate> m_Private;
};

#endif // MUSICPLAYER_H
