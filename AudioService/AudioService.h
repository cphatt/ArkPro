#ifndef AUDIOSERVICE_H
#define AUDIOSERVICE_H

#define AudioApplication             QString("-audiomanager")
#define ArkMicroAudioService         QString("com.arkmicro.audiomanager")
#define ArkMicroAudioPath            QString("/com/arkmicro/audiomanager")
#define ArkMicroAudioInterface       QString("Local.DbusServer.AudioManager")
#define ArkMicroAudioRequest         QString("requestAudioSource")
#define ArkMicroAudioRelease         QString("releaseAudioSource")

#include <QObject>
#include <QScopedPointer>

enum EffectType {
    ET_Undefine = -1,
    ET_Default = 0,
    ET_Classical = 1,
    ET_Jazz = 2,
    ET_Rock = 3,
    ET_Pop = 4,
    ET_Custom = 5,
};
#define EffectType int

typedef enum
{
    LEFT = 0x01,
    RIGHT = 0x2,
}TYPE_VOLUME;

enum AudioSource {
    AS_Idle = 0,
    AS_Music = 1,
    AS_Video = 2,
    AS_Mirror = 3,
    AS_Carplay = 4,
    AS_AV1 = 5,
    AS_AV2 = 6,
    AS_Carlife = 7,
};
#define AudioSource int

class AudioServicePrivate;
class AudioService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioService)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.AudioManager")
public:
    explicit AudioService(QObject* parent = NULL);
    ~AudioService();
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        //    public slots:
        //    void releaseAudioSource(const AudioSource source);
        virtual void requestIncreaseVolume() = 0;
        virtual void requestDecreaseVolume() = 0;
        virtual void requsetIsOpenFM() = 0;
        virtual void requestOpenFM(int open) = 0;
        virtual void requestFMToggle() = 0;
        virtual void requestSetVolume(const int volume) = 0;
        virtual void requestSetFreqency(int freq) = 0;
        //    signals:
        virtual void onFMChange(int freq) = 0;
        virtual void onFMIsOpen(int open) = 0;
        virtual void onVolumeChange(int volume) = 0;
        virtual void onVolumeRangeChange(int min, int max) = 0;
    };
public slots:
    bool requestAudioSource(const int source, const QString &destination, const QString &path, const QString &interface, const QString &method);
    //    bool requestAudioSource(const AudioSource source, const QString &destination, const QString &path, const QString &Interface, const QString &method);
    void releaseAudioSource(const int source);
//    void releaseAudioSource(const AudioSource source);
    void synchronize();
    //    void releaseAudioSource(const AudioSource source);
    void requestIncreaseVolume();
    void requestDecreaseVolume();
    void requsetIsOpenFM();
    void requestOpenFM(int open);
    void requestFMToggle();
    void requestSetVolume(const int volume);
    void requestSetFreqency(int freq);
signals:
    void onFMChange(int freq);
    void onFMIsOpen(int open);
    void onVolumeChange(int volume);
    void onVolumeRangeChange(int min, int max);
private:
    friend class AudioServicePrivate;
    QScopedPointer<AudioServicePrivate> m_Private;
};

#endif // AUDIOSERVICE_H
