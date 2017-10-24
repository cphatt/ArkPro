#ifndef VIDEOSTATUSWIDGET_H
#define VIDEOSTATUSWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VideoStatusWidgetPrivate;
class VideoStatusWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoStatusWidget)
public:
    explicit VideoStatusWidget(QWidget *parent = NULL);
    ~VideoStatusWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void customEvent(QEvent* event);
protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    void onVideoPlayerInformation(const int type, const int index,const QString &fileName, const int endTime);
private:
    friend class VideoStatusWidgetPrivate;
    QScopedPointer<VideoStatusWidgetPrivate> m_Private;
};

#endif // VIDEOSTATUSWIDGET_H
