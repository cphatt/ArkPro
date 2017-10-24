#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>

class PixmapWidgetPrivate;
class PixmapWidget
        : protected QWidget
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(PixmapWidget)
public:
    explicit PixmapWidget(QWidget *parent);
    ~PixmapWidget();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
protected slots:
    void onImagePlayerChange(const QString &fileName,const int width, const int height, const int format, const QByteArray &imageData);
private:
    QPixmap m_Pixmap;
    int m_X1;
    int m_Y1;
    int m_DeltaX;
    int m_DeltaY;
};
#endif // PIXMAPWIDGET_H
