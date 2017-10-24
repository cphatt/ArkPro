#include "PixmapWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QImage>

PixmapWidget::PixmapWidget(QWidget *parent)
    : QWidget(parent)
    , Multimedia::Interface()
{
    m_X1 = 0;
    m_Y1 = 0;
    m_DeltaX = 0;
    m_DeltaY = 0;
}

PixmapWidget::~PixmapWidget()
{
}

void PixmapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //    painter.setPen(Qt::green);
    //    painter.drawRect(rect().adjusted(0, 0, -1, -1));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawPixmap(QRect(m_DeltaX, m_DeltaY, width(), height()), m_Pixmap);
    //    painter.drawPixmap(m_DeltaX, m_DeltaY, m_Pixmap);
    QWidget::paintEvent(event);
}

void PixmapWidget::mousePressEvent(QMouseEvent *event)
{
    m_X1 = event->pos().x();
    m_Y1 = event->pos().y();
    QWidget::mousePressEvent(event);
}

void PixmapWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (x() < 0) {
        int x2  = event->pos().x();
        int deltaX = x2 - m_X1;
        m_X1 = event->pos().x();
        if ((deltaX + m_DeltaX + x()) <= 0) {
            m_DeltaX += deltaX;
        }
        if (m_DeltaX > 0) {
            if (m_DeltaX + x() >= 0) {
                m_DeltaX = -x();
            }
        } else {
            if (m_DeltaX <= x()) {
                m_DeltaX = x();
            }
        }
    }
    if (y() < 0) {
        int y2  = event->pos().y();
        int deltaY = y2 - m_Y1;
        m_Y1 = event->pos().y();
        if ((deltaY + m_DeltaY + y()) <= 0) {
            m_DeltaY += deltaY;
        }
        if (m_DeltaY > 0) {
            if (m_DeltaY + y() >= 0) {
                m_DeltaY = -y();
            }
        } else {
            if (m_DeltaY <= y()) {
                m_DeltaY = y();
            }
        }
    }
    update();
    QWidget::mouseMoveEvent(event);
}

void PixmapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

void PixmapWidget::onImagePlayerChange(const QString &fileName, const int width, const int height, const int format, const QByteArray &imageData)
{
    QImage image(width, height, static_cast<QImage::Format>(format));
    if (NULL == memcpy(image.bits(), imageData.data(), imageData.length())) {
        qDebug() << "onImagePlayerChange memcpy failed!";
    }
    m_Pixmap = QPixmap::fromImage(image);
    m_X1 = 0;
    m_Y1 = 0;
    m_DeltaX = 0;
    m_DeltaY = 0;
    update();
}
