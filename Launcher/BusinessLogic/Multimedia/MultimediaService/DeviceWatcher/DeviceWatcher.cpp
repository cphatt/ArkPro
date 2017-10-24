#include "DeviceWatcher.h"
#include "MusicPlayer/MusicPlayer.h"
#include "DiskScanner/DiskScanner.h"
#include <QDebug>
#include <QDir>
#ifdef gcc
#include <signal.h>
static inline void signalHandler(int signo);
#endif

#ifdef gcc
static const QString mountUSBPath("/tmp/udisk");
static const QString mountSDPath("/tmp/sdisk");
#else
static const QString mountUSBPath("/media/udisk");
static const QString mountSDPath("/media/sdisk");
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
    deviceWatcherCheckStatus(DWT_SDDisk);
    deviceWatcherCheckStatus(DWT_USBDisk);
#ifdef gcc
    //    m_Private->sdDiskScan(QString("/home/user/Music/Pictures"));
    //    m_Private->usbDiskScan(QString("/home/user/Music/CloudMusic"));
#endif
#ifdef gcc
    signal(SIGUSR1, signalHandler);
    signal(SIGUSR2, signalHandler);
#endif
//    if (qApp->arguments().contains(MULTIMEDIAAPPLICATION)) {
//#ifdef gcc
//        system("kill  -10 `ps -elf | grep Launcher | grep multimedia | awk '{print $4}'`");
//#endif
//    } else {
//#ifdef gcc
//        system("kill  -10 `ps -elf | grep Launcher| awk '{print $4}'`");
//#endif
//        qDebug() << "MultimediaService inner";
//    }
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

static int count(0);
void DeviceWatcher::testMount()
{
    ++count;
    qDebug() << "++count" << count;
    m_Private->sdDiskScan(QString("/home/user/Music/Pictures"));
    //    m_Private->usbDiskScan(QString("/home/user/Music/CloudMusic"));
}

void DeviceWatcher::testUnmount()
{
    m_Private->usbDiskScan(QString("/home/user/Music/CloudMusic"));;
    return;
    --count;
    qDebug() << "--count" << count;
    m_Private->sdDiskCancelScan(QString("/home/user/Music/Pictures"));
    m_Private->usbDiskCancelScan(QString("/home/user/Music/CloudMusic"));
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
    m_ImageSuffix.append(QString("GIF"));
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
    if (path.startsWith(QString("/dev/sd"))) {
        QChar lastChar = path.at(path.length() - 1);
        if ((lastChar >= QChar('0'))
                && (lastChar <= QChar('9'))) {
            if (m_USBDiskPath.isEmpty()
                    && QFile::exists(path)) {
                if (!QFile::exists(mountUSBPath)) {
#ifdef gcc
                    system("mkdir -p /tmp/udisk");
#else
                    system("mkdir -p /media/udisk");
#endif
                }
                QString command = QString(" mount ") + path + QString(" -o utf8=1 ") + mountUSBPath;
                int ret = system(command.toLocal8Bit().constData());
                if (0 == ret) {
                    m_USBDiskPath = path;
                    usbDiskScan(mountUSBPath);
                } else {
                    qCritical() << "mount usb failed!!!!!1";
                }
            }
        }
    } else if (path.startsWith(QString("/dev/mmcblk"))) {
        QChar lastChar = path.at(path.length() - 1);
        if ((lastChar >= QChar('0'))
                && (lastChar <= QChar('9'))) {
            if (m_SDDiskPath.isEmpty()
                    && QFile::exists(path)) {
                if (!QFile::exists(mountSDPath)) {
#ifdef gcc
                    system("mkdir -p /tmp/ddisk");
#else
                    system("mkdir -p /media/sdisk");
#endif
                }
                QString command = QString(" mount ") + path + QString(" -o utf8=1 ") + mountSDPath;
                int ret = system(command.toLocal8Bit().constData());
                if (0 == ret) {
                    m_SDDiskPath = path;
                    sdDiskScan(mountSDPath);
                } else {
                    qCritical() << "mount sd failed!!!!!1";
                }
            }
        }
    } else {
        qDebug() << "add other device!";
    }
}

