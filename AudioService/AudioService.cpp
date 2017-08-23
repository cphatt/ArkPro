#include "AudioService.h"
#include "AudioServiceProxy.h"
#include "AutoConnect.h"
#include <QDBusMessage>
#include <QDebug>

class AudioServicePrivate
{
public:
    explicit AudioServicePrivate(AudioService* parent);
    ~AudioServicePrivate();
    void initialize();
    void synchronize();
    bool m_Toggle;
    int m_CurrentFrequency;
    int m_CurrentVolume;
    QString m_Destinattion;
    QString m_Path;
    QString m_Interface;
    QString m_Method;
    AudioSource m_AudioSource;
private:
    AudioService* m_Parent;
};


AudioService::AudioService(QObject *parent)
    : QObject(parent)
    , m_Private(new AudioServicePrivate(this))
{
}

AudioService::~AudioService()
{

}

bool AudioService::requestAudioSource(const AudioSource source, const QString &destination, const QString &path, const QString &interface, const QString &method)
{
    qDebug() << "AudioPolicy::requestAudioSource" << source << destination << path << interface << method;
    bool flag(flag);
    if (AS_Idle == m_Private->m_AudioSource) {
        m_Private->m_Destinattion = destination;
        m_Private->m_Path = path;
        m_Private->m_Interface = interface;
        m_Private->m_Method = method;
        flag = true;
    } else {
        if (source != m_Private->m_AudioSource) {
            QDBusMessage message = QDBusMessage::createMethodCall(m_Private->m_Destinattion,
                                                                  m_Private->m_Path,
                                                                  m_Private->m_Interface,
                                                                  m_Private->m_Method);
            message << m_Private->m_AudioSource;
            QDBusMessage response = QDBusConnection::sessionBus().call(message);
            qDebug() << response.type() << "MethodCallMessage";
            if (QDBusMessage::ReplyMessage == response.type()) {
                qDebug() << "Release method call ok!";
            }
        }
        m_Private->m_Destinattion = destination;
        m_Private->m_Path = path;
        m_Private->m_Interface = interface;
        m_Private->m_Method = method;
        flag = true;
    }
    m_Private->m_AudioSource = source;
    return flag;
}

void AudioService::releaseAudioSource(const AudioSource source)
{
    qDebug() << "AudioPolicy::releaseAudioSource" << source;
    if (source == m_Private->m_AudioSource) {
        m_Private->m_AudioSource = AS_Idle;
        m_Private->m_Destinattion.clear();
        m_Private->m_Path.clear();
        m_Private->m_Interface.clear();
        m_Private->m_Method.clear();
        qDebug() << "ReleaseAudio success!" << source;
    }
}

void AudioService::synchronize()
{
    m_Private->synchronize();
}

void AudioService::requestIncreaseVolume()
{
    if (m_Private->m_CurrentVolume < 40) {
        ++m_Private->m_CurrentVolume;
    }
    emit onVolumeChange(m_Private->m_CurrentVolume);
}

void AudioService::requestDecreaseVolume()
{
    if (m_Private->m_CurrentVolume > 0) {
        --m_Private->m_CurrentVolume;
    }
    emit onVolumeChange(m_Private->m_CurrentVolume);
}

void AudioService::requsetIsOpenFM()
{
}

void AudioService::requestOpenFM(int open)
{
}

void AudioService::requestFMToggle()
{
    m_Private->m_Toggle = !m_Private->m_Toggle;
    m_Private->synchronize();
}

void AudioService::requestSetVolume(const int volume)
{
    if (volume > 40) {
        m_Private->m_CurrentVolume = 40;
    } else if (volume < 0) {
        m_Private->m_CurrentVolume = 0;
    } else {
        m_Private->m_CurrentVolume = volume;
    }
    m_Private->synchronize();
}

void AudioService::requestSetFreqency(int freq)
{
    m_Private->m_Toggle = true;
    m_Private->m_CurrentFrequency = freq;
    m_Private->synchronize();
}

AudioServicePrivate::AudioServicePrivate(AudioService *parent)
    : m_Parent(parent)
{
    m_Toggle = false;
    m_CurrentFrequency = 885;
    m_CurrentVolume = 20;
    m_AudioSource = AS_Idle;
    m_Destinattion.clear();
    m_Path.clear();
    m_Interface.clear();
    m_Method.clear();
    initialize();
}

AudioServicePrivate::~AudioServicePrivate()
{
    system("kill  `ps -elf | grep Launcher | grep audiopolicy | awk '{print $4}'`");
}

void AudioServicePrivate::initialize()
{
    if (ArkMicroAudioService == qApp->applicationName()) {
        bool ret = QDBusConnection::sessionBus().registerService(ArkMicroAudioService);
        ret = ret && QDBusConnection::sessionBus().registerObject(ArkMicroAudioPath,
                                                                  m_Parent,
                                                                  QDBusConnection::ExportNonScriptableSignals
                                                                  | QDBusConnection::ExportNonScriptableSlots);
        if (!ret) {
            qCritical() << "AudioService Register QDbus failed!";
            exit(EXIT_FAILURE);
        }
        qDebug() << "AudioService Register QDbus ok!";
    }
}

void AudioServicePrivate::synchronize()
{
    int flag(0);
    if (m_Toggle) {
        flag = 1;
        emit m_Parent->onFMChange(m_CurrentFrequency);
    }
    emit m_Parent->onFMIsOpen(flag);
    emit m_Parent->onVolumeChange(m_CurrentVolume);
}
