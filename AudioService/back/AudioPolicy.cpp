#include "AudioPolicy.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDBusConnection>
#include <QStringList>
#include <QDBusMessage>

class AudioPolicyPrivate
{
public:
    explicit AudioPolicyPrivate(AudioPolicy* parent);
    ~AudioPolicyPrivate();
    void initialize();
    void connectAllSlots();
    QString m_Destinattion;
    QString m_Path;
    QString m_Interface;
    QString m_Method;
    AudioSource m_AudioSource;
private:
    AudioPolicy* m_Parent;
};

AudioPolicy::AudioPolicy(QObject *parent)
    : QObject(parent)
    , m_Private(new AudioPolicyPrivate(this))
{
}

AudioPolicy::~AudioPolicy()
{
}

bool AudioPolicy::requestAudioSource(const AudioSource source, const QString &destination, const QString &path, const QString &interface, const QString &method)
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

void AudioPolicy::releaseAudioSource(const int source)
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


AudioPolicyPrivate::AudioPolicyPrivate(AudioPolicy *parent)
    : m_Parent(parent)
{
    m_AudioSource = AS_Idle;
    m_Destinattion.clear();
    m_Path.clear();
    m_Interface.clear();
    m_Method.clear();
    initialize();
    connectAllSlots();
}

AudioPolicyPrivate::~AudioPolicyPrivate()
{
}

void AudioPolicyPrivate::initialize()
{
    qDebug() << "AudioPolicyPrivate::initialize" << qApp->arguments();
    if (qApp->arguments().contains(AudioPolicyApplication)) {
        bool ret = QDBusConnection::sessionBus().registerService(ArkMicroPolicyService);
        ret = ret && QDBusConnection::sessionBus().registerObject(ArkMicroPolicyPath,
                                                                  m_Parent,
                                                                  QDBusConnection::ExportNonScriptableSlots);
        if (!ret) {
            qCritical() << "AudioPolicyPrivate Register QDbus failed!";
            exit(EXIT_FAILURE);
        }
        qDebug() << "AudioPolicyPrivate Register QDbus ok!";
    } else {
        qDebug() << "AudioPolicyPrivate inner";
    }
}

void AudioPolicyPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
}
