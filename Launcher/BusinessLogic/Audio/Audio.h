#ifndef AUDIO_H
#define AUDIO_H

#include "AudioService.h"
#include "DbusService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class AudioPrivate;
class Audio
        : public QObject
        , protected AudioService::Interface
        , protected DbusService::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(Audio)
#ifdef g_Audio
#undef g_Audio
#endif
#define g_Audio (Audio::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onFMChange(int freq) = 0;
        virtual void onFMIsOpen(int open) = 0;
        virtual void onVolumeChange(int type, int volume) = 0;
        virtual void onVolumeRangeChange(int min, int max) = 0;
    };
    inline static Audio* instance() {
        static Audio* audio(new Audio(qApp));
        return audio;
    }
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
    void onVolumeChange(int type, int volume);
    void onVolumeRangeChange(int min, int max);
protected:
    void customEvent(QEvent* event);
private slots:
    void onServiceRegistered(const QString& service);
    void onServiceUnregistered(const QString& service);
private:
    explicit Audio(QObject* parent = NULL);
    ~Audio();
    friend class AudioPrivate;
    QScopedPointer<AudioPrivate> m_Private;
};

#endif // AUDIO_H
