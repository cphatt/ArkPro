#ifndef LINKWIDGET_H
#define LINKWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Link/Link.h"
#include <QWidget>
#include <QScopedPointer>

class LinkWidgetPrivate;
class LinkWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(LinkWidget)
public:
    explicit LinkWidget(QWidget *parent = NULL);
    ~LinkWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onToolButtonRelease();
private:
    friend class LinkWidgetPrivate;
    QScopedPointer<LinkWidgetPrivate> m_Private;
};

#endif // LINKWIDGET_H
