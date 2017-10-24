#include "AVEngine.h"
#include <QProcess>
#include <QTimer>
#include <QDebug>

class AVEnginePrivate
{
    Q_DISABLE_COPY(AVEnginePrivate)
public:
    explicit AVEnginePrivate(AVEngine* parent);
    ~AVEnginePrivate();
    void initialize();
    void connectAllSlots();
    QProcess* m_Mplayer;
    QTimer* m_Timer;
    AVEngine::AVStatus m_AVStatus;
private:
    AVEngine* m_Parent;
};

AVEngine::AVEngine(QObject *parent)
    : QObject(parent)
    , m_Private(new AVEnginePrivate(this))
{
}

AVEngine::~AVEngine()
{
}

void AVEngine::seekToMillesimal(const int millesimal)
{
}

void AVEngine::playAVFile(const QString &path)
{
    qDebug() << "path" << path;
    QString cmd = QString("loadfile \"") + path + QString("\"\n");
    qDebug() << "AVEngine::playAVFile" << cmd;
    m_Private->m_Mplayer->write(cmd.toLocal8Bit().constData());
}

void AVEngine::playControl(const AVEngine::AVStatus status)
{
    QString command;
    command.clear();
    switch (status) {
    case AVEngine::AVS_Stop: {
        command = QString("stop\n");
        break;
    }
    case AVEngine::AVS_Play: {
        command = QString("pause\n");
        break;
    }
    case AVEngine::AVS_Pause: {
        command = QString("pause\n");
        break;
    }
    default: {
        break;
    }
    }
    m_Private->m_Mplayer->write(command.toLocal8Bit().constData());
}

void AVEngine::onMplayerOutput()
{
//    qDebug() << "onMplayerOutput" << m_Private->m_Mplayer->canReadLine();
//    while (m_Private->m_Mplayer->canReadLine()) {
//        qDebug() << "onMplayerOutput" << output;
//    }
    QString output(m_Private->m_Mplayer->readLine());
//    qDebug() << "readLine" << output;
    if (output.contains(QString("Starting playback...\n"))) {
        qDebug() << "start";
    } else if (output.contains(QString("  =====  PAUSE  =====\n"))) {
        qDebug() << "pause";
    } else if (output == (QString("\n"))) {
        qDebug() << "stop";
    } else if (output.startsWith(QString("A:"))) {
        qDebug() << "output" << output;
    }
}

void AVEngine::onTimeout()
{
}

AVEnginePrivate::AVEnginePrivate(AVEngine *parent)
    : m_Parent(parent)
{
    m_Mplayer = NULL;
    initialize();
    connectAllSlots();
}

AVEnginePrivate::~AVEnginePrivate()
{
    m_Mplayer->terminate();
    if (!m_Mplayer->waitForFinished()) {
        m_Mplayer->kill();
    }
}

void AVEnginePrivate::initialize()
{
    qDebug() << "void AVEnginePrivate::initialize()";
    m_Mplayer = new QProcess(m_Parent);
//    m_Mplayer->setProcessChannelMode(QProcess::MergedChannels);

    QString cmd = QString("mplayer");
    QStringList arguments;
    arguments << QString("-slave");
//    arguments << QString("-quiet");
    arguments << QString("-idle");
    arguments << QString("-ao");
    arguments << QString("alsa");
#ifdef gcc
    arguments << QString("-vo");
    arguments << QString("fbdev");
#endif
    m_Mplayer->start(cmd, arguments);

    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(false);
    m_Timer->setInterval(250);
}

void AVEnginePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Mplayer, SIGNAL(readyReadStandardOutput()),
                     m_Parent,   SLOT(onMplayerOutput()),
                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}
