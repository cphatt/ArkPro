#ifndef FMWIDGET_H
#define FMWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class FMWidgetPrivate;
class FMWidget
        : protected QWidget
{
    Q_OBJECT
public:
    explicit FMWidget(QWidget* parent = NULL);
    ~FMWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
private:
    friend class FMWidgetPrivate;
    QScopedPointer<FMWidgetPrivate> m_Private;
};

#endif // FMWIDGET_H
