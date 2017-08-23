#include "ImageWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/Utility.h"
#include "ImageStatusWidget/ImageStatusWidget.h"
#include "PixmapWidget/PixmapWidget.h"
#include "ImageShortCutWidget/ImageShortCutWidget.h"
#include "ImageLoadingWidget/ImageLoadingWidget.h"
#include "ImageToolBarWidget/ImageToolBarWidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QTimer>

class ImageWidgetPrivate
{
public:
    explicit ImageWidgetPrivate(ImageWidget *parent);
    ~ImageWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void imageWidgetSwitchHandler(const QString &status);
    ImageStatusWidget* m_StatusWidget;
    ImageToolBarWidget* m_ToolBarWidget;
    PixmapWidget* m_PixmapWidget;
    ImageLoadingWidget* m_ImageLoadingWidget;
    ImageShortCutWidget* m_ImageShortCutWidget;
    QTimer* m_Timer;
    QRect m_TouchRect;
    QImage m_Image;
    QMatrix m_Matrix;
private:
    ImageWidget *m_Parent;
};

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new ImageWidgetPrivate(this))
{
}

ImageWidget::~ImageWidget()
{
}

void ImageWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void ImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Utility::customBlackColor());
#ifdef gcc
    painter.setPen(Qt::red);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void ImageWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "ImageWidget::mousePressEvent";
    QWidget::mousePressEvent(event);
}

void ImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "ImageWidget::mouseMoveEvent";
    QWidget::mouseMoveEvent(event);
}

void ImageWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (m_Private->m_TouchRect.contains(event->pos())) {
        if (QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight()) == m_Private->m_TouchRect) {
            g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::Show);
        } else {
            g_Widget->setWidgetType(Widget::T_ImageFullScreen, WidgetStatus::Show);
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void ImageWidget::hideEvent(QHideEvent *event)
{
    if (isVisible()) {
        g_Multimedia->imagePlayerExit();
    }
    QWidget::hideEvent(event);
}

void ImageWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Image: {
        m_Private->imageWidgetSwitchHandler(status);
        break;
    }
    case Widget::T_ImageFullScreen: {
        if (WidgetStatus::Show == status) {
            m_Private->m_TouchRect = QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight());
            m_Private->m_Timer->stop();
            setVisible(true);
        }
        break;
    }
    default : {
        if (WidgetStatus::Show == status) {
            m_Private->m_Timer->stop();
            setVisible(false);
        }
        break;
    }
    }
}

void ImageWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    qDebug() << "ImageWidget::onImagePlayerPlayStatus" << status;
    switch (status) {
    case IPPS_Start: {
        if (m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->start();
        }
        m_Private->m_PixmapWidget->setVisible(false);
        break;
    }
    case IPPS_Play: {
        if (m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->start();
        }
        m_Private->m_PixmapWidget->setVisible(true);
        break;
    }
    default: {
        break;
    }
    }
}

void ImageWidget::onImagePlayerChange(const DeviceWatcherType type, const QString &filePath, const int index, const int percent, const int rotate)
{
    qDebug() << "ImageWidget::onImagePlayerChange" << type << filePath << index << percent << rotate;
    const float scale = (static_cast<const float>(percent) / 100);
    m_Private->m_Image.load(filePath);
    m_Private->m_Matrix.reset();
    m_Private->m_Matrix.rotate(rotate);
    m_Private->m_Image = m_Private->m_Image.scaled(m_Private->m_Image.width() * scale, m_Private->m_Image.height() * scale, Qt::KeepAspectRatio).transformed(m_Private->m_Matrix, Qt::SmoothTransformation);
    m_Private->m_PixmapWidget->onPixmapChange(QPixmap::fromImage(m_Private->m_Image), false);
}

void ImageWidget::onStartTimer()
{
    qDebug() << "onStartTimer";
    if (QRect(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight()) != m_Private->m_TouchRect) {
        m_Private->m_Timer->start();
    }
}

void ImageWidget::onStopTimer()
{
    qDebug() << "onStopTimer";
    m_Private->m_Timer->stop();
}

ImageWidgetPrivate::ImageWidgetPrivate(ImageWidget *parent)
    : m_Parent(parent)
{
    m_Timer = NULL;
    m_StatusWidget = NULL;
    m_ToolBarWidget = NULL;
    m_PixmapWidget = NULL;
    m_ImageLoadingWidget = NULL;
    m_ImageShortCutWidget = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

ImageWidgetPrivate::~ImageWidgetPrivate()
{
}

void ImageWidgetPrivate::initialize()
{
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(7000);
    m_PixmapWidget = new PixmapWidget(m_Parent);
    m_StatusWidget = new ImageStatusWidget(m_Parent);
    m_ToolBarWidget = new ImageToolBarWidget(m_Parent);
    m_ImageLoadingWidget = new ImageLoadingWidget(m_Parent);
    m_ImageShortCutWidget = new ImageShortCutWidget(m_Parent);
}

void ImageWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
    //    QObject::connect(m_PixmapWidget,  SIGNAL(startTimer()),
    //                     m_Parent,        SLOT(onStartTimer()),
    //                     type);
    //    QObject::connect(m_PixmapWidget,  SIGNAL(stopTimer()),
    //                     m_Parent,        SLOT(onStopTimer()),
    //                     type);
}

void ImageWidget::onTimeout()
{
    g_Widget->setWidgetType(Widget::T_ImageFullScreen, WidgetStatus::Show);
}

void ImageWidgetPrivate::imageWidgetSwitchHandler(const QString &status)
{
    qDebug() << "ImageWidgetPrivate::imageWidgetSwitchHandler" << status;
    if (WidgetStatus::RequestShow == status) {
        g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::Show);
    } else if (WidgetStatus::Show == status) {
        m_TouchRect = g_Widget->geometryFit(0, 74, g_Widget->baseWindowWidth() - 0, g_Widget->baseWindowHeight() - 74 - 103);
        m_Parent->setVisible(true);
        m_Timer->start();
    }
}
