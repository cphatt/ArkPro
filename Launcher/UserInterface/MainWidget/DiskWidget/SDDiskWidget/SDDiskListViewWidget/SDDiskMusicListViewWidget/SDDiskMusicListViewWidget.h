#ifndef SDDISKMUSICLISTVIEWWIDGET_H
#define SDDISKMUSICLISTVIEWWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskMusicListViewWidgetPrivate;
class SDDiskMusicListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskMusicListViewWidget)
public:
    explicit SDDiskMusicListViewWidget(QWidget *parent = 0);
    ~SDDiskMusicListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //DeviceWatcher::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    //Multimedia::Interface
    void onMusicPlayerFileNames(const int type, const QString &xml);
//    void onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onMusicPlayerPlayStatus(const int status);
    //    void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
private slots:
    void onMusicListViewItemRelease(const int index);
    void onToolButtonRelease();
private:
    friend class SDDiskMusicListViewWidgetPrivate;
    QScopedPointer<SDDiskMusicListViewWidgetPrivate> m_Private;
};

#endif // SDDISKMUSICLISTVIEWWIDGET_H
