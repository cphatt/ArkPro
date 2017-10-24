#include "MusicPlayer.h"
#include "DeviceWatcher/DeviceWatcher.h"
#include "ImagePlayer/ImagePlayer.h"
#include "VideoPlayer/VideoPlayer.h"
#include "ID3TagParser.h"
#include "AutoConnect.h"
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
    void parserID3Tag(const QString &path);
    void playMusicIndex(const DeviceWatcherType type, const int index);
    QList<QString>& getPathList(const DeviceWatcherType type);
    void seekToMillesimal(const int millesimal);
    void setPlayStatus(const MusicPlayerPlayStatus status);
    void setPlayMode(const MusicPlayerPlayMode mode);
    void timePositionHandler(const QString &output);
    void endOfFileHandler();
    void exitMusicPlayer();
    void createUSBFileNamesXml();
    void createSDFileNamesXml();
    MusicPlayerPlayMode m_PlayMode;
    MusicPlayerPlayStatus m_PlayStatus;
    QProcess* m_MusicPlayer;
    QTimer* m_Timer;
    ID3TagParser m_ID3TagParser;
    QList<QString> m_USBPathList;
    QList<QString> m_SDPathList;
    QString m_USBFileNamesXml;
    QString m_SDFileNamesXml;
    DeviceWatcherType m_DiskType;
    int m_PlayIndex;
    int m_ElapsedTime;
    int m_EndTime;
private:
    MusicPlayer* m_Parent;
};

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
    if (QProcess::NotRunning != m_Private->m_MusicPlayer->state()) {
        if (status != m_Private->m_PlayStatus) {
            switch (status) {
            case MPPS_Play: {
                if (!m_Private->m_Timer->isActive()) {
                    m_Private->m_Timer->start();
                }
                m_Private->m_MusicPlayer->write("pause\n");
                m_Private->setPlayStatus(status);
                break;
            }
            case MPPS_Pause: {
                if (m_Private->m_Timer->isActive()) {
                    m_Private->m_Timer->stop();
                }
                m_Private->m_MusicPlayer->write("get_time_pos\n");
                m_Private->m_MusicPlayer->write("pause\n");
                m_Private->setPlayStatus(status);
                break;
            }
            case MPPS_Stop: {
                break;
            }
            default : {
                break;
            }
            }
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
    int listSize = 0;
    if (DWT_SDDisk == m_Private->m_DiskType) {
        listSize = m_Private->m_SDPathList.size();
    } else if (DWT_USBDisk == m_Private->m_DiskType) {
        listSize = m_Private->m_USBPathList.size();
    }
    if ((lastIndex > 0)
            && (lastIndex <= listSize - 1)) {
        --lastIndex;
    } else {
        lastIndex = listSize - 1;
    }
    musicPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex);
}

void MusicPlayer::musicPlayerPlayNextListViewIndex()
{
    int lastIndex = m_Private->m_PlayIndex;
    int listSize = 0;
    if (DWT_SDDisk == m_Private->m_DiskType) {
        listSize = m_Private->m_SDPathList.size();
    } else if (DWT_USBDisk == m_Private->m_DiskType) {
        listSize = m_Private->m_USBPathList.size();
    }
    if (((lastIndex < (listSize - 1)))
            && (lastIndex >= 0)) {
        ++lastIndex;
    } else {
        lastIndex = 0;
    }
    musicPlayerPlayListViewIndex(m_Private->m_DiskType, lastIndex);
}

void MusicPlayer::musicPlayerSeekToMillesimal(const int millesimal)
{
    if (QProcess::NotRunning != m_Private->m_MusicPlayer->state()) {
        m_Private->seekToMillesimal(millesimal);
    }
}

void MusicPlayer::musicPlayerExit(const DeviceWatcherType type)
{
    m_Private->exitMusicPlayer();
}

void MusicPlayer::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
//    connectSignalAndSlotByNamesake(g_ImagePlayer, this);
//    connectSignalAndSlotByNamesake(g_VideoPlayer, this);
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
    m_DiskType = -1;
    m_PlayIndex = 0;
    m_ElapsedTime = 0;
    m_EndTime = 0;
    m_MusicPlayer = NULL;
    m_USBPathList.clear();
    m_SDPathList.clear();
    m_PlayMode = MPPM_AllRepeat;
    m_PlayStatus = MPPS_Stop;
    m_USBFileNamesXml.clear();
    initialize();
    connectAllSlots();
}

