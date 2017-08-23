#ifndef MIRRORLINKWIDGET_H
#define MIRRORLINKWIDGET_H

#include "BusinessLogic/Link/Link.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/MessageBox.h"
#include <QWidget>
#include <QScopedPointer>

class MirrorLinkWidgetPrivate;
class MirrorLinkWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Link::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(MirrorLinkWidget)
public:
    explicit MirrorLinkWidget(QWidget *parent = NULL);
    ~MirrorLinkWidget();
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
    //Link::Interface
    void onLinkStatusChange(const int type, const int status) ;
    //  void onLinkStatusChange(const Link_Type type, const Link_STATUS status);
private slots:
    void onMessageWidgetChange(const MessageBox::Type type);
    void onPopBtnRelease();
    void onToolBtnRelease(const int type);
    void onTimeout();
private:
    friend class MirrorLinkWidgetPrivate;
    QScopedPointer<MirrorLinkWidgetPrivate> m_Private;
};

#endif // MIRRORLINKWIDGET_H
