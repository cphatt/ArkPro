#ifndef CARLIFELINKWIDGET_H
#define CARLIFELINKWIDGET_H

#include "BusinessLogic/Link/Link.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/MessageBox.h"
#include <QWidget>
#include <QScopedPointer>

class CarlifeLinkWidgetPrivate;
class CarlifeLinkWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Link::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(CarlifeLinkWidget)
public:
    explicit CarlifeLinkWidget(QWidget *parent = 0);
    ~CarlifeLinkWidget();

signals:

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
    friend class CarlifeLinkWidgetPrivate;
    QScopedPointer<CarlifeLinkWidgetPrivate> m_Private;
};

#endif // CARLIFELINKWIDGET_H
