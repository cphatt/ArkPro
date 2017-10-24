#include "VideoPlayer.h"
#include "AutoConnect.h"
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
    void playVideoIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height);
    void setPlayStatus(const VideoPlayerPlayStatus status);
    void endTimePositionHandler(const QString &output);
    void timePositionHandler(const QString &output);
    QList<QString>& getPathList(const DeviceWatcherType type);
    void endOfFileHandler();
    void seekToMillesimal(const int millesimal);
    void createSDFileNamesXml();
    void createUSBFileNamesXml();
    void exitVideoPlayer();
    VideoPlayerShowStatus m_ShowStatus;
    VideoPlayerPlayStatus m_PlayStatus;
    QString m_SDFileNamesXml;
    QString m_USBFileNamesXml;
    QList<QString> m_SDPathList;
    QList<QString> m_USBPathList;
    QProcess* m_VideoPlayer;
    QTimer* m_Timer;
    DeviceWatcherType m_DiskType;
    int m_PlayIndex;
    int m_ElapsedTime;
    int m_EndTime;
private:
    VideoPlayer *m_Parent;
};

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
    if (QProcess::NotRunning != m_Private->m_VideoPlayer->state()) {
        if (status != m_Private->m_ShowStatus) {
            m_Private->m_ShowStatus = status;
            emit onVideoPlayerShowStatus(m_Private->m_ShowStatus);
        }
    }
}

