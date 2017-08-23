#ifndef DISKSCANNER_H
#define DISKSCANNER_H

#include <QObject>
#include <QMap>
#include <QStringList>
#include <QScopedPointer>

class DiskScannerPrivate;
class DiskScanner : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DiskScanner)
public:
    explicit DiskScanner(QObject *parent = NULL);
    ~DiskScanner();
    void setScannerSuffixMap(const QMap<int, QStringList> &mapList);
    void setMinimumScanTime(const int msec);
    void startScanner(const QString &path);
    void stopScanner();
signals:
    void finish();
    void filePath(const QString &path, const int index);
private slots:
    void onFinish();
    void onTimeout();
private:
    friend class DiskScannerPrivate;
    QScopedPointer<DiskScannerPrivate> m_Private;
};

#endif // DISKSCANNER_H
