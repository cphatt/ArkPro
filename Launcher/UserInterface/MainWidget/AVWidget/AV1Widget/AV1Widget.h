#ifndef AV1WIDGET_H
#define AV1WIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/AV/AV.h"
#include <QWidget>
#include <QScopedPointer>

class AV1WidgetPrivate;
class AV1Widget
        : protected QWidget
        , protected Widget::Interface
        , protected AV::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(AV1Widget)
public:
    explicit AV1Widget(QWidget *parent = NULL);
    ~AV1Widget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //AV::Interface
    void onAVStatus(const int type, const int status);
    //    void onStartAV(const AVType type, const AVStatus status);
private slots:
    void onTimeout();
private:
    friend class AV1WidgetPrivate;
    QScopedPointer<AV1WidgetPrivate> m_Private;
};

#endif // AV1WIDGET_H