void DeviceWatcherPrivate::diskDeviceRemove(const QString &path)
{
    qDebug() << "diskDeviceRemove" << path << m_USBDiskPath << m_SDDiskPath;
    if (m_USBDiskPath == path) {
        if (!QFile::exists(path)) {
            QString command = QString(" umount -l ") + mountUSBPath;
            int ret = system(command.toLocal8Bit().constData());
            if (0 == ret) {
                usbDiskCancelScan(mountUSBPath);
            } else {
                qCritical() << "umount usb failed!!!!";
            }
        }
    } else if (m_SDDiskPath == path) {
        if (!QFile::exists(path)) {
            QString command = QString(" umount -l ") + mountSDPath;
            int ret = system(command.toLocal8Bit().constData());
            if (0 == ret) {
                sdDiskCancelScan(mountSDPath);
            } else {
                qCritical() << "umount sd failed!!!!";
            }
        }
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


#ifdef gcc
static inline void signalHandler(int signo)
{
    qDebug() << "signalHandler" << signo;
    switch (signo) {
    case SIGUSR1: {
        if (NULL != qApp) {
            g_DeviceWatcher->testMount();
        }
        break;
    }
    case SIGUSR2: {
        if (NULL != qApp) {
            g_DeviceWatcher->testUnmount();
        }
        break;
    }
    default : {
        exit(EXIT_FAILURE);
        break;
    }
    }
}
#endif

///* Signal number definitions.  Linux version.
//   Copyright (C) 1995-2016 Free Software Foundation, Inc.
//   This file is part of the GNU C Library.

//   The GNU C Library is free software; you can redistribute it and/or
//   modify it under the terms of the GNU Lesser General Public
//   License as published by the Free Software Foundation; either
//   version 2.1 of the License, or (at your option) any later version.

//   The GNU C Library is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//   Lesser General Public License for more details.

//   You should have received a copy of the GNU Lesser General Public
//   License along with the GNU C Library; if not, see
//   <http://www.gnu.org/licenses/>.  */

//#ifdef	_SIGNAL_H

///* Fake signal functions.  */
//#define SIG_ERR	((__sighandler_t) -1)		/* Error return.  */
//#define SIG_DFL	((__sighandler_t) 0)		/* Default action.  */
//#define SIG_IGN	((__sighandler_t) 1)		/* Ignore signal.  */

//#ifdef __USE_UNIX98
//# define SIG_HOLD	((__sighandler_t) 2)	/* Add signal to hold mask.  */
//#endif


///* Signals.  */
//#define	SIGHUP		1	/* Hangup (POSIX).  */
//#define	SIGINT		2	/* Interrupt (ANSI).  */
//#define	SIGQUIT		3	/* Quit (POSIX).  */
//#define	SIGILL		4	/* Illegal instruction (ANSI).  */
//#define	SIGTRAP		5	/* Trace trap (POSIX).  */
//#define	SIGABRT		6	/* Abort (ANSI).  */
//#define	SIGIOT		6	/* IOT trap (4.2 BSD).  */
//#define	SIGBUS		7	/* BUS error (4.2 BSD).  */
//#define	SIGFPE		8	/* Floating-point exception (ANSI).  */
//#define	SIGKILL		9	/* Kill, unblockable (POSIX).  */
//#define	SIGUSR1		10	/* User-defined signal 1 (POSIX).  */
//#define	SIGSEGV		11	/* Segmentation violation (ANSI).  */
//#define	SIGUSR2		12	/* User-defined signal 2 (POSIX).  */
//#define	SIGPIPE		13	/* Broken pipe (POSIX).  */
//#define	SIGALRM		14	/* Alarm clock (POSIX).  */
//#define	SIGTERM		15	/* Termination (ANSI).  */
//#define	SIGSTKFLT	16	/* Stack fault.  */
//#define	SIGCLD		SIGCHLD	/* Same as SIGCHLD (System V).  */
//#define	SIGCHLD		17	/* Child status has changed (POSIX).  */
//#define	SIGCONT		18	/* Continue (POSIX).  */
//#define	SIGSTOP		19	/* Stop, unblockable (POSIX).  */
//#define	SIGTSTP		20	/* Keyboard stop (POSIX).  */
//#define	SIGTTIN		21	/* Background read from tty (POSIX).  */
//#define	SIGTTOU		22	/* Background write to tty (POSIX).  */
//#define	SIGURG		23	/* Urgent condition on socket (4.2 BSD).  */
//#define	SIGXCPU		24	/* CPU limit exceeded (4.2 BSD).  */
//#define	SIGXFSZ		25	/* File size limit exceeded (4.2 BSD).  */
//#define	SIGVTALRM	26	/* Virtual alarm clock (4.2 BSD).  */
//#define	SIGPROF		27	/* Profiling alarm clock (4.2 BSD).  */
//#define	SIGWINCH	28	/* Window size change (4.3 BSD, Sun).  */
//#define	SIGPOLL		SIGIO	/* Pollable event occurred (System V).  */
//#define	SIGIO		29	/* I/O now possible (4.2 BSD).  */
//#define	SIGPWR		30	/* Power failure restart (System V).  */
//#define SIGSYS		31	/* Bad system call.  */
//#define SIGUNUSED	31

//#define	_NSIG		65	/* Biggest signal number + 1
//				   (including real-time signals).  */

//#define SIGRTMIN        (__libc_current_sigrtmin ())
//#define SIGRTMAX        (__libc_current_sigrtmax ())

///* These are the hard limits of the kernel.  These values should not be
//   used directly at user level.  */
//#define __SIGRTMIN	32
//#define __SIGRTMAX	(_NSIG - 1)

//#endif	/* <signal.h> included.  */
