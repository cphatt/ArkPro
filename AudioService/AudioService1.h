#ifndef ALSADBUS_H
#define ALSADBUS_H

#include <QObject>
#include"audioconfig.h"

#define ArkMicroAlsaService     "com.arkmicro.audiomanager"
#define ArkMicroAlsaPath        "/com/arkmicro/audiomanager"
#define ArkMicroAlsaInterface   "Local.DbusServer.AudioManager"

#define VOL_MAX_LEVEL 40
typedef enum
{
    LEFT = 0x01,
    RIGHT = 0x2,
}TYPE_VOLUME;


class AlsaDbus : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AlsaDbus)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.AudioManager")
#define g_Link (AlsaDbus::instance())
public:
    explicit AlsaDbus(QObject *parent = 0);

    ~AlsaDbus();
    inline static AlsaDbus& instance() {
        static AlsaDbus AlsaDbus;
        return AlsaDbus;
    }

    void initialize();

    void sendVolume(const int volume);

    void sendVolumeRange(const int min, const int max);

    void sendFM(const int freq);

    void sendIsOpenFM(int open);

private:
    int	m_nMinVol;
    int	m_nMaxVol;
    int m_nCurVol;

    bool m_bOpenFM;
    int  m_nCurFreq;

    int volume2pos(int volume);
    int pos2volume(int pos/* 0 ~ 40*/);
signals:
    void onVolumeChange(const int volume);

    void onVolumeRangeChange(const int min, const int max);

    void onFMChange(int freq);

    void onFMIsOpen(int open);

public slots:
    void requestStart();

    void synchronize();

    void requestIncreaseVolume();

    void requestDecreaseVolume();

    void requsetIsOpenFM();

    void requestFMToggle();

    void requestOpenFM(int open);


    void requestSetVolume(const int volume);

    void requestSetFreqency(int freq);

//test
    void requestget();
    void requstset(int volume);
};

#endif // ALSADBUS_H

