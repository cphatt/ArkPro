#ifndef SDDISKWIDGET_H
#define SDDISKWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskWidgetPrivate;
class SDDiskWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskWidget)
public:
    explicit SDDiskWidget(QWidget *parent = NULL);
    ~SDDiskWidget();
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
    friend class SDDiskWidgetPrivate;
    QScopedPointer<SDDiskWidgetPrivate> m_Private;
};

#endif // SDDISKWIDGET_H