MusicPlayerPrivate::~MusicPlayerPrivate()
{
    if (QProcess::NotRunning != m_MusicPlayer->state()) {
        m_MusicPlayer->write("quit\n");
        m_MusicPlayer->waitForFinished();
    }
}

void MusicPlayerPrivate::initialize()
{
    m_MusicPlayer = new QProcess(m_Parent);
    m_MusicPlayer->setProcessChannelMode(QProcess::MergedChannels);
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(false);
    m_Timer->setInterval(100);
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
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

void MusicPlayerPrivate::parserID3Tag(const QString &path)
{
    m_ID3TagParser.parserFilePath(path);
    m_EndTime = m_ID3TagParser.getEndTime();
    emit m_Parent->onMusicPlayerID3TagChange(m_ID3TagParser.getFileName(),
                                             m_ID3TagParser.getTitle(),
                                             m_ID3TagParser.getArtist(),
                                             m_ID3TagParser.getAlbum(),
                                             m_ID3TagParser.getEndTime(),
                                             QByteArray());
}

void MusicPlayerPrivate::playMusicIndex(const DeviceWatcherType type, const int index)
{
    QList<QString> temp = getPathList(type);
    qDebug() << "onPlayMusic" << index << m_MusicPlayer->state() << temp.size();
    if ((temp.size() > index)
            && (QFile(temp.at(index))).exists()) {
        m_DiskType = type;
        m_ElapsedTime = 0;
        m_EndTime = 0;
        m_PlayIndex = index;
        if (m_Timer->isActive()) {
            m_Timer->stop();
        }
        if (QProcess::NotRunning != m_MusicPlayer->state()) {
            m_MusicPlayer->write("quit\n");
            m_MusicPlayer->kill();
            m_MusicPlayer->waitForFinished();
        }
        QString cmd = QString("mplayer");
        QStringList arguments;
        arguments << QString("-slave");
//        arguments << QString("-quiet");
        arguments << QString("-ao");
        arguments << QString("alsa");
        arguments << temp.at(index);
        m_MusicPlayer->start(cmd, arguments);
        m_MusicPlayer->waitForStarted();
        m_PlayStatus = MPPS_Play;
        emit m_Parent->onMusicPlayerPlayStatus(m_PlayStatus);
        emit m_Parent->onMusicPlayerPlayMode(m_PlayMode);
        parserID3Tag(temp.at(index));
        timePositionHandler(QString(""));
        qDebug() << "play start" << cmd << arguments;
        m_Timer->start();
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
    emit m_Parent->onMusicPlayerElapsedInformation(m_ElapsedTime, millesimal);
}

void MusicPlayerPrivate::endOfFileHandler()
{
    m_Timer->stop();
    switch (m_PlayMode) {
    case MPPM_AllRepeat: {
        if (getPathList(m_DiskType).size() > m_PlayIndex) {
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
    playMusicIndex(m_PlayIndex, m_DiskType);
}

void MusicPlayerPrivate::exitMusicPlayer()
{
    if (QProcess::NotRunning != m_MusicPlayer->state()) {
        if (m_Timer->isActive()) {
            m_Timer->stop();
        }
        m_MusicPlayer->write("quit\n");
        //        m_MusicPlayer->kill();
        m_MusicPlayer->waitForFinished();
    }
    setPlayStatus(MPPS_Stop);
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

void MusicPlayer::onReadyReadStandardOutput()
{
    while (m_Private->m_MusicPlayer->canReadLine()) {
        QString output(m_Private->m_MusicPlayer->readLine());
        qDebug() << "onReadyReadStandardOutput" << output;
        if (output.contains(QString("ANS_TIME_POSITION="))) {
            m_Private->timePositionHandler(output);
        } else if (output.contains(QString("Exiting... (End of file)\n"))) {
            m_Private->endOfFileHandler();
        }
    }
}

void MusicPlayer::onReadyReadStandardError()
{

}

void MusicPlayer::onTimeout()
{
    m_Private->m_MusicPlayer->write("get_time_pos\n");
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

void MusicPlayer::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug() << "MusicPlayer::onImagePlayerPlayStatus" << status;
//    if (VPPS_Stop != status) {
//        musicPlayerExit(m_Private->m_DiskType);
//    }
}

void MusicPlayer::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    qDebug() << "MusicPlayer::onVideoPlayerPlayStatus" << status;
//    if (VPPS_Stop != status) {
//        musicPlayerExit(m_Private->m_DiskType);
//    }
}
