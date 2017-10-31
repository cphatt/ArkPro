#include "MusicPlayer.h"
#include "DeviceWatcher/DeviceWatcher.h"
#include "AutoConnect.h"
#include "AudioService.h"
#include "Utility.h"
#include <QDBusConnection>
#include <QDebug>
#include <QProcess>
#include <QDir>
#include <QTimer>
#include <QFileInfo>
#include <QDomDocument>

class MusicPlayerPrivate
{
    Q_DISABLE_COPY(MusicPlayerPrivate)
public:
    explicit MusicPlayerPrivate(MusicPlayer *parent);
    ~MusicPlayerPrivate();
    void initialize();
    void connectAllSlots();
    bool requestAudioSource(const AudioSource source);
    void releaseAudioSource(const AudioSource source);
    void playMusicIndex(const DeviceWatcherType type, const int index);
    QList<QString>& getPathList(const DeviceWatcherType type);
    void seekToMillesimal(const int millesimal);
    void setPlayStatus(const MusicPlayerPlayStatus status);
    void setPlayMode(const MusicPlayerPlayMode mode);
    void startHandler(const QString& output);
    void timeLengthHandler(const QString &output);
    void positionHandelr(const QString& output);
    void timePositionHandler(const QString &output);
    void quitHandler();
    void endOfFileHandler();
    void exitMusicPlayer();
    void createUSBFileNamesXml();
    void createSDFileNamesXml();
    void musicPlayerSetPlay();
    void musicPlayerSetPause();
    void musicPlayerSetStop();
    void musicPlayerSetExit();
    MusicPlayerPlayMode m_PlayMode;
    MusicPlayerPlayStatus m_PlayStatus;
    QProcess* m_MusicPlayer;
    QTimer* m_PositionTimer;
    QTimer* m_ElapsedTimer;
    QList<QString> m_USBPathList;
    QList<QString> m_SDPathList;
    QString m_USBFileNamesXml;
    QString m_SDFileNamesXml;
    DeviceWatcherType m_DiskType;
    QString m_CurrentFilePath;
    int m_PlayIndex;
    int m_ElapsedTime;
    int m_EndTime;
    bool m_Filter;
private:
    MusicPlayer* m_Parent;
};

static void releaseMusicSource(void* paramater)
{
    qDebug() << "MusicPlayerreleaseAudioSource" << paramater;
    MusicPlayerPrivate* ptr = static_cast<MusicPlayerPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->releaseAudioSource(AS_Music);
    }
}

void MusicPlayer::releaseAudioSource(const AudioSource source)
{
    qDebug() << "MusicPlayer::releaseAudioSource" << source;
    if (AS_Music == source) {
        musicPlayerExit(m_Private->m_DiskType);
        clearOwner();
    }
}

void MusicPlayer::musicPlayerRequestFileNames(const DeviceWatcherType type)
{
    switch (type) {
    case DWT_SDDisk: {
        emit onMusicPlayerFileNames(DWT_SDDisk, m_Private->m_SDFileNamesXml);
        break;
    }
    case DWT_USBDisk: {
        emit onMusicPlayerFileNames(DWT_USBDisk, m_Private->m_USBFileNamesXml);
        break;
    }
    default: {
        break;
    }
    }
}

void MusicPlayer::musicPlayerSetPlayModeToggle()
{
    switch (m_Private->m_PlayMode) {
    case MPPM_AllRepeat: {
        musicPlayerSetPlayMode(MPPM_Shuffle);
        break;
    }
    case MPPM_Shuffle: {
        musicPlayerSetPlayMode(MPPM_RepeatOnce);
        break;
    }
    case MPPM_RepeatOnce:
    default: {
        musicPlayerSetPlayMode(MPPM_AllRepeat);
        break;
    }
    }
}

void MusicPlayer::musicPlayerSetPlayMode(const MusicPlayerPlayMode mode)
{
    m_Private->setPlayMode(mode);
}

