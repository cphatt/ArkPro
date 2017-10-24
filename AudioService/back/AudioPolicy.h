#ifndef AUDIOPOLICY_H
#define AUDIOPOLICY_H

#include <QObject>
#include <QScopedPointer>

#define AudioPolicyApplication       QString("-audiopolicy")
#define ArkMicroPolicyService        QString("com.arkmicro.audiopolicy")
#define ArkMicroPolicyPath           QString("/com/arkmicro/audiopolicy")
#define ArkMicroPolicyInterface      QString("Local.DbusServer.AudioPolicy")

class AudioPolicyPrivate;
class AudioPolicy : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioPolicy)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.AudioPolicy")
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
    };
    explicit AudioPolicy(QObject* parent = NULL);
    ~AudioPolicy();
public slots:
    bool requestAudioSource(const int source, const QString &destination, const QString &path, const QString &interface, const QString &method);
    //    bool requestAudioSource(const AudioSource source, const QString &destination, const QString &path, const QString &Interface, const QString &method);
    void releaseAudioSource(const int source);
//    void releaseAudioSource(const AudioSource source);
private:
    friend class AudioPolicyPrivate;
    QScopedPointer<AudioPolicyPrivate> m_Private;
};

#endif // AUDIOPOLICY_H
