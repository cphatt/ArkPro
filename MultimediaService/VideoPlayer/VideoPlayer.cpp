#include "VideoPlayer.h"
#include "AutoConnect.h"
#include "AudioService.h"
#include "Utility.h"
#include <QList>
#include <QFileInfo>
#include <QDebug>
#include <QTimer>
#include <QDomDocument>

class VideoPlayerPrivate
{
    Q_DISABLE_COPY(VideoPlayerPrivate)
public:
    explicit VideoPlayerPrivate(VideoPlayer *parent);
    ~VideoPlayerPrivate();
    void initialize();
    void connectAllSlots();
    bool requestAudioSource(const AudioSource source);
    void releaseAudioSource(const AudioSource source);
    void playVideoIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height);
    void setPlayStatus(const VideoPlayerPlayStatus status);
    void startHandler(const QString& output);
    void endTimePositionHandler(const QString &output);
    void timePositionHandler(const QString &output);
    QList<QString>& getPathList(const DeviceWatcherType type);
    void endOfFileHandler();
    void seekToMillesimal(const int millesimal);
    void createSDFileNamesXml();
    void createUSBFileNamesXml();
    void videoPlayerSetPlay();
    void videoPlayerSetPause();
    void exitVideoPlayer();
    VideoPlayerShowStatus m_ShowStatus;
    VideoPlayerPlayStatus m_PlayStatus;
    QString m_SDFileNamesXml;
    QString m_USBFileNamesXml;
    QList<QString> m_SDPathList;
    QList<QString> m_USBPathList;
    QProcess* m_VideoPlayer;
    QTimer* m_PositionTimer;
    QTimer* m_ElapsedTimer;
    DeviceWatcherType m_DiskType;
    int m_PlayIndex;
    int m_ElapsedTime;
    int m_EndTime;
    int m_X;
    int m_Y;
    int m_Width;
    int m_Height;
    bool m_Filter;
private:
    VideoPlayer *m_Parent;
};

static void releaseMusicSource(void* paramater)
{
    qDebug() << "VideoPlayerreleaseMusicSource" << paramater;
    VideoPlayerPrivate* ptr = static_cast<VideoPlayerPrivate*>(paramater);
    if (NULL != ptr) {
        ptr->releaseAudioSource(AS_Video);
    }
}

void VideoPlayer::releaseAudioSource(const AudioSource source)
{
    qDebug() << "VideoPlayer::releaseAudioSource" << source;
    if (AS_Video == source) {
        videoPlayerExit(m_Private->m_DiskType);
        clearOwner();
    }
}

void VideoPlayer::videoPlayerRequestFileNames(const DeviceWatcherType type)
{
    switch (type) {
    case DWT_SDDisk: {
        emit onVideoPlayerFileNames(DWT_SDDisk, m_Private->m_SDFileNamesXml);
        break;
    }
    case DWT_USBDisk: {
        emit onVideoPlayerFileNames(DWT_USBDisk, m_Private->m_USBFileNamesXml);
        break;
    }
    default: {
        break;
    }
    }
}

void VideoPlayer::videoPlayerSetPlayStatusToggle()
{
    switch (m_Private->m_PlayStatus) {
    case VPPS_Play: {
        videoPlayerSetPlayStatus(VPPS_Pause);
        break;
    }
    case VPPS_Pause:
    default: {
        videoPlayerSetPlayStatus(VPPS_Play);
        break;
    }
    }
}

void VideoPlayer::videoPlayerSetShowStatus(const VideoPlayerShowStatus status)
{
    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
        if (status != m_Private->m_ShowStatus) {
            m_Private->m_ShowStatus = status;
            emit onVideoPlayerShowStatus(m_Private->m_ShowStatus);
        }
    }
}

void VideoPlayer::videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status)
{
    qDebug() << "VideoPlayer::videoPlayerSetPlayStatus" << m_Private->m_VideoPlayer->state() << m_Private->m_PlayStatus << status;
    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
        switch (status) {
        case VPPS_Play: {
            m_Private->videoPlayerSetPlay();
            break;
        }
        case VPPS_Pause: {
            m_Private->videoPlayerSetPause();
            break;
        }
        default : {
            break;
        }
        }
    }
}