void MusicPlayer::musicPlayerSetPlayStatusToggle()
{
    qDebug() << "musicPlayerSetPlayStatusToggle" << m_Private->m_PlayStatus;
    switch (m_Private->m_PlayStatus) {
    case MPPS_Play: {
        musicPlayerSetPlayStatus(MPPS_Pause);
        break;
    }
    case MPPS_Pause:
    default: {
        musicPlayerSetPlayStatus(MPPS_Play);
        break;
    }
    }
}

void MusicPlayer::musicPlayerSetPlayStatus(const MusicPlayerPlayStatus status)
{
    qDebug() << "MusicPlayer::musicPlayerSetPlayStatus" << status;
    switch (status) {
    case MPPS_Play: {
        m_Private->musicPlayerSetPlay();
        break;
    }
    case MPPS_Pause: {
        m_Private->musicPlayerSetPause();
        break;
    }
    case MPPS_Stop: {
        m_Private->musicPlayerSetStop();
        break;
    }
    case MPPS_Exit: {
        break;
    }
    default : {
        break;
    }
    }
}

void MusicPlayer::musicPlayerPlayListViewIndex(const DeviceWatcherType type, const int index)
{
    m_Private->playMusicIndex(type, index);
}

void MusicPlayer::musicPlayerPlayPreviousListViewIndex()
{
    int lastIndex = m_Private->m_PlayIndex;
    if ((lastIndex > 0)
            && (lastIndex <= m_Private->getPathList(m_Private->m_DiskType).size() - 1)) {
        --lastIndex;
    } else {
        lastIndex = m_Private->getPathList(m_Private->m_DiskType).size() - 1;
    }
    musicPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex);
}

void MusicPlayer::musicPlayerPlayNextListViewIndex()
{
    int lastIndex = m_Private->m_PlayIndex;
    if ((lastIndex < (m_Private->getPathList(m_Private->m_DiskType).size() - 1))
            && (lastIndex >= 0)) {
        ++lastIndex;
    } else {
        lastIndex = 0;
    }
    musicPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex);
}

void MusicPlayer::musicPlayerSeekToMillesimal(const int millesimal)
{
    qDebug() << "MusicPlayer::musicPlayerSeekToMillesimal" << millesimal;
    switch (m_Private->m_MusicPlayer->state()) {
    case QProcess::Running: {
        m_Private->seekToMillesimal(millesimal);
        break;
    }
    case QProcess::NotRunning: {
        musicPlayerPlayListViewIndex(m_Private->m_DiskType, m_Private->m_PlayIndex);
        break;
    }
    default: {
        break;
    }
    }
}

void MusicPlayer::musicPlayerExit(const DeviceWatcherType type)
{
    if (type == m_Private->m_DiskType) {
        m_Private->exitMusicPlayer();
    }
}

void MusicPlayer::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "MusicPlayer::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_SDPathList.clear();
            break;
        }
        case DWS_Busy: {
            break;
        }
        case DWS_Ready: {
            m_Private->createSDFileNamesXml();
            musicPlayerRequestFileNames(DWT_SDDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDPathList.clear();
            musicPlayerExit(DWT_SDDisk);
            break;
        }
        default : {
            break;
        }
        }
    } else if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBPathList.clear();
            break;
        }
        case DWS_Busy: {
            break;
        }
        case DWS_Ready: {
            m_Private->createUSBFileNamesXml();
            musicPlayerRequestFileNames(DWT_USBDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBPathList.clear();
            musicPlayerExit(DWT_USBDisk);
            break;
        }
        default : {
            break;
        }
        }
    }
}

void MusicPlayer::onMusicFilePath(const QString &path, const DeviceWatcherType type)
{
    if (DWT_USBDisk == type) {
        m_Private->m_USBPathList.append(path);
    } else if (DWT_SDDisk == type) {
        m_Private->m_SDPathList.append(path);
    }
}

void MusicPlayer::onImageFilePath(const QString &path, const DeviceWatcherType type)
{
}

void MusicPlayer::onVideoFilePath(const QString &path, const DeviceWatcherType type)
{
}

MusicPlayer::MusicPlayer(QObject *parent)
    : QObject(parent)
    , m_Private(new MusicPlayerPrivate(this))
{
}

