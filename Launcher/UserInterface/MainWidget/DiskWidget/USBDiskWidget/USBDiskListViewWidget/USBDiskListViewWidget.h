#ifndef USBDISKLISTVIEWWIDGET_H
#define USBDISKLISTVIEWWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskListViewWidgetPrivate;
class USBDiskListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
public:
    explicit USBDiskListViewWidget(QWidget *parent = NULL);
    ~USBDiskListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class USBDiskListViewWidgetPrivate;
    QScopedPointer<USBDiskListViewWidgetPrivate> m_Private;
};

#endif // USBDISKLISTVIEWWIDGET_H
