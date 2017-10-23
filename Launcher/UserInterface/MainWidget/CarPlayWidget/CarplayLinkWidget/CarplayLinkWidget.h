#ifndef CARPLAYLINKWIDGET_H
#define CARPLAYLINKWIDGET_H

#include "BusinessLogic/Link/Link.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/MessageBox.h"
#include <QWidget>
#include <QScopedPointer>

class CarplayLinkWidgetPrivate;
class CarplayLinkWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Link::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(CarplayLinkWidget)
public:
    explicit CarplayLinkWidget(QWidget *parent = NULL);
    ~CarplayLinkWidget();
protected:
    bool event(QEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Link::Interface  //收到来自服务的消息
    void onLinkStatusChange(const int type, const int status) ;
    //  void onLinkStatusChange(const Link_Type type, const Link_STATUS status);
private:
    friend class CarplayLinkWidgetPrivate;
    QScopedPointer<CarplayLinkWidgetPrivate> m_Private;
};

#endif // CARPLAYLINKWIDGET_H