MusicPlayer::~MusicPlayer()
{
}

MusicPlayerPrivate::MusicPlayerPrivate(MusicPlayer *parent)
    : m_Parent(parent)
{
    m_Filter = false;
    m_DiskType = -1;
    m_PlayIndex = 0;
    m_ElapsedTime = -1;
    m_EndTime = -1;
    m_MusicPlayer = NULL;
    m_PositionTimer = NULL;
    m_ElapsedTimer = NULL;
    m_USBPathList.clear();
    m_SDPathList.clear();
    m_CurrentFilePath.clear();
    m_PlayMode = MPPM_AllRepeat;
    m_PlayStatus = MPPS_Stop;
    m_USBFileNamesXml.clear();
    m_SDFileNamesXml.clear();
    initialize();
    connectAllSlots();
}

MusicPlayerPrivate::~MusicPlayerPrivate()
{
    if (QProcess::NotRunning != m_MusicPlayer->state()) {
        m_MusicPlayer->write("quit\n");
        m_MusicPlayer->waitForBytesWritten();
        m_MusicPlayer->waitForFinished();
    }
}

void MusicPlayerPrivate::initialize()
{
    m_MusicPlayer = new QProcess(m_Parent);
    m_MusicPlayer->setProcessChannelMode(QProcess::MergedChannels);
    m_PositionTimer = new QTimer(m_Parent);
    m_PositionTimer->setSingleShot(false);
    m_PositionTimer->setInterval(333);
    m_ElapsedTimer = new QTimer(m_Parent);
    m_ElapsedTimer->setSingleShot(true);
    m_ElapsedTimer->setInterval(333);
}

void MusicPlayerPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DeviceWatcher, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_MusicPlayer, SIGNAL(started()),
                     m_Parent,      SLOT(onStarted()),
                     type);
    QObject::connect(m_MusicPlayer, SIGNAL(finished(int, QProcess::ExitStatus)),
                     m_Parent,      SLOT(onFinished(int, QProcess::ExitStatus)),
                     type);
    QObject::connect(m_MusicPlayer, SIGNAL(finished(int, QProcess::ExitStatus)),
                     m_Parent,      SLOT(onFinished(int, QProcess::ExitStatus)),
                     type);
    QObject::connect(m_MusicPlayer, SIGNAL(error(QProcess::ProcessError)),
                     m_Parent,      SLOT(onError(QProcess::ProcessError)),
                     type);
    QObject::connect(m_MusicPlayer, SIGNAL(stateChanged(QProcess::ProcessState)),
                     m_Parent,      SLOT(onStateChanged(QProcess::ProcessState)),
                     type);
    QObject::connect(m_MusicPlayer, SIGNAL(readyReadStandardOutput()),
                     m_Parent,      SLOT(onReadyReadStandardOutput()),
                     type);
    QObject::connect(m_MusicPlayer, SIGNAL(readyReadStandardError()),
                     m_Parent,      SLOT(onReadyReadStandardError()),
                     type);
    QObject::connect(m_PositionTimer, SIGNAL(timeout()),
                     m_Parent,        SLOT(onTimeout()),
                     type);
    QObject::connect(m_ElapsedTimer, SIGNAL(timeout()),
                     m_Parent,      SLOT(onTimeout()),
                     type);
}

void MusicPlayerPrivate::releaseAudioSource(const AudioSource source)
{
    qDebug() << "MusicPlayerPrivate::releaseAudioSource" << source;
    m_Parent->releaseAudioSource(source);
    QDBusInterface interface(ArkMicroAudioService,
                             ArkMicroAudioPath,
                             ArkMicroAudioInterface,
                             QDBusConnection::sessionBus());
    if (!interface.isValid()) {
        qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
        exit(EXIT_FAILURE);
    }
    QDBusReply<void> reply = interface.call(ArkMicroAudioRelease,
                                            source);
    if (reply.isValid()) {
        qDebug() << "MusicPlayerPrivate::releaseAudioSource ok!";
    } else {
        qDebug() << "MusicPlayerPrivate::releaseAudioSource fail!";
    }
}

