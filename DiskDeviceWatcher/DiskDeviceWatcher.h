#ifndef DISKDEVICEWATCHER_H
#define DISKDEVICEWATCHER_H

#include <QObject>
#include <QScopedPointer>

class DiskDeviceWatcherPrivate;
class DiskDeviceWatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DiskDeviceWatcher)
public:
    enum Action {
        A_Add = 0,
        A_Remove = 1,
    };
    explicit DiskDeviceWatcher(QObject *parent = NULL);
    ~DiskDeviceWatcher();
signals:
    void diskDeviceChange(const QString &device, const DiskDeviceWatcher::Action action);
private slots:
    void onSocketNotifier();
private:
    friend class DiskDeviceWatcherPrivate;
    QScopedPointer<DiskDeviceWatcherPrivate> m_Private;
};

#endif // DISKDEVICEWATCHER_H
