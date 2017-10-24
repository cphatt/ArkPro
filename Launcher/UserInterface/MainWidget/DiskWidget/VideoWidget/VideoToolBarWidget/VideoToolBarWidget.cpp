#include "VideoToolBarWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/Slider.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/TextWidget.h"
#include <QPainter>
#include <QVariant>
#include <QDebug>

class VideoToolBarWidgetPrivate
{
    Q_DISABLE_COPY(VideoToolBarWidgetPrivate)
public:
    enum FunctionType {
        FT_Volume = 0,
        FT_Video = 1,
    };
    explicit VideoToolBarWidgetPrivate(VideoToolBarWidget* parent);
    ~VideoToolBarWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void switchFunction();
    QString convertTime(const int time);
    Slider* m_Slider;
    TextWidget* m_ElapsedTimeText;
    TextWidget* m_EndTimeText;
    BmpButton* m_VolumeBtn;
    BmpButton* m_PreviousBtn;
    BmpButton* m_ToggleBtn;
    BmpButton* m_NextBtn;
    BmpButton* m_FMBtn;
    BmpButton* m_EffectBtn;
    BmpButton* m_IRBtn;
    BmpWidget* m_Background;
    BmpWidget* m_SliderBlock;
    BmpWidget* m_SliderPress;
    BmpButton* m_SwitchFunctionBtn;

    FunctionType m_FunctionType;
private:
    VideoToolBarWidget* m_Parent;
};

VideoToolBarWidget::VideoToolBarWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new VideoToolBarWidgetPrivate(this))
{
}

VideoToolBarWidget::~VideoToolBarWidget()
{
}

void VideoToolBarWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 398, 800, 82, this);
    g_Widget->geometryFit(0, 398, 800, 82, m_Private->m_Background);
    g_Widget->geometryFit(0, 7, 50 * 2, 27, m_Private->m_ElapsedTimeText);
    g_Widget->geometryFit(100, 7, 600, 35, m_Private->m_Slider);
    g_Widget->geometryFit(100 , 7, 600, 27, m_Private->m_SliderBlock);
    g_Widget->geometryFit(100 , 7, 0, 27, m_Private->m_SliderPress);
    g_Widget->geometryFit(800 - 100, 7, 50 * 2, 27, m_Private->m_EndTimeText);
    int width(54);
    int height(48);
    g_Widget->geometryFit(254 , 34, width, height, m_Private->m_PreviousBtn);
    g_Widget->geometryFit(372 + (663 - 618 - width) * 0.5, 34, width, height, m_Private->m_ToggleBtn);
    g_Widget->geometryFit(490 + (837 - 797  - width) * 0.5, 34, width, height, m_Private->m_NextBtn);
//    g_Widget->geometryFit(441 + (481 - 441 - width) * 0.5, 34, width, height, m_Private->m_FMBtn);
//    g_Widget->geometryFit(618 + (663 - 618 - width) * 0.5, 34, width, height, m_Private->m_EffectBtn);
//    g_Widget->geometryFit(797 + (837 - 797  - width) * 0.5, 34, width, height, m_Private->m_IRBtn);
    width = 54;
    height = 54;
    g_Widget->geometryFit(23 + (147 - 71 - width) * 0.5, 34, width, height, m_Private->m_VolumeBtn);
    g_Widget->geometryFit(724, 34, width, height, m_Private->m_SwitchFunctionBtn);
    QWidget::resizeEvent(event);
}

void VideoToolBarWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Utility::multimediaAlphaColor()));
    QWidget::paintEvent(event);
}

void VideoToolBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Video: {
        if (WidgetStatus::Show == status) {
            if (VideoToolBarWidgetPrivate::FT_Video == m_Private->m_FunctionType) {
                m_Private->m_PreviousBtn->setVisible(true);
                m_Private->m_ToggleBtn->setVisible(true);
                m_Private->m_NextBtn->setVisible(true);
                m_Private->m_FMBtn->setVisible(false);
                m_Private->m_EffectBtn->setVisible(false);
                m_Private->m_IRBtn->setVisible(false);
            } else {
                m_Private->m_PreviousBtn->setVisible(false);
                m_Private->m_ToggleBtn->setVisible(false);
                m_Private->m_NextBtn->setVisible(false);
                m_Private->m_FMBtn->setVisible(true);
                m_Private->m_EffectBtn->setVisible(true);
                m_Private->m_IRBtn->setVisible(true);
            }
            m_Private->m_VolumeBtn->setVisible(true);

            m_Private->m_SliderBlock->setVisible(true);
            m_Private->m_SliderPress->setVisible(true);
            m_Private->m_ElapsedTimeText->setVisible(true);
            m_Private->m_Slider->setVisible(true);
            setVisible(true);
        }
        break;
    }
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
            m_Private->m_PreviousBtn->setVisible(false);
            m_Private->m_ToggleBtn->setVisible(false);
            m_Private->m_NextBtn->setVisible(false);
            m_Private->m_VolumeBtn->setVisible(false);
            m_Private->m_Slider->setVisible(false);
            m_Private->m_SliderPress->setVisible(false);
            m_Private->m_SliderBlock->setVisible(false);
            m_Private->m_ElapsedTimeText->setVisible(false);
        }
        break;
    }
    default : {
        break;
    }
    }
}

void VideoToolBarWidget::onVideoPlayerShowStatus(const VideoPlayerShowStatus status)
{
}

void VideoToolBarWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    switch (status) {
    case VPPS_Pause: {
        m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPlayBtnNormal"));
        m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPlayBtnNormal"));
        break;
    }
    case VPPS_Play: {
        m_Private->m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPauseBtnNormal"));
        m_Private->m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPauseBtnNormal"));
        break;
    }
    default : {
        break;
    }
    }
}

void VideoToolBarWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index,const QString &fileName, const int endTime)
{
    m_Private->m_EndTimeText->setText(m_Private->convertTime(endTime));
    m_Private->m_EndTimeText->setVisible(true);
}

void VideoToolBarWidget::onVideoPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal)
{
    m_Private->m_ElapsedTimeText->setText(m_Private->convertTime(elapsedTime));
    m_Private->m_Slider->setTickMarksMillesimal(elapsedMillesimal);
    //g_Widget->geometryFit(211 , 352, elapsedMillesimal * 0.4, 35, m_Private->m_SliderPress);
    g_Widget->geometryFit(100 , 7, elapsedMillesimal * 0.56, 27, m_Private->m_SliderPress);
}

void VideoToolBarWidget::onToolButtonRelease()
{
    const BmpButton* ptr = dynamic_cast<const BmpButton*>(sender());
    if (ptr == m_Private->m_PreviousBtn) {
        g_Multimedia->videoPlayerPlayPreviousListViewIndex();
    } else if (ptr == m_Private->m_ToggleBtn) {
        g_Multimedia->videoPlayerSetPlayStatusToggle();
    } else if (ptr == m_Private->m_NextBtn) {
        g_Multimedia->videoPlayerPlayNextListViewIndex();
    } else if (ptr == m_Private->m_VolumeBtn) {
        //        g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_SwitchFunctionBtn) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        //m_Private->switchFunction();
    } else if (ptr == m_Private->m_FMBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::FMWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_EffectBtn) {

    } else if (ptr == m_Private->m_IRBtn) {

    }
}

void VideoToolBarWidget::onTickMarksMillesimalStart(const int millesimal)
{
    qDebug() <<"onTickMarksMillesimalStart" << millesimal;
    g_Multimedia->videoPlayerSetPlayStatus(VPPS_Pause);
    g_Widget->geometryFit(100 , 7, millesimal * 0.56, 27, m_Private->m_SliderPress);
}

void VideoToolBarWidget::onTickMarksMillesimalEnd(const int millesimal)
{
    qDebug() <<"onTickMarksMillesimalEnd" << millesimal;
    g_Multimedia->videoPlayerSeekToMillesimal(millesimal);
    g_Widget->geometryFit(100 , 7, millesimal * 0.56, 27, m_Private->m_SliderPress);
}

