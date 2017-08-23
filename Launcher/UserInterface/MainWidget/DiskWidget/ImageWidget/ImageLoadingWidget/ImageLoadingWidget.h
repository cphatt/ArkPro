#ifndef IMAGELOADINGWIDGET_H
#define IMAGELOADINGWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class ImageLoadingWidgetPrivate;
class ImageLoadingWidget
        : protected QWidget
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(ImageLoadingWidget)
public:
    explicit ImageLoadingWidget(QWidget *parent = NULL);
    ~ImageLoadingWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    bool event(QEvent* event);
protected slots:
    //Multimedia::Interface
    void onImagePlayerPlayStatus(const int status);
    //        void onImagePlayerPlayStatus(const ImagePlayerPlayStatus status);
private:
    friend class ImageLoadingWidgetPrivate;
    QScopedPointer<ImageLoadingWidgetPrivate> m_Private;
};

#endif // IMAGELOADINGWIDGET_H
