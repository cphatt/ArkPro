#ifndef DATETIMEWIDGET_H
#define DATETIMEWIDGET_H

#include <QWidget>
#include <QScopedPointer>
#include "BusinessLogic/Setting/Setting.h"
#include "BusinessLogic/Widget/Widget.h"
class DateTimeWidgetPrivate;
class DateTimeWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(DateTimeWidget)
public:
    explicit DateTimeWidget(QWidget* parent = NULL);
    ~DateTimeWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

protected slots:
    void OkBtnRelease();
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private:
    friend class DateTimeWidgetPrivate;
    QScopedPointer<DateTimeWidgetPrivate> m_Private;
};

#endif // DATETIMEWIDGET_H

