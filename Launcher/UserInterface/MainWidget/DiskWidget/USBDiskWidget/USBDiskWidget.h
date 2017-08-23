#ifndef USBDISKWIDGET_H
#define USBDISKWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskWidgetPrivate;
class USBDiskWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskWidget)
public:
    explicit USBDiskWidget(QWidget *parent = NULL);
    ~USBDiskWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
private:
    friend class USBDiskWidgetPrivate;
    QScopedPointer<USBDiskWidgetPrivate> m_Private;
};

#endif // USBDISKWIDGET_H
