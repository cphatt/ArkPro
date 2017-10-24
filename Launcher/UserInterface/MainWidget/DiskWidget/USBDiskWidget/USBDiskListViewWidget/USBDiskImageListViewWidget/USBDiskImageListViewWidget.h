#ifndef USBDISKIMAGELISTVIEWWIDGET_H
#define USBDISKIMAGELISTVIEWWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskImageListViewWidgetPrivate;
class USBDiskImageListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskImageListViewWidget)
public:
    explicit USBDiskImageListViewWidget(QWidget *parent = 0);
    ~USBDiskImageListViewWidget();
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
    void onImagePlayerFileNames(const int type, const QString &xml);
//    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
private slots:
    void onImageListViewItemRelease(const int index);
    void onListBtnRelease();
private:
    friend class USBDiskImageListViewWidgetPrivate;
    QScopedPointer<USBDiskImageListViewWidgetPrivate> m_Private;
};

#endif // USBDISKIMAGELISTVIEWWIDGET_H