bool MusicPlayerPrivate::requestAudioSource(const AudioSource source)
{
    qDebug() << "MusicPlayerPrivate::requestAudioSource" << source;
    bool flag(true);
    const HANDLER ptr = acquirePreemptiveResource(releaseMusicSource, static_cast<void*>(this));
    if (releaseMusicSource != ptr) {
        QDBusInterface interface(ArkMicroAudioService,
                                 ArkMicroAudioPath,
                                 ArkMicroAudioInterface,
                                 QDBusConnection::sessionBus());
        if (!interface.isValid()) {
            qDebug() << qPrintable(QDBusConnection::sessionBus().lastError().message());
            exit(EXIT_FAILURE);
        }
        QDBusReply<bool> reply = interface.call(ArkMicroAudioRequest,
                                                source,
                                                qApp->applicationName(),
                                                ArkMicroMultimediaPath,
                                                ArkMicroMultimediaInterface,
                                                ArkMicroAudioRelease);
        //在这里申请失败了
        if (reply.isValid()) {
            flag = reply.value();
        } else {
            qDebug() << "MusicPlayerPrivate::requestAudioSource fail!";
            flag = false;
        }
    }
    return flag;
}

void MusicPlayerPrivate::playMusicIndex(const DeviceWatcherType type, const int index)
{
    QList<QString> temp = getPathList(type);
    qDebug() << "onPlayMusic" << index << m_MusicPlayer->state() << temp.size();
    if ((temp.size() > index)
            && (QFile(temp.at(index))).exists()
            && (requestAudioSource(AS_Music))) {
        m_CurrentFilePath = temp.at(index);
        m_DiskType = type;
        m_ElapsedTime = -1;
        m_EndTime = -1;
        m_PlayIndex = index;
        m_Filter = false;
        if (m_PositionTimer->isActive()) {
            m_PositionTimer->stop();
        }
        if (m_ElapsedTimer->isActive()) {
            m_ElapsedTimer->stop();
        }
        if (QProcess::NotRunning != m_MusicPlayer->state()) {
            m_MusicPlayer->write("quit\n");
            m_MusicPlayer->waitForBytesWritten();
            m_MusicPlayer->waitForFinished();
            timePositionHandler(QString(""));
        }
        QString cmd = QString("mplayer");
        QStringList arguments;
        arguments << QString("-slave");
        arguments << QString("-idle");
        arguments << QString("-quiet");
        arguments << QString("-ao");
        arguments << QString("alsa");
        arguments << m_CurrentFilePath;
        m_MusicPlayer->start(cmd, arguments);
        m_MusicPlayer->waitForStarted();
        m_PlayStatus = MPPS_Start;
        emit m_Parent->onMusicPlayerPlayStatus(m_PlayStatus);
        m_ElapsedTimer->start();
        m_PositionTimer->start();
        qDebug() << "start play music";
    }
}

QList<QString> &MusicPlayerPrivate::getPathList(const int type)
{
    switch (type) {
    case DWT_SDDisk: {
        return m_SDPathList;
        break;
    }
    case DWT_USBDisk:
    default: {
        return m_USBPathList;
        break;
    }
    }
}

void MusicPlayerPrivate::seekToMillesimal(const int millesimal)
{
    qDebug() << "seekToMillesimal" << millesimal / 10 << millesimal % 10;
    QString cmd("seek %1.%2% 1\n");
    cmd = cmd.arg(millesimal / 10, 3, 10, QChar(' ')).arg(millesimal % 10, 1, 10, QChar('0'));
    m_MusicPlayer->write(cmd.toLocal8Bit().constData());
    m_MusicPlayer->waitForBytesWritten();
    setPlayStatus(MPPS_Play);
    if (!m_PositionTimer->isActive()) {
        m_PositionTimer->start();
    }
}

void MusicPlayerPrivate::setPlayStatus(const MusicPlayerPlayStatus status)
{
    if (status != m_PlayStatus) {
        m_PlayStatus = status;
    }
    emit m_Parent->onMusicPlayerPlayStatus(m_PlayStatus);
}

