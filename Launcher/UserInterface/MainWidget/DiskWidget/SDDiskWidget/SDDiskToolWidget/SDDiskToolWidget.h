#ifndef SDDISKTOOLWIDGET_H
#define SDDISKTOOLWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskToolWidgetPrivate;
class SDDiskToolWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(SDDiskToolWidget)
public:
    explicit SDDiskToolWidget(QWidget *parent = NULL);
    ~SDDiskToolWidget();
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
    friend class SDDiskToolWidgetPrivate;
    QScopedPointer<SDDiskToolWidgetPrivate> m_Private;
};

#endif // SDDISKTOOLWIDGET_H
