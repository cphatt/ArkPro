#include "VideoShortCutWidget.h"
#include "AutoConnect.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "BusinessLogic/Widget/Widget.h"
#include "EventEngine.h"
#include <QVariant>
#include <QDebug>
#include <QPainter>

class VideoShortCutWidgetPrivate
{
    Q_DISABLE_COPY(VideoShortCutWidgetPrivate)
public:
    explicit VideoShortCutWidgetPrivate(VideoShortCutWidget* parent);
    ~VideoShortCutWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_Background;
private:
    VideoShortCutWidget* m_Parent;
};

VideoShortCutWidget::VideoShortCutWidget(QWidget *parent)
    : QWidget(parent)
    , Multimedia::Interface()
    , m_Private(new VideoShortCutWidgetPrivate(this))
{
}

VideoShortCutWidget::~VideoShortCutWidget()
{
}

void VideoShortCutWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
    int width(53);
    int height(53);
    g_Widget->geometryFit((104 - width) * 0.5, (g_Widget->baseTabBarHeight() - height) * 0.5 - 10, width, height, m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void VideoShortCutWidget::customEvent(QEvent *event)
{
    qDebug() << "ImageShortCutWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::TabBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            if (this != ptr->m_Data->value<QWidget*>()) {
                this->setVisible(false);
            }
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void VideoShortCutWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    switch (status) {
    case VPPS_Start: {
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(this));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
        break;
    }
    case VPPS_Exit: {
        setVisible(false);
        break;
    }
    default: {
        break;
    }
    }
}


void VideoShortCutWidget::onBmpButtonRelease()
{
   // g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::RequestShow);
}

VideoShortCutWidgetPrivate::VideoShortCutWidgetPrivate(VideoShortCutWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(false);
}

VideoShortCutWidgetPrivate::~VideoShortCutWidgetPrivate()
{
}

void VideoShortCutWidgetPrivate::initialize()
{
    m_Background = new BmpButton(m_Parent);
    m_Background->show();
//    m_Background->setNormalBmpPath(QString(":/Images/Resources/Images/VideoShortCutWidgetBackground"));
//    m_Background->setPressBmpPath(QString(":/Images/Resources/Images/VideoShortCutWidgetBackground"));
}

void VideoShortCutWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void VideoShortCutWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
//    QObject::connect(m_Background, SIGNAL(bmpButtonRelease()),
//                     m_Parent,     SLOT(onBmpButtonRelease()),
//                     type);
}
