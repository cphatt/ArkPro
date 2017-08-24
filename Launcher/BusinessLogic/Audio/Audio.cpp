#include "Audio.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "AudioServiceProxy.h"
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>

class AudioPrivate
{
public:
    explicit AudioPrivate(Audio* parent);
    ~AudioPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    Local::DbusServer::AudioManager* m_AudioManagerProxy;
private:
    Audio* m_Parent;
};

void Audio::requestIncreaseVolume()
{
    qDebug() << "Audio::requestIncreaseVolume";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestIncreaseVolume();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestDecreaseVolume()
{
    qDebug() << "Audio::requestDecreaseVolume";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestDecreaseVolume();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requsetIsOpenFM()
{
    qDebug() << "Audio::requsetIsOpenFM";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requsetIsOpenFM();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestOpenFM(int open)
{
    qDebug() << "Audio::requestOpenFM";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestOpenFM(open);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestFMToggle()
{
    qDebug() << "Audio::requestFMToggle";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestFMToggle();
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestSetVolume(const int volume)
{
    qDebug() << "Audio::requestSetVolume";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestSetVolume(volume);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::requestSetFreqency(int freq)
{
    qDebug() << "AudioManager::requestSetFreqency";
    QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->requestSetFreqency(freq);
    reply.waitForFinished();
    qDebug() << "m_Private->m_AudioManagerProxy" << reply.isFinished();
    if (reply.isError()) {
        qDebug() << "method call customEvent failed" << reply.error();
    }
}

void Audio::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        g_EventEngine->detachCustomEvent(this);
        m_Private->initialize();
        m_Private->connectAllSlots();
        onServiceUnregistered(ArkMicroAudioService);
        break;
    }
    default: {
        break;
    }
    }
    QObject::customEvent(event);
}

void Audio::onServiceRegistered(const QString &service)
{
    qDebug() << "Audio::onServiceRegistered" << service;
    if (ArkMicroAudioService == service) {
        if (NULL != m_Private->m_AudioManagerProxy) {
            QDBusPendingReply<> reply = m_Private->m_AudioManagerProxy->synchronize();
#ifdef gcc
            reply.waitForFinished();
            qDebug() << "Dbus call m_AudioManagerProxy synchronize" << reply.isFinished();
            if (reply.isError()) {
                qDebug() << "method call AudioManagerProxy synchronize failed" << reply.error();
            }
#endif
        }
    }
}

void Audio::onServiceUnregistered(const QString &service)
{
    qDebug() << "Audio::onServiceUnregistered" << service;
    if (ArkMicroAudioService == service) {
#ifdef gcc
        g_DbusService->addWatchedService(ArkMicroAudioService);
        QStringList cmd;
        cmd << QString("-t") << AudioApplication;
        bool ret = QProcess::startDetached(qApp->applicationFilePath(), cmd);
        qDebug() << "start" << ArkMicroAudioService << ret;
#else
        g_DbusService->startService(ArkMicroAudioService);
#endif
    }
}

Audio::Audio(QObject *parent)
    : QObject(parent)
    , AudioService::Interface()
    , DbusService::Interface()
    , m_Private(new AudioPrivate(this))
{
    qDebug() << "Audio::Audio";
}

Audio::~Audio()
{
}

AudioPrivate::AudioPrivate(Audio *parent)
    : m_Parent(parent)
{
    m_AudioManagerProxy = NULL;
    receiveAllCustomEvent();
}

AudioPrivate::~AudioPrivate()
{
    system("kill  `ps -elf | grep Launcher | grep audiomanager | awk '{print $4}'`");
}

void AudioPrivate::initialize()
{
    m_AudioManagerProxy = new Local::DbusServer::AudioManager(ArkMicroAudioService,
                                                              ArkMicroAudioPath,
                                                              QDBusConnection::sessionBus(),
                                                              m_Parent);
}

void AudioPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void AudioPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DbusService, m_Parent);
    connectSignalAndSignalByNamesake(m_AudioManagerProxy, m_Parent);
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          ArkMicroAudioInterface,
                                          QString("onVolumeChange"),
                                          m_Parent,
                                          SIGNAL(onVolumeChange(const int, const int)));
    QDBusConnection::sessionBus().connect(QString(),
                                          QString(),
                                          ArkMicroAudioInterface,
                                          QString("onFMIsOpen"),
                                          m_Parent,
                                          SIGNAL(onFMIsOpen(int)));
}
