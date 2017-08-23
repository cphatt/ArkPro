#ifndef EFFECTTOOLBARWIDGET_H
#define EFFECTTOOLBARWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class EffectToolBarWidgetPrivate;
class EffectToolBarWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(EffectToolBarWidget)
public:
    explicit EffectToolBarWidget(QWidget *parent = NULL);
    ~EffectToolBarWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
private:
    friend class EffectToolBarWidgetPrivate;
    QScopedPointer<EffectToolBarWidgetPrivate> m_Private;
};

#endif // EFFECTTOOLBARWIDGET_H
