#ifndef USBDISKVIDEOLISTVIEWWIDGET_H
#define USBDISKVIDEOLISTVIEWWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskVideoListViewWidgetPrivate;
class USBDiskVideoListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskVideoListViewWidget)
public:
    explicit USBDiskVideoListViewWidget(QWidget *parent = 0);
    ~USBDiskVideoListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onVideoPlayerFileNames(const int type, const QString& xml);
    //    void onVideoPlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
     void onVideoPlayerInformation(const int type, const int index, const QString &fileName, const int endTime);
private slots:
    void onVideoListViewItemRelease(const int index);
    void onToolButtonRelease();
private:
    friend class USBDiskVideoListViewWidgetPrivate;
    QScopedPointer<USBDiskVideoListViewWidgetPrivate> m_Private;
};

#endif // USBDISKVIDEOLISTVIEWWIDGET_H
