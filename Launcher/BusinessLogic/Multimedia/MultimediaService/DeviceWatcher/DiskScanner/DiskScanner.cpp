#include "DiskScanner.h"
#include "CustomThread.h"
#include <QTimer>
#include <QDir>
#include <QDebug>

static void scannerThreadCallback(void *paramater);

class DiskScannerPrivate
{
    Q_DISABLE_COPY(DiskScannerPrivate)
public:
    explicit DiskScannerPrivate(DiskScanner *parent);
    ~DiskScannerPrivate();
    void initialize();
    void connectAllSlots();
    void recursionScan(const QString &path);
    void scanFinish();
    CustomThread* m_CustomThread;
    QMap< int, QStringList > m_MapList;
    QTimer* m_Timer;
    QString m_Path;
private:
    DiskScanner* m_Parent;
};

DiskScanner::DiskScanner(QObject *parent)
    : QObject(parent)
    , m_Private(new DiskScannerPrivate(this))
{   
}

DiskScanner::~DiskScanner()
{
}

void DiskScanner::setScannerSuffixMap(const QMap<int, QStringList> &mapList)
{
    m_Private->m_MapList = mapList;
}

void DiskScanner::setMinimumScanTime(const int msec)
{
    m_Private->m_Timer->setInterval(msec);
}

void DiskScanner::startScanner(const QString &path)
{
    stopScanner();
    m_Private->m_Path = path;
    m_Private->m_CustomThread->start();
}

void DiskScanner::stopScanner()
{
    m_Private->m_Path.clear();
    m_Private->m_Timer->stop();
    if (m_Private->m_CustomThread->isRunning()) {
        m_Private->m_CustomThread->wait();
        m_Private->m_CustomThread->quit();
    }
}

void DiskScanner::onFinish()
{
    qDebug() << "m_Private->m_Timer->isActive1()" << m_Private->m_Timer->isActive();
    if (!m_Private->m_Timer->isActive()) {
        qDebug() << "DiskScanner::onFinish";
        onTimeout();
    }
}

void DiskScanner::onTimeout()
{
    qDebug() << "m_Private->m_Timer->isActive1()" << m_Private->m_Timer->isActive();
    if (!m_Private->m_CustomThread->isRunning()) {
        qDebug() << "DiskScanner::onTimeout";
        emit finish();
    }
}

DiskScannerPrivate::DiskScannerPrivate(DiskScanner *parent)
    : m_Parent(parent)
{
    m_MapList.clear();
    m_Path.clear();
    m_CustomThread = NULL;
    m_Timer = NULL;
    initialize();
    connectAllSlots();
}

DiskScannerPrivate::~DiskScannerPrivate()
{
    m_CustomThread->exit(0);
    m_CustomThread->wait();
}

void DiskScannerPrivate::initialize()
{
    m_CustomThread = new CustomThread(m_Parent);
    m_CustomThread->setCallbackFunction(scannerThreadCallback, static_cast<void *>(this));
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(1500);
}

void DiskScannerPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_CustomThread, SIGNAL(finished()),
                     m_Parent,       SLOT(onFinish()),
                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

void DiskScannerPrivate::recursionScan(const QString &path)
{
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList fileInfoList = dir.entryInfoList();
    for (QFileInfoList::iterator fileIter = fileInfoList.begin(); fileIter != fileInfoList.end(); ++fileIter) {
        if (fileIter->isDir()) {
            recursionScan(fileIter->filePath());
        } else {
            for (QMap< int, QStringList >::iterator suffixIter = m_MapList.begin();
                 suffixIter != m_MapList.end();
                 ++suffixIter) {
                if (suffixIter.value().contains(fileIter->suffix(), Qt::CaseInsensitive)) {
                    emit m_Parent->filePath(fileIter->filePath(), suffixIter.key());
                }
            }
        }
    }
}

void DiskScannerPrivate::scanFinish()
{
}

static void scannerThreadCallback(void *paramater)
{
    DiskScannerPrivate *ptr = static_cast<DiskScannerPrivate *>(paramater);
    if (NULL != ptr) {
        ptr->m_Timer->start();
        ptr->recursionScan(ptr->m_Path);
        ptr->scanFinish();
    }
}