void MusicPlayerPrivate::setPlayMode(const MusicPlayerPlayMode mode)
{
    if (mode != m_PlayMode) {
        m_PlayMode = mode;
        emit m_Parent->onMusicPlayerPlayMode(m_PlayMode);
    }
}

void MusicPlayerPrivate::startHandler(const QString &output)
{
    m_ElapsedTime = 0;
    if (-1 == m_EndTime) {
        m_MusicPlayer->write("get_time_length\n");
    }
}

void MusicPlayerPrivate::timeLengthHandler(const QString &output)
{
    int start = output.indexOf(QChar('=')) + 1;
    int end = output.indexOf(QChar('\n'));
    if ((-1 != start)
            && (-1 != end)) {
        m_EndTime = static_cast<int>(output.mid(start, end - start).toFloat());
    } else {
        m_EndTime = 0;
    }
}

void MusicPlayerPrivate::positionHandelr(const QString &output)
{
    m_MusicPlayer->write("get_time_pos\n");
}

void MusicPlayerPrivate::timePositionHandler(const QString &output)
{
    int start = output.indexOf(QChar('=')) + 1;
    int end = output.indexOf(QChar('\n'));
    if ((-1 != start)
            && (-1 != end)) {
        m_ElapsedTime = static_cast<int>(output.mid(start, end - start).toFloat());
    } else {
        m_ElapsedTime = 0;
    }
    int millesimal = 0;
    if (m_EndTime > 0) {
        millesimal = 1000 * m_ElapsedTime / m_EndTime;
    }
    //    if (MPPS_Pause == m_PlayStatus) {
    //        m_PlayStatus = MPPS_Play;
    //        emit m_Parent->onMusicPlayerPlayStatus(m_PlayStatus);
    //    }
    //    if (!m_PositionTimer->isActive()) {
    //        m_PositionTimer->start();
    //    }
    emit m_Parent->onMusicPlayerElapsedInformation(m_ElapsedTime, millesimal);
}

void MusicPlayerPrivate::quitHandler()
{
    m_ElapsedTime = 0;
    emit m_Parent->onMusicPlayerElapsedInformation(m_ElapsedTime, 0);
    setPlayStatus(MPPS_Stop);
}

void MusicPlayerPrivate::endOfFileHandler()
{
    qDebug() << "MusicPlayerPrivate::endOfFileHandler" << m_PlayStatus;
    switch (m_PlayStatus) {
    case MPPS_Pause:
    case MPPS_Play: {
        if (m_PositionTimer->isActive()) {
            m_PositionTimer->stop();
        }
        switch (m_PlayMode) {
        case MPPM_AllRepeat: {
            if ((getPathList(m_DiskType).size() - 1) > m_PlayIndex) {
                ++m_PlayIndex;
            } else {
                m_PlayIndex = 0;
            }
            break;
        }
        case MPPM_RepeatOnce: {
            break;
        }
        case MPPM_Shuffle:
        default : {
            m_PlayIndex = qrand() % getPathList(m_DiskType).size();
            break;
        }
        }
        playMusicIndex(m_DiskType, m_PlayIndex);
        break;
    }
    default: {
        break;
    }
    }
}

void MusicPlayerPrivate::exitMusicPlayer()
{
    MusicPlayerPlayStatus status = MPPS_Stop;
    if (QProcess::NotRunning != m_MusicPlayer->state()) {
        if (m_PositionTimer->isActive()) {
            m_PositionTimer->stop();
        }
        m_MusicPlayer->write("quit\n");
        m_MusicPlayer->waitForBytesWritten();
        m_MusicPlayer->waitForFinished();
        status = MPPS_Exit;
    }
    quitHandler();
    setPlayStatus(status);
}

