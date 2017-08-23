#ifndef DISKWIDGET_H
#define DISKWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>


class DiskWidgetPrivate;
class DiskWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(DiskWidget)
public:
    explicit DiskWidget(QWidget *parent = NULL);
    ~DiskWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
private slots:
    void onBmpButtonRelease();

private:
    friend class DiskWidgetPrivate;
    QScopedPointer<DiskWidgetPrivate> m_Private;
};

#endif // DISKWIDGET_H
