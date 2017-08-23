#ifndef FIELDWIDGET_H
#define FIELDWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class FieldWidgetPrivate;
class FieldWidget
        : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(FieldWidget)
public:
    explicit FieldWidget(QWidget *parent = NULL);
    ~FieldWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class FieldWidgetPrivate;
    QScopedPointer<FieldWidgetPrivate> m_Private;
};

#endif // FIELDWIDGET_H
