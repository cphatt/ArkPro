#ifndef SDDISKIMAGELISTVIEWWIDGET_H
#define SDDISKIMAGELISTVIEWWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskImageListViewWidgetPrivate;
class SDDiskImageListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskImageListViewWidget)
public:
    explicit SDDiskImageListViewWidget(QWidget *parent = 0);
    ~SDDiskImageListViewWidget();
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
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerFileNames(const int type, const QString &xml);
//    void onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml);
private slots:
    void onImageListViewItemRelease(const int index);
    void onListBtnRelease();
private:
    friend class SDDiskImageListViewWidgetPrivate;
    QScopedPointer<SDDiskImageListViewWidgetPrivate> m_Private;
};

#endif // SDDISKIMAGELISTVIEWWIDGET_H