void VideoPlayer::videoPlayerSetPlayStatus(const VideoPlayerPlayStatus status)
{
    qDebug() << "VideoPlayer::videoPlayerSetPlayStatus" << m_Private->m_VideoPlayer->state() << m_Private->m_PlayStatus << status;
    if (QProcess::NotRunning != m_Private->m_VideoPlayer->state()) {
        if (status != m_Private->m_PlayStatus) {
            switch (status) {
            case VPPS_Play: {
                if (!m_Private->m_Timer->isActive()) {
                    m_Private->m_Timer->start();
                }
                m_Private->m_VideoPlayer->write("pause\n");
                m_Private->setPlayStatus(status);
                break;
            }
            case VPPS_Pause: {
                if (m_Private->m_Timer->isActive()) {
                    m_Private->m_Timer->stop();
                }
                m_Private->m_VideoPlayer->write("get_time_pos\n");
                m_Private->m_VideoPlayer->write("pause\n");
                m_Private->setPlayStatus(status);
                break;
            }
            case VPPS_Stop: {
                m_Private->exitVideoPlayer();
                m_Private->setPlayStatus(status);
                break;
            }
            default : {
                break;
            }
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
    if ((lastIndex > 0)
            && (lastIndex <= m_Private->m_USBPathList.size() - 1)) {
        --lastIndex;
    } else {
        lastIndex = m_Private->m_USBPathList.size() - 1;
    }
//    videoPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex);
}

void VideoPlayer::videoPlayerPlayNextListViewIndex()
{
    int lastIndex = m_Private->m_PlayIndex;
    if (((lastIndex < (m_Private->m_USBPathList.size() - 1)))
            && (lastIndex >= 0)) {
        ++lastIndex;
    } else {
        lastIndex = 0;
    }
//    videoPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex);
}

void VideoPlayer::videoPlayerSeekToMillesimal(const int millesimal)
{
    if (QProcess::NotRunning != m_Private->m_VideoPlayer->state()) {
        m_Private->seekToMillesimal(millesimal);
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
            videoPlayerSetPlayStatus(VPPS_Stop);
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
            videoPlayerSetPlayStatus(VPPS_Stop);
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

void VideoPlayer::onMplayerOutput()
{
    while (m_Private->m_VideoPlayer->canReadLine()) {
        QString output(m_Private->m_VideoPlayer->readLine());
        //        qDebug() << "VideoPlayeronReadyReadStandardOutput" << output;
        if (output.contains(QString("ANS_LENGTH="))) {
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
    m_Private->m_VideoPlayer->write("get_time_pos\n");
}

void VideoPlayer::onStateChanged(QProcess::ProcessState state)
{
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
    m_PlayStatus = VPPS_Stop;
    m_USBPathList.clear();
    m_SDPathList.clear();
    m_VideoPlayer = NULL;
    m_Timer = NULL;
    m_PlayIndex = 0;
    m_ElapsedTime = 0;
    m_EndTime = 0;
    m_USBFileNamesXml.clear();
    initialize();
    connectAllSlots();
}

VideoPlayerPrivate::~VideoPlayerPrivate()
{
}

void VideoPlayerPrivate::initialize()
{
    m_VideoPlayer = new QProcess(m_Parent);
    m_VideoPlayer->setProcessChannelMode(QProcess::MergedChannels);
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(false);
    m_Timer->setInterval(350);
}

void VideoPlayerPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_DeviceWatcher, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_VideoPlayer, SIGNAL(readyReadStandardOutput()),
                     m_Parent,      SLOT(onMplayerOutput()),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(stateChanged(QProcess::ProcessState)),
                     m_Parent,      SLOT(onStateChanged(QProcess::ProcessState)),
                     type);
    QObject::connect(m_VideoPlayer, SIGNAL(error(QProcess::ProcessError)),
                     m_Parent,      SLOT(onError(QProcess::ProcessError)),
                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

void VideoPlayerPrivate::playVideoIndex(const DeviceWatcherType type, const int index, const int x, const int y, const int width, const int height)
{
    qDebug() << "onPlayMusic" << index << m_VideoPlayer->state();
    QList<QString> temp = getPathList(type);
    if ((temp.size() > index)
            && (QFile(temp.at(index))).exists()) {
        m_DiskType = type;
        m_ElapsedTime = 0;
        m_EndTime = 0;
        m_PlayIndex = index;
        if (m_Timer->isActive()) {
            m_Timer->stop();
        }
        if (QProcess::NotRunning != m_VideoPlayer->state()) {
            m_VideoPlayer->write("quit\n");
            m_VideoPlayer->waitForFinished();
        }
        QString cmd = QString("mplayer");
        QStringList arguments;
        arguments << QString("-slave");
        arguments << QString("-quiet");
        arguments << QString("-geometry");
        arguments << QString("1280x720+0+0");
    #ifndef gcc
        arguments << QString("-vo");
        arguments << QString("customfb");
    #endif
        arguments << QString("-ao");
        arguments << QString("alsa");
        arguments << QString("-cache");
        arguments << QString("4096");
        arguments << temp.at(index);
//        QProcess tempProcess;
//        tempProcess.start(QString(" mplayer -identify -frames 0 -endpos 0 ") + QString(m_USBPathList.at(index)));
//        tempProcess.waitForFinished();
//        endTimePositionHandler(tempProcess.readAllStandardOutput());
        m_VideoPlayer->start(cmd, arguments);
        m_PlayStatus = VPPS_Play;
        emit m_Parent->onVideoPlayerPlayStatus(m_PlayStatus);
        m_Timer->start();
        qDebug() << "startvideo" << cmd << arguments << m_VideoPlayer->canReadLine();
    }
}

void VideoPlayerPrivate::setPlayStatus(const VideoPlayerPlayStatus status)
{
    if (status != m_PlayStatus) {
        m_PlayStatus = status;
        emit m_Parent->onVideoPlayerPlayStatus(status);
    }
}

void VideoPlayerPrivate::endTimePositionHandler(const QString &output)
{
    QString keyWord("ID_LENGTH=");
    int startPos = output.indexOf(keyWord);
    int length = keyWord.length();
    QString endTime;
    endTime.clear();
    if (-1 != startPos) {
        for (int i = 0; i < (output.length() - startPos); ++i) {
            if (QChar('\n') == output.at(startPos + length + i)) {
                m_EndTime = static_cast<int>(endTime.toFloat());
                qDebug() << "m_EndTime" << m_EndTime;
                emit m_Parent->onVideoPlayerInformation(QFileInfo(m_USBPathList.at(m_PlayIndex)).fileName(), m_EndTime);
                break;
            }
            endTime += output.at(startPos + length + i);
        }
    }
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
        //        qDebug() << "millesimal" << millesimal;
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
    if (m_Timer->isActive()) {
        m_Timer->stop();
    }
    if (getPathList(m_DiskType).size() > m_PlayIndex) {
        ++m_PlayIndex;
    } else {
        m_PlayIndex = 0;
    }
//    playVideoIndex(m_DiskType, m_PlayIndex);
}

void VideoPlayerPrivate::seekToMillesimal(const int millesimal)
{
    qDebug() << "seekToMillesimal" << millesimal / 10 << millesimal % 10;
    QString cmd("seek %1.%2% 1\n");
    cmd = cmd.arg(millesimal / 10, 3, 10, QChar(' ')).arg(millesimal % 10, 1, 10, QChar('0'));
    m_VideoPlayer->write(cmd.toLocal8Bit().constData());
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

void VideoPlayerPrivate::exitVideoPlayer()
{
    qDebug() << "exitVideoPlayer" << m_VideoPlayer->state();
    if (QProcess::NotRunning != m_VideoPlayer->state()) {
        m_VideoPlayer->write("quit\n");
        //        m_VideoPlayer->kill();
        m_VideoPlayer->waitForFinished();
        if (m_Timer->isActive()) {
            m_Timer->stop();
        }
    }
}
