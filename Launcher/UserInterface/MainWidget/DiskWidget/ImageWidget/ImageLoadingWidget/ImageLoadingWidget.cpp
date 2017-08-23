#include "ImageLoadingWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/MainWidget/DiskWidget/MultimediaLoadingWidget.h"
#include <QPainter>

class ImageLoadingWidgetPrivate
{
public:
    explicit ImageLoadingWidgetPrivate(ImageLoadingWidget* parent);
    ~ImageLoadingWidgetPrivate();
    void initialize();
    void connectAllSlots();
    MultimediaLoadingWidget* m_Background;
private:
    ImageLoadingWidget* m_Parent;
};

ImageLoadingWidget::ImageLoadingWidget(QWidget* parent)
    : QWidget(parent)
    , Multimedia::Interface()
    , m_Private(new ImageLoadingWidgetPrivate(this))
{
}

ImageLoadingWidget::~ImageLoadingWidget()
{
}

void ImageLoadingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void ImageLoadingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1, 127));
    QWidget::paintEvent(event);
}

bool ImageLoadingWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove: {
        event->accept();
        return true;
        break;
    }
    default: {
        break;
    }
    }
    return QWidget::event(event);
}

void ImageLoadingWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    switch (status) {
    case IPPS_Start: {
        setVisible(true);
        break;
    }
    default: {
        setVisible(false);
        break;
    }
    }
}

ImageLoadingWidgetPrivate::ImageLoadingWidgetPrivate(ImageLoadingWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

ImageLoadingWidgetPrivate::~ImageLoadingWidgetPrivate()
{
}

void ImageLoadingWidgetPrivate::initialize()
{
    m_Background = new MultimediaLoadingWidget(m_Parent);
    m_Background->show();
}

void ImageLoadingWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
