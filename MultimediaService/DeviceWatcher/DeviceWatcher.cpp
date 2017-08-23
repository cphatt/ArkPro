#include "DeviceWatcher.h"
#include "MusicPlayer/MusicPlayer.h"
#include "DiskScanner/DiskScanner.h"
#include <QDebug>
#include <QDir>
#include <QRegExp>

#ifndef gcc
static const QString mountUSBPath("/media/udisk");
static const QString mountSDPath("/media/sdisk");
#else
static const QString usbPath("/home/user/Music/USB");
static const QString sdPath("/home/user/Music/SD");
#endif

class DeviceWatcherPrivate
{
    Q_DISABLE_COPY(DeviceWatcherPrivate)
public:
    explicit DeviceWatcherPrivate(DeviceWatcher *parent);
    ~DeviceWatcherPrivate();
    void initialize();
    void connectAllSlots();
    void diskDeviceAdd(const QString &path);
    void diskDeviceRemove(const QString &path);
    void usbDiskScan(const QString &path);
    void usbDiskCancelScan(const QString &path);
    void sdDiskScan(const QString &path);
    void sdDiskCancelScan(const QString &path);
    bool regExpUSBPath(const QString& path);
    bool regExpSDPath(const QString& path);
    DiskScanner* m_USBDiskScanner;
    DiskScanner* m_SDDiskScanner;
    DiskDeviceWatcher* m_DiskDeviceWatcher;
    QString m_USBDiskPath;
    QString m_SDDiskPath;
    DeviceWatcherStatus m_USBDiskStatus;
    DeviceWatcherStatus m_SDDiskStatus;
private:
    DeviceWatcher* m_Parent;
};

DeviceWatcher::DeviceWatcher(QObject *parent)
    : QObject(parent)
    , m_Private(new DeviceWatcherPrivate(this))
{
}

DeviceWatcher::~DeviceWatcher()
{
}

void DeviceWatcher::synchronize()
{
    qDebug() << "DeviceWatcher::synchronize";
    deviceWatcherCheckStatus(DWT_SDDisk);
    deviceWatcherCheckStatus(DWT_USBDisk);
}

void DeviceWatcher::deviceWatcherCheckStatus(const int type)
{
    qDebug() << "deviceWatcherCheckStatus" << type;
    switch (type) {
    case DWT_SDDisk: {
        emit onDeviceWatcherStatus(DWT_SDDisk, m_Private->m_SDDiskStatus);
        break;
    }
    case DWT_USBDisk: {
        emit onDeviceWatcherStatus(DWT_USBDisk, m_Private->m_USBDiskStatus);
        break;
    }
    default: {
        break;
    }
    }
}

#ifdef gcc
void DeviceWatcher::usbToggle(const int action)
{
    if (0 == action) {
        onDiskDeviceChange(usbPath, DiskDeviceWatcher::A_Add);
    } else {
        onDiskDeviceChange(usbPath, DiskDeviceWatcher::A_Remove);
    }
}

void DeviceWatcher::sdToggle(const int action)
{
    if (0 == action) {
        onDiskDeviceChange(sdPath, DiskDeviceWatcher::A_Add);
    } else {
        onDiskDeviceChange(sdPath, DiskDeviceWatcher::A_Remove);
    }
}
#endif