void VideoPlayer::videoPlayerPlayListViewIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height)
{
    m_Private->playVideoIndex(type, index, x, y, width, height);
}

void VideoPlayer::videoPlayerPlayPreviousListViewIndex()
{
    int lastIndex = m_Private->m_PlayIndex;
    QList<QString> temp = m_Private->getPathList(m_Private->m_DiskType);
    if ((lastIndex > 0)
            && (lastIndex <= temp.size() - 1)) {
        --lastIndex;
    } else {
        lastIndex = temp.size() - 1;
    }
    videoPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex, m_Private->m_X, m_Private->m_Y, m_Private->m_Width, m_Private->m_Height);
}

void VideoPlayer::videoPlayerPlayNextListViewIndex()
{
    int lastIndex = m_Private->m_PlayIndex;
    QList<QString> temp = m_Private->getPathList(m_Private->m_DiskType);
    if (((lastIndex < (temp.size() - 1)))
            && (lastIndex >= 0)) {
        ++lastIndex;
    } else {
        lastIndex = 0;
    }
    videoPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex, m_Private->m_X, m_Private->m_Y, m_Private->m_Width, m_Private->m_Height);
}

void VideoPlayer::videoPlayerSeekToMillesimal(const int millesimal)
{
    if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
        m_Private->seekToMillesimal(millesimal);
    }
}

void VideoPlayer::videoPlayerExit(const DeviceWatcherType type)
{
    qDebug() << "VideoPlayer::videoPlayerExit" << type;
    if (type == m_Private->m_DiskType) {
        m_Private->exitVideoPlayer();
    }
}

void VideoPlayer::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
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
            videoPlayerRequestFileNames(DWT_SDDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDPathList.clear();
            videoPlayerExit(DWT_SDDisk);
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
            videoPlayerRequestFileNames(DWT_USBDisk);
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBPathList.clear();
            videoPlayerSetPlayStatus(VPPS_Exit);
        }
        default : {
            break;
        }
        }
    }
}

void VideoPlayer::onMusicFilePath(const QString &path, const DeviceWatcherType type)
{
}

void VideoPlayer::onImageFilePath(const QString &path, const DeviceWatcherType type)
{
}

void VideoPlayer::onVideoFilePath(const QString &path, const DeviceWatcherType type)
{
    if (type == DWT_USBDisk) {
        m_Private->m_USBPathList.append(path);
    } else if (type == DWT_SDDisk) {
        m_Private->m_SDPathList.append(path);
    }
}

void VideoPlayer::onReadyReadStandardOutput()
{
    while (m_Private->m_VideoPlayer->canReadLine()) {
        QString output(m_Private->m_VideoPlayer->readLine());
        //        qDebug() << "VideoPlayeronReadyReadStandardOutput" << output;
        if (output.contains("Starting playback...")) {
            m_Private->startHandler(output);
        } else if (output.contains(QString("ANS_LENGTH="))) {
            m_Private->endTimePositionHandler(output);
        } else if (output.contains(QString("ANS_TIME_POSITION="))) {
            m_Private->timePositionHandler(output);
        } else if (output.contains(QString("Exiting... (End of file)\n"))) {
            m_Private->endOfFileHandler();
        }
    }
}

void VideoPlayer::onTimeout()
{
    QTimer* ptr = static_cast<QTimer*>(sender());
    if (ptr == m_Private->m_PositionTimer) {
        if (QProcess::Running == m_Private->m_VideoPlayer->state()) {
            m_Private->m_VideoPlayer->write("get_time_pos\n");
        }
        if ((!m_Private->m_Filter)) {
            if ((-1 != m_Private->m_EndTime)
                    && (-1 != m_Private->m_ElapsedTime)) {
                m_Private->m_Filter = true;
                if (!m_Private->m_ElapsedTimer->isActive()) {
                    m_Private->m_PlayStatus = VPPS_Play;
                    emit onVideoPlayerPlayStatus(m_Private->m_PlayStatus);
                }
            }
        }
    }  else if (ptr == m_Private->m_ElapsedTimer) {
        if (m_Private->m_Filter) {
            m_Private->m_PlayStatus = VPPS_Play;
            emit onVideoPlayerPlayStatus(m_Private->m_PlayStatus);
        }
    }
}

