#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QImage>
#include <QScopedPointer>

class ImageWidgetPrivate;
class ImageWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageWidget)
public:
    explicit ImageWidget(QWidget *parent = NULL);
    ~ImageWidget();
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void hideEvent(QHideEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type,const QString &status);
    //Multimedia::Interface
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
    void onImagePlayerChange(const int type, const QString &filePath, const int index, const int percent, const int rotate);
    //    void onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate);
private slots:
    void onStartTimer();
    void onStopTimer();
private slots:
    void onTimeout();
private:
    friend class ImageWidgetPrivate;
    QScopedPointer<ImageWidgetPrivate> m_Private;
};

#endif // IMAGEWIDGET_H