void DeviceWatcher::timerEvent(QTimerEvent *event)
{
    qDebug() << "DeviceWatcher::timerEvent";
    killTimer(event->timerId());
#ifdef gcc
    bool sdExsits(false);
    bool usbExists(false);
    if (QFile::exists(sdPath)) {
        sdExsits = true;
        onDiskDeviceChange(sdPath, DiskDeviceWatcher::A_Add);
    }
    if (QFile::exists(usbPath)) {
        usbExists = true;
        onDiskDeviceChange(usbPath, DiskDeviceWatcher::A_Add);
    }
#else
    QDir dir("/dev/");
    dir.setFilter(QDir::System | QDir::NoDotAndDotDot);
    QFileInfoList fileInfoList = dir.entryInfoList();
    bool sdExsits(false);
    bool usbExists(false);
    for (QFileInfoList::iterator fileIter = fileInfoList.begin(); fileIter != fileInfoList.end(); ++fileIter) {
        if ((!sdExsits) && (m_Private->regExpSDPath(fileIter->filePath()))) {
            //qDebug() << fileIter->filePath();
            sdExsits = true;
            onDiskDeviceChange(fileIter->filePath(), DiskDeviceWatcher::A_Add);
        } else if ((!usbExists) && (m_Private->regExpUSBPath(fileIter->filePath()))) {
           // qDebug() << fileIter->filePath();
            usbExists = true;
            onDiskDeviceChange(fileIter->filePath(), DiskDeviceWatcher::A_Add);
        }
        if (sdExsits && usbExists) {
            break;
        }
    }
#endif
    QObject::timerEvent(event);
}

DeviceWatcherPrivate::DeviceWatcherPrivate(DeviceWatcher *parent)
    : m_Parent(parent)
{
    m_USBDiskScanner = NULL;
    m_SDDiskScanner = NULL;
    m_USBDiskPath.clear();
    m_SDDiskPath.clear();
    m_USBDiskStatus = DWS_Empty ;
    m_SDDiskStatus = DWS_Empty;
    m_DiskDeviceWatcher = NULL;
    initialize();
    connectAllSlots();
    m_Parent->startTimer(0);
}

DeviceWatcherPrivate::~DeviceWatcherPrivate()
{
}

void DeviceWatcherPrivate::initialize()
{
    QStringList m_MusicSuffix;
    m_MusicSuffix.clear();
    m_MusicSuffix.append(QString("MP3"));
    m_MusicSuffix.append(QString("WMA"));
    m_MusicSuffix.append(QString("M4A"));
    m_MusicSuffix.append(QString("FLAC"));
    m_MusicSuffix.append(QString("OGG"));
    m_MusicSuffix.append(QString("AC3"));
    m_MusicSuffix.append(QString("WAV"));
    QStringList m_ImageSuffix;
    m_ImageSuffix.clear();
    m_ImageSuffix.append(QString("JPG"));
    m_ImageSuffix.append(QString("BMP"));
    m_ImageSuffix.append(QString("JPEG"));
    m_ImageSuffix.append(QString("PNG"));
//    m_ImageSuffix.append(QString("GIF"));
    QStringList m_VideoSuffix;
    m_VideoSuffix.clear();
    m_VideoSuffix.append(QString("AVI"));
    m_VideoSuffix.append(QString("MP4"));
    m_VideoSuffix.append(QString("MPG"));
    m_VideoSuffix.append(QString("M4V"));
    m_VideoSuffix.append(QString("MKV"));
    m_VideoSuffix.append(QString("3GP"));
    m_VideoSuffix.append(QString("ASF"));
    m_VideoSuffix.append(QString("MOV"));
    m_VideoSuffix.append(QString("MPEG"));
    m_VideoSuffix.append(QString("VOB"));
    m_VideoSuffix.append(QString("TS"));
    m_VideoSuffix.append(QString("WMV"));
    m_VideoSuffix.append(QString("RM"));
    m_VideoSuffix.append(QString("RMVB"));
    m_VideoSuffix.append(QString("DIVX"));

    m_USBDiskScanner = new DiskScanner(m_Parent);
    m_USBDiskScanner->setMinimumScanTime(1500);
    QMap<int, QStringList> map;
    map.insert(0, m_MusicSuffix);
    map.insert(1, m_ImageSuffix);
    map.insert(2, m_VideoSuffix);
    m_USBDiskScanner->setScannerSuffixMap(map);

    m_SDDiskScanner = new DiskScanner(m_Parent);
    m_SDDiskScanner->setMinimumScanTime(1500);
    map.insert(0, m_MusicSuffix);
    map.insert(1, m_ImageSuffix);
    map.insert(2, m_VideoSuffix);
    m_SDDiskScanner->setScannerSuffixMap(map);

    m_USBDiskPath.clear();
    m_SDDiskPath.clear();
    m_DiskDeviceWatcher = new DiskDeviceWatcher(m_Parent);
}

void DeviceWatcherPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_DiskDeviceWatcher, SIGNAL(diskDeviceChange(const QString &, const DiskDeviceWatcher::Action)),
                     m_Parent,            SLOT(onDiskDeviceChange(const QString &, const DiskDeviceWatcher::Action)),
                     type);
    QObject::connect(m_USBDiskScanner, SIGNAL(filePath(const QString &, const int)),
                     m_Parent,         SLOT(onUSBFilePath(const QString &, const int)),
                     type);
    QObject::connect(m_USBDiskScanner, SIGNAL(finish()),
                     m_Parent,         SLOT(onFinish()),
                     type);
    QObject::connect(m_SDDiskScanner, SIGNAL(filePath(const QString &, const int)),
                     m_Parent,        SLOT(onSDFilePath(const QString &, const int)),
                     type);
    QObject::connect(m_SDDiskScanner, SIGNAL(finish()),
                     m_Parent,        SLOT(onFinish()),
                     type);
}

void DeviceWatcherPrivate::diskDeviceAdd(const QString &path)
{
    qDebug() << "diskDeviceAdd" << path << m_USBDiskPath << m_SDDiskPath;
    if (regExpUSBPath(path)) {
        if (m_USBDiskPath.isEmpty()
                && QFile::exists(path)) {
#ifdef gcc
            QString mountUSBPath(path);
#else
            if (!QFile::exists(mountUSBPath)) {
                system("mkdir -p /media/udisk");
            }

            QString command = QString(" mount ") + path + QString(" -o utf8=1 ") + mountUSBPath;
            int ret = system(command.toLocal8Bit().constData());
            if (0 == ret) {
#endif
                m_USBDiskPath = path;
                usbDiskScan(mountUSBPath);
#ifndef gcc
            } else {
                qCritical() << "mount usb failed!!!!!1";
            }
#endif
        }
    } else if (regExpSDPath(path)) {
        if (m_SDDiskPath.isEmpty()
                && QFile::exists(path)) {
#ifdef gcc
            QString mountSDPath(path);
#else
            if (!QFile::exists(mountSDPath)) {
                system("mkdir -p /media/sdisk");
            }
            QString command = QString(" mount ") + path + QString(" -o utf8=1 ") + mountSDPath;
            int ret = system(command.toLocal8Bit().constData());
            if (0 == ret) {
#endif
                m_SDDiskPath = path;
                sdDiskScan(mountSDPath);
#ifndef gcc
            } else {
                qCritical() << "mount sd failed!!!!!1";
            }
#endif
        }
    } else {
        qDebug() << "add other device!";
    }
}

void DeviceWatcherPrivate::diskDeviceRemove(const QString &path)
{
    qDebug() << "diskDeviceRemove" << path << m_USBDiskPath << m_SDDiskPath;
    if (m_USBDiskPath == path) {
#ifndef gcc
        if (!QFile::exists(path)) {
#else
        QString mountUSBPath(path);
#endif
#ifndef gcc
            QString command = QString(" umount -l ") + mountUSBPath;
            int ret = system(command.toLocal8Bit().constData());
            if (0 == ret) {
#endif
                usbDiskCancelScan(mountUSBPath);
#ifndef gcc
            } else {
                qCritical() << "umount usb failed!!!!";
            }
        }
#endif
    } else if (m_SDDiskPath == path) {
#ifndef gcc
        if (!QFile::exists(path)) {
#else
            QString mountSDPath(path);
#endif
#ifndef gcc
            QString command = QString(" umount -l ") + mountSDPath;
            int ret = system(command.toLocal8Bit().constData());
            if (0 == ret) {
#endif
                sdDiskCancelScan(mountSDPath);
#ifndef gcc
            } else {
                qCritical() << "umount sd failed!!!!";
            }
        }
#endif
    } else {
        qDebug() << "remove other device!";
    }
}

