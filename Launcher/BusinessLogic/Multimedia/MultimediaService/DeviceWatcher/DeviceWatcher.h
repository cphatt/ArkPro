#ifndef DEVICEWATCHER_H
#define DEVICEWATCHER_H

#include "MultimediaService.h"
#include "DiskDeviceWatcher.h"
#include <QObject>
#include <QSharedPointer>

class DeviceWatcherPrivate;
class DeviceWatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeviceWatcher)
#ifdef g_DeviceWatcher
#undef g_DeviceWatcher
#endif
#define g_DeviceWatcher (DeviceWatcher::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onDeviceWatcherStatus(const int type, const int status) = 0;
        //    virtual void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status) = 0;
        virtual void onMusicFilePath(const QString &path, const int type) = 0;
        //    virtual void onMusicFilePath(const QString &path, const DeviceWatcherType type) = 0;
        virtual void onImageFilePath(const QString &path, const int type) = 0;
        //    virtual void onImageFilePath(const QString &path, const DeviceWatcherType type) = 0;
        virtual void onVideoFilePath(const QString &path, const int type) = 0;
        //    virtual void onVideoFilePath(const QString &path, const DeviceWatcherType type) = 0;
    };
    inline static DeviceWatcher* instance() {
        static DeviceWatcher deviceWatcher;
        return &deviceWatcher;
    }
    void synchronize();
    void deviceWatcherCheckStatus(const int type);
    //    void deviceWatcherCheckStatus(const DeviceWatcherType type);
    void testMount();
    void testUnmount();
signals:
    void onDeviceWatcherStatus(const int type, const int status);
    //    void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onMusicFilePath(const QString &path, const int type);
    //    void onMusicFilePath(const QString &path, const DeviceWatcherType type);
    void onImageFilePath(const QString &path, const int type);
    //    void onImageFilePath(const QString &path, const DeviceWatcherType type);
    void onVideoFilePath(const QString &path, const int type);
    //    void onVideoFilePath(const QString &path, const DeviceWatcherType type);
private slots:
    void onDiskDeviceChange(const QString &device, const DiskDeviceWatcher::Action action);
    void onUSBFilePath(const QString &path, const int index);
    void onSDFilePath(const QString &path, const int index);
    void onFinish();
private:
    explicit DeviceWatcher(QObject *parent = NULL);
    ~DeviceWatcher();
    friend class DeviceWatcherPrivate;
    QSharedPointer<DeviceWatcherPrivate> m_Private;
};

#endif // DEVICEWATCHER_H
