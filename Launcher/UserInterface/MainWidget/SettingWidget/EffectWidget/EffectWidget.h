#ifndef EFFECTWIDGET_H
#define EFFECTWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class EffectWidgetPrivate;
class EffectWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(EffectWidget)
public:
    explicit EffectWidget(QWidget *parent = NULL);
    ~EffectWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class EffectWidgetPrivate;
    QScopedPointer<EffectWidgetPrivate> m_Private;
};

#endif // EFFECTWIDGET_H