void DeviceWatcherPrivate::usbDiskScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::usbDiskScan" << path;
    m_USBDiskStatus = DWS_Busy;
    emit m_Parent->onDeviceWatcherStatus(DWT_USBDisk, m_USBDiskStatus);
    m_USBDiskScanner->startScanner(path);
}

void DeviceWatcherPrivate::usbDiskCancelScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::usbDiskCancelScan" << path;
    m_USBDiskStatus = DWS_Remove;
    emit m_Parent->onDeviceWatcherStatus(DWT_USBDisk, m_USBDiskStatus);
    m_USBDiskPath.clear();
    m_USBDiskScanner->stopScanner();
    m_USBDiskStatus = DWS_Empty;
}

void DeviceWatcherPrivate::sdDiskScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::sdDiskScan" << path;
    m_SDDiskStatus = DWS_Busy;
    emit m_Parent->onDeviceWatcherStatus(DWT_SDDisk, m_SDDiskStatus);
    m_SDDiskScanner->startScanner(path);
}

void DeviceWatcherPrivate::sdDiskCancelScan(const QString &path)
{
    qDebug() << "DeviceWatcherPrivate::sdDiskCancelScan" << path;
    m_SDDiskStatus = DWS_Remove;
    emit m_Parent->onDeviceWatcherStatus(DWT_SDDisk, m_SDDiskStatus);
    m_SDDiskPath.clear();
    m_SDDiskScanner->stopScanner();
    m_SDDiskStatus = DWS_Empty;
}

bool DeviceWatcherPrivate::regExpUSBPath(const QString &path)
{
#ifndef gcc
    QRegExp usbRegExp("^/dev/sd[a-z][0-9]");
    return usbRegExp.exactMatch(path);
#else
    if (path.contains("USB")) {
        return true;
    } else {
        return false;
    }
#endif
}


bool DeviceWatcherPrivate::regExpSDPath(const QString &path)
{
#ifndef gcc
    QRegExp sdRegExp("^/dev/mmcblk[0-9]p[0-9]");
    return sdRegExp.exactMatch(path);
#else
    if (path.contains("SD")) {
        return true;
    } else {
        return false;
    }
#endif
}

void DeviceWatcher::onDiskDeviceChange(const QString &device, const DiskDeviceWatcher::Action action)
{
    qDebug() << "DeviceWatcher::onDiskDeviceChange" << device << action;
    switch (action) {
    case DiskDeviceWatcher::A_Add: {
        m_Private->diskDeviceAdd(device);
        break;
    }
    case DiskDeviceWatcher::A_Remove: {
        m_Private->diskDeviceRemove(device);
        break;
    }
    default: {
        break;
    }
    }
}

void DeviceWatcher::onUSBFilePath(const QString &path, const int index)
{
    switch(index) {
    case 0: {
        emit onMusicFilePath(path, DWT_USBDisk);
        break;
    }
    case 1: {
        emit onImageFilePath(path, DWT_USBDisk);
        break;
    }
    case 2: {
        emit onVideoFilePath(path, DWT_USBDisk);
        break;
    }
    default: {
        break;
    }
    }
}

void DeviceWatcher::onSDFilePath(const QString &path, const int index)
{
    switch(index) {
    case 0: {
        emit onMusicFilePath(path, DWT_SDDisk);
        break;
    }
    case 1: {
        emit onImageFilePath(path, DWT_SDDisk);
        break;
    }
    case 2: {
        emit onVideoFilePath(path, DWT_SDDisk);
        break;
    }
    default: {
        break;
    }
    }
}

void DeviceWatcher::onFinish()
{
    if (sender() == m_Private->m_USBDiskScanner) {
        qDebug() << "USB::onFinish";
        m_Private->m_USBDiskStatus = DWS_Ready;
        emit onDeviceWatcherStatus(DWT_USBDisk, m_Private->m_USBDiskStatus);
    } else if (sender() == m_Private->m_SDDiskScanner) {
        qDebug() << "SD::onFinish";
        m_Private->m_SDDiskStatus = DWS_Ready;
        emit onDeviceWatcherStatus(DWT_SDDisk, m_Private->m_SDDiskStatus);
    }
}
