#include "VideoWidget.h"
#include "VideoStatusWidget/VideoStatusWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/Utility.h"
#include "VideoShortCutWidget/VideoShortCutWidget.h"
#include "VideoLoadingWidget/VideoLoadingWidget.h"
#include <QPainter>
#include <QBrush>
#include <QDebug>
#include <QLabel>
#include <QFileInfo>
#include <QTimer>
#include <QMouseEvent>

class VideoWidgetPrivate
{
    Q_DISABLE_COPY(VideoWidgetPrivate)
public:
    explicit VideoWidgetPrivate(VideoWidget * parent);
    ~VideoWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void videoWidgetSwitchHandler(const QString &status);
    QString convertTime(const int time);
    VideoShortCutWidget* m_VideoShortCutWidget;
    VideoStatusWidget* m_StatusWidget;
    VideoToolBarWidget* m_ToolBarWidget;
    VideoLoadingWidget* m_VideoLoadingWidget;
    QTimer *m_Timer;
    QRect m_TouchRect;
private:
    VideoWidget* m_Parent;
};

VideoWidget::VideoWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new VideoWidgetPrivate(this))
{
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
    QWidget::paintEvent(event);
}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isVisible()) {
        if (m_Private->m_TouchRect.contains(event->pos())) {
            if (m_Private->m_TouchRect == g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight())) {
                g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::Show);
            } else {
                g_Widget->setWidgetType(Widget::T_VideoFullScreen, WidgetStatus::Show);
            }
        }
    }
    QWidget::mousePressEvent(event);
}

void VideoWidget::hideEvent(QHideEvent *event)
{
    if (isHidden()) {
        g_Multimedia->videoPlayerSetPlayStatus(VPPS_Pause);
    }
    QWidget::hideEvent(event);
}

void VideoWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Video: {
        m_Private->videoWidgetSwitchHandler(status);
        break;
    }
    case Widget::T_VideoFullScreen: {
        m_Private->m_TouchRect = g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight());
        m_Private->m_Timer->stop();
        break;
    }
    default : {
        if (status == WidgetStatus::Show) {
            setVisible(false);
        }
//        setVisible(true);
        break;
    }

    }
}

void VideoWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus playStatus)
{
    switch (playStatus) {
    case VPPS_Play: {
        if (!m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->start();
        }
        //        m_Private->m_ToggleBtn->setText(SourceString::Pause);
        break;
    }
    case VPPS_Pause: {
        m_Private->m_Timer->stop();
        //        m_Private->m_ToggleBtn->setText(SourceString::Play);
        break;
    }
    case VPPS_Exit: {
        m_Private->m_Timer->stop();
        break;
    }
    default : {
        break;
    }
    }
}

void VideoWidget::onVideoPlayerInformation(const QString &fileName, const int endTime)
{
    m_Private->m_Timer->start();
    //    qDebug() << "onVideoInformation" << fileName << endTime;
    //    if (VideoWidgetPrivate::S_Normal == m_Private->m_ShowStatus) {
    //        if (!m_Private->m_Timer->isActive()) {
    //            //            if (SourceString::Pause == m_Private->m_ToggleBtn->getText()) {
    //            //                m_Private->m_Timer->start();
    //            //            }
    //        }
    //    }
}

void VideoWidget::onTimeout()
{
    if (isVisible()) {
        g_Widget->setWidgetType(Widget::T_VideoFullScreen, WidgetStatus::Show);
    }
}

VideoWidgetPrivate::VideoWidgetPrivate(VideoWidget * parent)
    : m_Parent(parent)
{
    m_Timer = NULL;
    m_VideoShortCutWidget = NULL;
    m_StatusWidget = NULL;
    m_ToolBarWidget = NULL;
    m_VideoLoadingWidget = NULL;
    m_TouchRect = QRect(0, 0, 0, 0);
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

VideoWidgetPrivate::~VideoWidgetPrivate()
{
}

void VideoWidgetPrivate::initialize()
{
    m_VideoShortCutWidget = new VideoShortCutWidget(m_Parent);
    m_StatusWidget = new VideoStatusWidget(m_Parent);
    m_ToolBarWidget = new VideoToolBarWidget(m_Parent);
    m_VideoLoadingWidget = new VideoLoadingWidget(m_Parent);
    m_Timer = new QTimer(m_Parent);
    m_Timer->setInterval(5000);
    m_Timer->setSingleShot(true);
}

void VideoWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

void VideoWidgetPrivate::videoWidgetSwitchHandler(const QString &status)
{
    if (WidgetStatus::RequestShow == status) {
        g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::Show);
    } else if (WidgetStatus::Show == status) {
        m_TouchRect = g_Widget->geometryFit(0, 88, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - 88 - 124);
        m_Timer->start();
        if (!m_Parent->isVisible()) {
            g_Multimedia->videoPlayerSetPlayStatus(VPPS_Play);
        }
        m_Parent->setVisible(true);
    }
}

QString VideoWidgetPrivate::convertTime(const int time)
{
    QString hour("%1");
    QString minute("%1");
    QString second("%1");
    return hour.arg((time / 60) / 60, 2, 10, QChar('0'))
            + QString(":") + minute.arg((time / 60) % 60, 2, 10, QChar('0'))
            + QString(":") + second.arg(time % 60, 2, 10, QChar('0'));
}