void MusicPlayerPrivate::createUSBFileNamesXml()
{
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("MusicPlayer")));
    QDomElement root = domDocument.firstChildElement(QString("MusicPlayer"));
    QDomElement fileNames;
    QDomElement info;
    fileNames = domDocument.createElement(QString("USBFileNames"));
    root.appendChild(fileNames);
    m_USBFileNamesXml.clear();
    QFileInfo fileInfo;
    for (int i = 0; i < m_USBPathList.size(); ++i) {
        info = domDocument.createElement(QString("Index:" + QString::number(i)));
        fileNames.appendChild(info);
        fileInfo.setFile(m_USBPathList.at(i));
        info.appendChild(domDocument.createTextNode(fileInfo.fileName()));
    }
    m_USBFileNamesXml = domDocument.toString();
    //            {
    //                QDomDocument document;
    //                document.setContent(domDocument.toString());
    //                QDomElement root = document.documentElement();
    //                if ((!root.isNull())
    //                        && (root.isElement())
    //                        && (QString("MusicPlayer") == root.toElement().tagName())
    //                        && (root.hasChildNodes())) {
    //                    QDomNode node = root.firstChild();
    //                    while (!node.isNull()) {
    //                        if (node.isElement()) {
    //                            QDomElement element = node.toElement();
    //                            if (!element.isNull()) {
    //                                if (QString("FileNames") == element.tagName()) {
    //                                    QDomNodeList nodeList = element.childNodes();
    //                                    for (int i = 0; i < nodeList.size(); ++i) {
    //                                        QDomNode node = nodeList.at(i);
    //                                        if (node.isElement()) {
    //                                            if (!node.toElement().isNull()) {
    //                                                qDebug() << root.toElement().tagName();
    //                                                qDebug() << "Index:" << node.toElement().tagName();
    //                                                qDebug() << "FileNames:" << node.toElement().text();
    //                                            }
    //                                        }
    //                                    }
    //                                }
    //                            }
    //                        }
    //                        node = node.nextSibling();
    //                    }
    //                }
    //            }
}

void MusicPlayerPrivate::createSDFileNamesXml()
{
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("MusicPlayer")));
    QDomElement root = domDocument.firstChildElement(QString("MusicPlayer"));
    QDomElement fileNames;
    QDomElement info;
    fileNames = domDocument.createElement(QString("SDFileNames"));
    root.appendChild(fileNames);
    m_SDFileNamesXml.clear();
    QFileInfo fileInfo;
    for (int i = 0; i < m_SDPathList.size(); ++i) {
        info = domDocument.createElement(QString("Index:" + QString::number(i)));
        fileNames.appendChild(info);
        fileInfo.setFile(m_SDPathList.at(i));
        info.appendChild(domDocument.createTextNode(fileInfo.fileName()));
    }
    m_SDFileNamesXml = domDocument.toString();
    //            {
    //                QDomDocument document;
    //                document.setContent(domDocument.toString());
    //                QDomElement root = document.documentElement();
    //                if ((!root.isNull())
    //                        && (root.isElement())
    //                        && (QString("MusicPlayer") == root.toElement().tagName())
    //                        && (root.hasChildNodes())) {
    //                    QDomNode node = root.firstChild();
    //                    while (!node.isNull()) {
    //                        if (node.isElement()) {
    //                            QDomElement element = node.toElement();
    //                            if (!element.isNull()) {
    //                                if (QString("FileNames") == element.tagName()) {
    //                                    QDomNodeList nodeList = element.childNodes();
    //                                    for (int i = 0; i < nodeList.size(); ++i) {
    //                                        QDomNode node = nodeList.at(i);
    //                                        if (node.isElement()) {
    //                                            if (!node.toElement().isNull()) {
    //                                                qDebug() << root.toElement().tagName();
    //                                                qDebug() << "Index:" << node.toElement().tagName();
    //                                                qDebug() << "FileNames:" << node.toElement().text();
    //                                            }
    //                                        }
    //                                    }
    //                                }
    //                            }
    //                        }
    //                        node = node.nextSibling();
    //                    }
    //                }
    //            }
}

void MusicPlayerPrivate::musicPlayerSetPlay()
{
    switch (m_PlayStatus) {
    case MPPS_Stop: {
        playMusicIndex(m_DiskType, m_PlayIndex);
        break;
    }
    case MPPS_Pause: {
        if (!m_PositionTimer->isActive()) {
            m_PositionTimer->start();
        }
        m_MusicPlayer->write("pause\n");
        setPlayStatus(MPPS_Play);
        break;
    }
    default: {
        break;
    }
    }
}

