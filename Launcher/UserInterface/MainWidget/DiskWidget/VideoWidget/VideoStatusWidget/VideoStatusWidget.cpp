#include "VideoStatusWidget.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include "UserInterface/Common/TextWidget.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include <QPainter>
#include <QDebug>

namespace SourceString {
static const QString Video = QString(QObject::tr("Video>"));
}

class VideoStatusWidgetPrivate
{
    Q_DISABLE_COPY(VideoStatusWidgetPrivate)
public:
    explicit VideoStatusWidgetPrivate(VideoStatusWidget* parent);
    ~VideoStatusWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    TextWidget* m_TitleText;
    TextWidget* m_FileNameText;
private:
    VideoStatusWidget* m_Parent;
};

VideoStatusWidget::VideoStatusWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new VideoStatusWidgetPrivate(this))
{
}

VideoStatusWidget::~VideoStatusWidget()
{
}

void VideoStatusWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, 800, 58, this);
    g_Widget->geometryFit(0, 0, 150, 58, m_Private->m_TitleText);
    g_Widget->geometryFit(172, 0, 500, 58, m_Private->m_FileNameText);
    QWidget::resizeEvent(event);
}

void VideoStatusWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Utility::multimediaAlphaColor()));
    QWidget::paintEvent(event);
}

void VideoStatusWidget::customEvent(QEvent *event)
{
    qDebug() << "VideoStatusWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::VideoToolBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void VideoStatusWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Video: {
        if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    default : {
        break;
    }
    }
}

void VideoStatusWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index,const QString &fileName, const int endTime)
{
    qDebug() << "VideoStatusWidget::onVideoPlayerInformation" << fileName;
    m_Private->m_FileNameText->setText(fileName);
    m_Private->m_FileNameText->setVisible(true);
}

VideoStatusWidgetPrivate::VideoStatusWidgetPrivate(VideoStatusWidget *parent)
    : m_Parent(parent)
{
    m_TitleText = NULL;
    m_FileNameText = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

VideoStatusWidgetPrivate::~VideoStatusWidgetPrivate()
{
}

void VideoStatusWidgetPrivate::initialize()
{
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    int fontPointSize(22 * g_Widget->widthScalabilityFactor());
    m_TitleText->setFontPointSize(fontPointSize);
    m_TitleText->setText(SourceString::Video);
    m_TitleText->show();
    m_FileNameText = new TextWidget(m_Parent);
    m_FileNameText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_FileNameText->setFontPointSize(fontPointSize);
    m_FileNameText->setLanguageType(TextWidget::T_NoTranslate);
    m_FileNameText->show();
    m_Parent->setVisible(true);
}

void VideoStatusWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void VideoStatusWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
