#ifndef SDDISKLISTVIEWWIDGET_H
#define SDDISKLISTVIEWWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class SDDiskListViewWidgetPrivate;
class SDDiskListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
public:
    explicit SDDiskListViewWidget(QWidget *parent = NULL);
    ~SDDiskListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class SDDiskListViewWidgetPrivate;
    QScopedPointer<SDDiskListViewWidgetPrivate> m_Private;
};

#endif // SDDISKLISTVIEWWIDGET_H