void MusicPlayerPrivate::musicPlayerSetPause()
{
    switch (m_PlayStatus) {
    case MPPS_Play: {
        m_MusicPlayer->write("pause\n");
    }
    case MPPS_Pause: {
        break;
    }
    default: {
        return ;
        break;
    }
    }
    if (m_PositionTimer->isActive()) {
        m_PositionTimer->stop();
    }
    setPlayStatus(MPPS_Pause);
}

void MusicPlayerPrivate::musicPlayerSetStop()
{
    m_MusicPlayer->write("quit\n");
    m_ElapsedTime = 0;
    emit m_Parent->onMusicPlayerElapsedInformation(m_ElapsedTime, 0);
    setPlayStatus(MPPS_Stop);
}

void MusicPlayerPrivate::musicPlayerSetExit()
{

}

void MusicPlayer::onReadyReadStandardOutput()
{
    while (m_Private->m_MusicPlayer->canReadLine()) {
        QString output(m_Private->m_MusicPlayer->readLine());
        //        qDebug() << "onReadyReadStandardOutput" << output;
        if (output.contains("Starting playback...")) {
            m_Private->startHandler(output);
        }/* else if (output.contains(QString("Position:"))) {
                        m_Private->positionHandelr(output);
        } */else if (output.contains(QString("ANS_LENGTH="))) {
            m_Private->timeLengthHandler(output);
        } else if (output.contains(QString("ANS_TIME_POSITION="))) {
            m_Private->timePositionHandler(output);
        } else if (output.contains(QString("Exiting... (End of file)\n"))) {
            m_Private->endOfFileHandler();
        } else if (output.contains(QString("Exiting... (Quit)\n"))) {
            m_Private->quitHandler();
        }
    }
}

void MusicPlayer::onReadyReadStandardError()
{
    qDebug() << "MusicPlayer::onReadyReadStandardError";
}

void MusicPlayer::onTimeout()
{
    QTimer* ptr = static_cast<QTimer*>(sender());
    if (ptr == m_Private->m_PositionTimer) {
        if (QProcess::Running == m_Private->m_MusicPlayer->state()) {
            m_Private->m_MusicPlayer->write("get_time_pos\n");
        }
        if ((!m_Private->m_Filter)) {
            if ((-1 != m_Private->m_EndTime)
                    && (-1 != m_Private->m_ElapsedTime)) {
                m_Private->m_Filter = true;
                QFileInfo fileInfo(m_Private->m_CurrentFilePath);
                emit onMusicPlayerID3TagChange(m_Private->m_DiskType,
                                                m_Private->m_PlayIndex,
                                               fileInfo.fileName(),
                                               m_Private->m_EndTime);
                if (!m_Private->m_ElapsedTimer->isActive()) {
                    m_Private->m_PlayStatus = MPPS_Play;
                    emit onMusicPlayerPlayStatus(m_Private->m_PlayStatus);
                    emit onMusicPlayerPlayMode(m_Private->m_PlayMode);
                }
            }
        }
    }  else if (ptr == m_Private->m_ElapsedTimer) {
        if (m_Private->m_Filter) {
            m_Private->m_PlayStatus = MPPS_Play;
            emit onMusicPlayerPlayStatus(m_Private->m_PlayStatus);
            emit onMusicPlayerPlayMode(m_Private->m_PlayMode);
        }
    }
}

void MusicPlayer::onStarted()
{
    qDebug() << "MusicPlayer::onStarted";
}

void MusicPlayer::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "MusicPlayer::onFinished" << exitCode << exitStatus;
}

void MusicPlayer::onError(QProcess::ProcessError error)
{
    qDebug() << "MusicPlayer::onError" << error;
}

void MusicPlayer::onStateChanged(QProcess::ProcessState state)
{
    qDebug() << "MusicPlayer::onStateChanged" << state;
}