void VideoPlayer::onStarted()
{
    qDebug() << "VideoPlayer::onStarted";
}

void VideoPlayer::onFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "VideoPlayer::onFinished" << exitCode << exitStatus;
}

void VideoPlayer::onStateChanged(QProcess::ProcessState state)
{
    qDebug() << "VideoPlayer::onStateChanged" << state;
}

void VideoPlayer::onReadyReadStandardError()
{
    qDebug() << "VideoPlayer::onReadyReadStandardError";
}

void VideoPlayer::onError(QProcess::ProcessError error)
{
    qDebug() << "VideoPlayer::onError" << error;
}

VideoPlayer::VideoPlayer(QObject *parent)
    : QObject(parent)
    , m_Private(new VideoPlayerPrivate(this))
{
}

VideoPlayer::~VideoPlayer()
{
}

VideoPlayerPrivate::VideoPlayerPrivate(VideoPlayer *parent)
    : m_Parent(parent)
{
    m_ShowStatus = VPSS_Normal;
    m_PlayStatus = VPPS_Exit;
    m_USBPathList.clear();
    m_SDPathList.clear();
    m_VideoPlayer = NULL;
    m_PositionTimer = NULL;
    m_ElapsedTimer = NULL;
    m_PlayIndex = -1;
    m_ElapsedTime = -1;
    m_EndTime = -1;
    m_SDFileNamesXml.clear();
    m_USBFileNamesXml.clear();
    m_X = 0;
    m_Y = 0;
    m_Width = 800;
    m_Height = 480;
    m_Filter = false;
    initialize();
    connectAllSlots();
}

VideoPlayerPrivate::~VideoPlayerPrivate()
{
    if (QProcess::NotRunning != m_VideoPlayer->state()) {
        m_VideoPlayer->write("quit\n");
        m_VideoPlayer->waitForBytesWritten();
        m_VideoPlayer->waitForFinished();
    }
}

void VideoPlayerPrivate::initialize()
{
    m_VideoPlayer = new QProcess(m_Parent);
    m_VideoPlayer->setProcessChannelMode(QProcess::MergedChannels);
    m_PositionTimer = new QTimer(m_Parent);
    m_PositionTimer->setSingleShot(false);
    m_PositionTimer->setInterval(333);
    m_ElapsedTimer = new QTimer(m_Parent);
    m_ElapsedTimer->setSingleShot(true);
    m_ElapsedTimer->setInterval(333);
}

void VideoPlayerPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DeviceWatcher, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_VideoPlayer, SIGNAL(started()),
                     m_Parent,      SLOT(onStarted()),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(finished(int, QProcess::ExitStatus)),
                     m_Parent,      SLOT(onFinished(int, QProcess::ExitStatus)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(finished(int, QProcess::ExitStatus)),
                     m_Parent,      SLOT(onFinished(int, QProcess::ExitStatus)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(error(QProcess::ProcessError)),
                     m_Parent,      SLOT(onError(QProcess::ProcessError)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(stateChanged(QProcess::ProcessState)),
                     m_Parent,      SLOT(onStateChanged(QProcess::ProcessState)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(readyReadStandardOutput()),
                     m_Parent,      SLOT(onReadyReadStandardOutput()),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(readyReadStandardError()),
                     m_Parent,      SLOT(onReadyReadStandardError()),
                     type);
    QObject::connect(m_PositionTimer, SIGNAL(timeout()),
                     m_Parent,        SLOT(onTimeout()),
                     type);
    QObject::connect(m_ElapsedTimer, SIGNAL(timeout()),
                     m_Parent,       SLOT(onTimeout()),
                     type);
}

bool VideoPlayerPrivate::requestAudioSource(const AudioSource source)
{
    qDebug() << "VideoPlayerPrivate::requestAudioSource" << source;
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
        qDebug() << "interface.call";
        QDBusReply<bool> reply = interface.call(ArkMicroAudioRequest,
                                                source,
                                                qApp->applicationName(),
                                                ArkMicroMultimediaPath,
                                                ArkMicroMultimediaInterface,
                                                ArkMicroAudioRelease);
        if (reply.isValid()) {
            flag = reply.value();
        } else {
            qDebug() << "VideoPlayerPrivate::requestAudioSource fail!";
            flag = false;
        }
    }
    return flag;
}

void VideoPlayerPrivate::releaseAudioSource(const AudioSource source)
{
    qDebug() << "VideoPlayerPrivate::releaseAudioSource" << source;
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
        qDebug() << "VideoPlayerPrivate::releaseAudioSource ok!";
    } else {
        qDebug() << "VideoPlayerPrivate::releaseAudioSource fail!";
    }
}

