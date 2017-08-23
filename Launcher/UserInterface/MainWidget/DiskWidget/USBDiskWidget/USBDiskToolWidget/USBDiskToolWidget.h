#ifndef USBDISKTOOLWIDGET_H
#define USBDISKTOOLWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskToolWidgetPrivate;
class USBDiskToolWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskToolWidget)
public:
    explicit USBDiskToolWidget(QWidget *parent = NULL);
    ~USBDiskToolWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
private slots:
    void onToolButtonRelease();
private:
    friend class USBDiskToolWidgetPrivate;
    QScopedPointer<USBDiskToolWidgetPrivate> m_Private;
};

#endif // USBDISKTOOLWIDGET_H