void VideoToolBarWidget::onTickMarksMillesimalChange(const int millesimal)
{
     qDebug() << millesimal;
     g_Multimedia->videoPlayerSeekToMillesimal(millesimal);
     g_Widget->geometryFit(100 , 7, millesimal * 0.56, 27, m_Private->m_SliderPress);
}
VideoToolBarWidgetPrivate::VideoToolBarWidgetPrivate(VideoToolBarWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    m_ElapsedTimeText = NULL;
    m_Slider = NULL;
    m_EndTimeText = NULL;
    m_VolumeBtn = NULL;
    m_PreviousBtn = NULL;
    m_ToggleBtn = NULL;
    m_NextBtn = NULL;
    m_FMBtn = NULL;
    m_EffectBtn = NULL;
    m_IRBtn = NULL;
    m_SwitchFunctionBtn = NULL;
    m_FunctionType = FT_Video;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

VideoToolBarWidgetPrivate::~VideoToolBarWidgetPrivate()
{
}

void VideoToolBarWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/HomeWidgetBackground"));
    m_ElapsedTimeText = new TextWidget(m_Parent);
    m_ElapsedTimeText->hide();
    m_ElapsedTimeText->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_EndTimeText = new TextWidget(m_Parent);
    m_EndTimeText->hide();
    m_EndTimeText->setFontPointSize(15 * g_Widget->widthScalabilityFactor());

    m_SliderBlock = new BmpWidget(m_Parent);
    m_SliderBlock->hide();
    m_SliderBlock->setBackgroundBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetSliderBackground"));

    m_SliderPress = new BmpWidget(m_Parent);
    m_SliderPress->hide();
    m_SliderPress->setBackgroundBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetSliderPress"));
    m_Slider = new Slider(m_Parent);
    m_Slider->setTickMarksSize(QSize(40 * g_Widget->widthScalabilityFactor(), 40 * g_Widget->heightScalabilityFactor()));
   // m_Slider->setBackgroundBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetSliderBackground"));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderTickMarksBackground"));
    m_Slider->setTickMarksMillesimal(0);
    m_Slider->hide();

    m_VolumeBtn = new BmpButton(m_Parent);
    m_VolumeBtn->show();
    m_VolumeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
    m_VolumeBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
    m_PreviousBtn = new BmpButton(m_Parent);
    m_PreviousBtn->hide();
    m_PreviousBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPreviousBtnNormal"));
    m_PreviousBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetPreviousBtnNormal"));
    m_ToggleBtn = new BmpButton(m_Parent);
    m_ToggleBtn->hide();
    m_NextBtn = new BmpButton(m_Parent);
    m_NextBtn->hide();
    m_NextBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetNextBtnNormal"));
    m_NextBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetNextBtnNormal"));
    m_FMBtn = new BmpButton(m_Parent);
    m_FMBtn->setVisible(false);
  //  m_FMBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetFMBtnNormal"));
    //m_FMBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetFMBtnNormal"));
    m_EffectBtn = new BmpButton(m_Parent);
    m_EffectBtn->setVisible(false);
  //  m_EffectBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetEffectBtnNormal"));
   // m_EffectBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetEffectBtnNormal"));
    m_IRBtn = new BmpButton(m_Parent);
    m_IRBtn->setVisible(false);
    //m_IRBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetIRBtnNormal"));
  //  m_IRBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolWidgetIRBtnNormal"));
    m_SwitchFunctionBtn = new BmpButton(m_Parent);
    m_SwitchFunctionBtn->show();
    m_SwitchFunctionBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetBack"));
    m_SwitchFunctionBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetBack-p"));

}

void VideoToolBarWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_PreviousBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,      SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ToggleBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_NextBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FMBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_EffectBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_IRBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_VolumeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_SwitchFunctionBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,            SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalStart(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalStart(const int)),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalChange(const int)),
                     m_Parent, SLOT(onTickMarksMillesimalChange(const int)),
                     type);
}

void VideoToolBarWidgetPrivate::switchFunction()
{
    if (FT_Video == m_FunctionType) {
        m_FunctionType = FT_Volume;
    } else {
        m_FunctionType = FT_Video;
    }
    g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::Show);
}

QString VideoToolBarWidgetPrivate::convertTime(const int time)
{
    QString hour("%1");
    QString minute("%1");
    QString second("%1");
    return hour.arg((time / 60) / 60, 2, 10, QChar('0'))
            + QString(":") + minute.arg((time / 60) % 60, 2, 10, QChar('0'))
            + QString(":") + second.arg(time % 60, 2, 10, QChar('0'));
}