void VideoPlayerPrivate::playVideoIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height)
{
    QList<QString> temp = getPathList(type);
    qDebug() << "playVideoIndex" << index << m_VideoPlayer->state() << temp.size();
    if ((temp.size() > index)
            && (QFile(temp.at(index))).exists()
            && (requestAudioSource(AS_Video))) {
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
#ifdef gcc
        m_X = 800;
        m_Y = 480;
        m_Width = 320;
        m_Height = 480;
#else
        m_X = x;
        m_Y = y;
        m_Width = width;
        m_Height = height;
#endif
        if (QProcess::NotRunning != m_VideoPlayer->state()) {
            m_VideoPlayer->write("quit\n");
            m_VideoPlayer->waitForBytesWritten();
            m_VideoPlayer->waitForFinished();
            timePositionHandler(QString(""));
        }
        QString cmd = QString("mplayer");
        QStringList arguments;
        arguments << QString("-slave");
        arguments << QString("-idle");
        //        arguments << QString("-quiet");
        arguments << QString("-geometry");
        arguments << QString(QString::number(m_Width)
                             + QString("x")
                             + QString::number(m_Height)
                             + QString("+")
                             + QString::number(m_X)
                             + QString("+")
                             + QString::number(m_Y));
#ifndef gcc
        arguments << QString("-vo");
        arguments << QString("customfb");
#endif
        arguments << QString("-ao");
        arguments << QString("alsa");
        arguments << QString("-cache");
        arguments << QString("4096");
        arguments << temp.at(index);
        m_VideoPlayer->start(cmd, arguments);
        qDebug() << "cmd" << cmd;
        qDebug() << "arguments" << arguments;
        m_VideoPlayer->waitForStarted();
        m_PlayStatus = VPPS_Start;
        emit m_Parent->onVideoPlayerPlayStatus(m_PlayStatus);
        qDebug() << "emit m_Parent->onVideoPlayerPlayStatus" << m_PlayStatus;
        m_PositionTimer->start();
        m_ElapsedTimer->start();
        qDebug() << "startvideo";
    }
}

void VideoPlayerPrivate::setPlayStatus(const VideoPlayerPlayStatus status)
{
    if (status != m_PlayStatus) {
        m_PlayStatus = status;
    }
    emit m_Parent->onVideoPlayerPlayStatus(status);
}

void VideoPlayerPrivate::startHandler(const QString &output)
{
    m_ElapsedTime = 0;
    if (-1 == m_EndTime) {
        m_VideoPlayer->write("get_time_length\n");
    }
}

