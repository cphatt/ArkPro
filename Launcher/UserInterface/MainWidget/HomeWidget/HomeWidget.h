#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class HomeWidgetPrivate;
class HomeWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(HomeWidget)
public:
    explicit HomeWidget(QWidget *parent = NULL);
    ~HomeWidget();
protected:
    void showEvent(QShowEvent *event);
    void resizeEvent(QResizeEvent *event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
private slots:
    void onBmpButtonRelease();
private:
    friend class HomeWidgetPrivate;
    QScopedPointer<HomeWidgetPrivate> m_Private;
};

#endif // HOMEWIDGET_H
