#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H
#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>


enum MediaStatus {
    IPPS = 0,
    MPPS = 1,
    VPPS = 2,
    None = 3,
};
#define MediaStatus int
class MediaWidgetPrivate;
class MediaWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(MediaWidget)
public:
    explicit MediaWidget(QWidget *parent = 0);
    ~MediaWidget();

protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);

signals:

protected slots:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    void onImagePlayerPlayStatus(const int status);
    void onMusicPlayerPlayStatus(const int status);
    void onVideoPlayerPlayStatus(const int status);
private slots:
    void onBmpButtonRelease();


private:
    friend class MediaWidgetPrivate;
    QScopedPointer<MediaWidgetPrivate> m_Private;
};

#endif // MEDIAWIDGET_H