void VideoPlayerPrivate::endTimePositionHandler(const QString &output)
{
    qDebug() << "VideoPlayerPrivate::endTimePositionHandler" << output;
    QString keyWord("ANS_LENGTH=");
    int startPos = output.indexOf(keyWord);
    int length = keyWord.length();
    QString endTime;
    endTime.clear();
    QList<QString> temp = getPathList(m_DiskType);
    m_EndTime = 0;
    if (-1 != startPos) {
        for (int i = 0; i < (output.length() - startPos); ++i) {
            if (QChar('\n') == output.at(startPos + length + i)) {
                m_EndTime = static_cast<int>(endTime.toFloat());
                qDebug() << "m_EndTime" << m_EndTime;
                emit m_Parent->onVideoPlayerInformation(m_DiskType, m_PlayIndex, QFileInfo(temp.at(m_PlayIndex)).fileName(), m_EndTime);
                break;
            }
            endTime += output.at(startPos + length + i);
        }
    }
    if (0 == m_EndTime) {
        emit m_Parent->onVideoPlayerInformation(m_DiskType, m_PlayIndex,QFileInfo(temp.at(m_PlayIndex)).fileName(), m_EndTime);
    }
    qDebug() << "m_EndTime" << m_EndTime;
}

void VideoPlayerPrivate::timePositionHandler(const QString &output)
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
    emit m_Parent->onVideoPlayerElapsedInformation(m_ElapsedTime, millesimal);
}

QList<QString> &VideoPlayerPrivate::getPathList(const int type)
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

void VideoPlayerPrivate::endOfFileHandler()
{
    if (m_PositionTimer->isActive()) {
        m_PositionTimer->stop();
    }
    if ((getPathList(m_DiskType).size() - 1) > m_PlayIndex) {
        ++m_PlayIndex;
    } else {
        m_PlayIndex = 0;
    }
    playVideoIndex(m_DiskType, m_PlayIndex, m_X, m_Y, m_Width, m_Height);
}

void VideoPlayerPrivate::seekToMillesimal(const int millesimal)
{
    qDebug() << "seekToMillesimal" << millesimal / 10 << millesimal % 10;
    QString cmd("seek %1.%2% 1\n");
    cmd = cmd.arg(millesimal / 10, 3, 10, QChar(' ')).arg(millesimal % 10, 1, 10, QChar('0'));
    m_VideoPlayer->write(cmd.toLocal8Bit().constData());
    m_VideoPlayer->waitForBytesWritten();
    setPlayStatus(VPPS_Play);
    if (!m_PositionTimer->isActive()) {
        m_PositionTimer->start();
    }
}

void VideoPlayerPrivate::createSDFileNamesXml()
{
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("VideoPlayer")));
    QDomElement root = domDocument.firstChildElement(QString("VideoPlayer"));
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
}

void VideoPlayerPrivate::createUSBFileNamesXml()
{
    QDomDocument domDocument;
    domDocument.clear();
    domDocument.appendChild(domDocument.createElement(QString("VideoPlayer")));
    QDomElement root = domDocument.firstChildElement(QString("VideoPlayer"));
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
}

void VideoPlayerPrivate::videoPlayerSetPlay()
{
    switch (m_PlayStatus) {
    case MPPS_Play: {
        break;
    }
    case MPPS_Pause: {
        m_VideoPlayer->write("pause\n");
        break;
    }
    default: {
        return;
        break;
    }
    }
    if (!m_PositionTimer->isActive()) {
        m_PositionTimer->start();
    }
    setPlayStatus(MPPS_Play);
}

void VideoPlayerPrivate::videoPlayerSetPause()
{
    switch (m_PlayStatus) {
    case MPPS_Play: {
        m_VideoPlayer->write("pause\n");
        break;
    }
    case MPPS_Pause: {
        break;
    }
    default: {
        return;
        break;
    }
    }
    if (m_PositionTimer->isActive()) {
        m_PositionTimer->stop();
    }
    setPlayStatus(MPPS_Pause);
}

void VideoPlayerPrivate::exitVideoPlayer()
{
    qDebug() << "exitVideoPlayer" << m_VideoPlayer->state();
    VideoPlayerPlayStatus status = VPPS_Stop;
    if (QProcess::NotRunning != m_VideoPlayer->state()) {
        if (m_PositionTimer->isActive()) {
            m_PositionTimer->stop();
        }
        m_VideoPlayer->write("quit\n");
        m_VideoPlayer->waitForBytesWritten();
        m_VideoPlayer->waitForFinished();
        status = VPPS_Exit;
    }
    //    quitHandler();
    setPlayStatus(status);
}
