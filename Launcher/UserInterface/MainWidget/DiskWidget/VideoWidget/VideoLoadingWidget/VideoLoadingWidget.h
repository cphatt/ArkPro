#ifndef VIDEOLOADINGWIDGET_H
#define VIDEOLOADINGWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class VideoLoadingWidgetPrivate;
class VideoLoadingWidget
        : protected QWidget
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoLoadingWidget)
public:
    explicit VideoLoadingWidget(QWidget *parent = NULL);
    ~VideoLoadingWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    bool event(QEvent* event);
protected slots:
    //Multimedia::Interface
    void onVideoPlayerPlayStatus(const int status);
    //    void onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status);
private:
    friend class VideoLoadingWidgetPrivate;
    QScopedPointer<VideoLoadingWidgetPrivate> m_Private;
};

#endif // VIDEOLOADINGWIDGET_H
