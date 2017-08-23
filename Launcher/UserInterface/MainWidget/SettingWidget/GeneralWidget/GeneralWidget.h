#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class GeneralWidgetPrivate;
class GeneralWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralWidget)
public:
    explicit GeneralWidget(QWidget *parent = NULL);
    ~GeneralWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent *event);

protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class GeneralWidgetPrivate;
    QScopedPointer<GeneralWidgetPrivate> m_Private;
};

#endif // GENERALWIDGET_H
