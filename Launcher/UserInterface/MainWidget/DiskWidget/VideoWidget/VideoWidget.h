#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include "VideoToolBarWidget/VideoToolBarWidget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VideoWidgetPrivate;
class VideoWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoWidget)
public:
    explicit VideoWidget(QWidget *parent = NULL);
    ~VideoWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void hideEvent(QHideEvent *event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerInformation(const QString &fileName, const int endTime);
private slots:
    void onTimeout();
private:
    friend class VideoWidgetPrivate;
    QScopedPointer<VideoWidgetPrivate> m_Private;
};

#endif // VIDEOWIDGET_H
