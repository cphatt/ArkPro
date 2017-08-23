#ifndef SDDISKVIDEOLISTVIEWWIDGET_H
#define SDDISKVIDEOLISTVIEWWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskVideoListViewWidgetPrivate;
class SDDiskVideoListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskVideoListViewWidget)
public:
    explicit SDDiskVideoListViewWidget(QWidget *parent = 0);
    ~SDDiskVideoListViewWidget();
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
    void onVideoPlayerFileNames(const int type, const QString& xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
private slots:
    void onVideoListViewItemRelease(const int index);
    void onToolButtonRelease();
private:
    friend class SDDiskVideoListViewWidgetPrivate;
    QScopedPointer<SDDiskVideoListViewWidgetPrivate> m_Private;
};

#endif // SDDISKVIDEOLISTVIEWWIDGET_H
