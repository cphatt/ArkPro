#ifndef VIDEOTOOLBARWIDGET_H
#define VIDEOTOOLBARWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class VideoToolBarWidgetPrivate;
class VideoToolBarWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoToolBarWidget)
public:
    explicit VideoToolBarWidget(QWidget *parent = NULL);
    ~VideoToolBarWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //VideoPlayer::Interface
    void onVideoPlayerShowStatus(const int status);
    //    void onVideoPlayerShowStatus(const VideoPlayerShowStatus status);
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
    void onVideoPlayerInformation(const int type, const int index,const QString &fileName, const int endTime);
    void onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
private slots:
    void onToolButtonRelease();
    void onTickMarksMillesimalStart(const int millesimal);
    void onTickMarksMillesimalEnd(const int millesimal);
    void onTickMarksMillesimalChange(const int millesimal);

private:
    friend class VideoToolBarWidgetPrivate;
    QScopedPointer<VideoToolBarWidgetPrivate> m_Private;
};

#endif // VIDEOTOOLBARWIDGET_H
