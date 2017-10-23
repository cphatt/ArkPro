#ifndef CARPLAYWIDGET_H
#define CARPLAYWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Link/Link.h"
#include <QWidget>
#include <QScopedPointer>
#include <QMouseEvent>
class CarPlayWidgetPrivate;
class CarPlayWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(CarPlayWidget)
public:
    explicit CarPlayWidget(QWidget *parent = NULL);
    ~CarPlayWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void customEvent(QEvent* event);
    void mousePressEvent(QMouseEvent *event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onToolButtonRelease();
private:
    friend class CarPlayWidgetPrivate;
    QScopedPointer<CarPlayWidgetPrivate> m_Private;
};

#endif // CarPlayWidget_H
