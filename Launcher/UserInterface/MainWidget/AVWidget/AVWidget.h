#ifndef AVWIDGET_H
#define AVWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class AVWidgetPrivate;
class AVWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(AVWidget)
public:
    explicit AVWidget(QWidget *parent = NULL);
    ~AVWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void hideEvent(QHideEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class AVWidgetPrivate;
    QScopedPointer<AVWidgetPrivate> m_Private;
};

#endif // AVWIDGET_H
