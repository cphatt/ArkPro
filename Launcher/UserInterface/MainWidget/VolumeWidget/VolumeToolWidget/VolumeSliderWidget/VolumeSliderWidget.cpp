#include "VolumeSliderWidget.h"
#include "UserInterface/Common/BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/Slider.h"
#include "AutoConnect.h"
#include <QDebug>

class VolumeSliderWidgetPrivate
{
    Q_DISABLE_COPY(VolumeSliderWidgetPrivate)
public:
    explicit VolumeSliderWidgetPrivate(VolumeSliderWidget* parent);
    ~VolumeSliderWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpButton* m_MinusBtn;
    Slider* m_Slider;
    BmpButton* m_PlusBtn;
private:
    VolumeSliderWidget* m_Parent;
};

VolumeSliderWidget::VolumeSliderWidget(QWidget* parent)
    : QWidget(parent)
    , m_Private(new VolumeSliderWidgetPrivate(this))
{
}

VolumeSliderWidget::~VolumeSliderWidget()
{
}

void VolumeSliderWidget::setTickMarksMillesimal(const int millesimal)
{
    m_Private->m_Slider->setTickMarksMillesimal(millesimal);
}

void VolumeSliderWidget::resizeEvent(QResizeEvent *event)
{
    int a(27);
    g_Widget->geometryFit(0, 180, 853, 180, this);
    g_Widget->geometryFit(152 + a, (180 - 37) * 0.5 - 30, 31, 37, m_Private->m_MinusBtn);
    g_Widget->geometryFit(214 + a, (180 - 40) * 0.5 - 30, 619 * 0.6, 40, m_Private->m_Slider);
    g_Widget->geometryFit(853 + a - 52 - 31 - 150, (180 - 37) * 0.5 - 30, 31, 37, m_Private->m_PlusBtn);
    QWidget::resizeEvent(event);
}

VolumeSliderWidgetPrivate::VolumeSliderWidgetPrivate(VolumeSliderWidget *parent)
    : m_Parent(parent)
{
    m_MinusBtn = NULL;
    m_Slider = NULL;
    m_PlusBtn = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

VolumeSliderWidgetPrivate::~VolumeSliderWidgetPrivate()
{
}

void VolumeSliderWidgetPrivate::initialize()
{
    m_MinusBtn = new BmpButton(m_Parent);
    m_MinusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderMinusNormal"));
    m_MinusBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderMinusNormal"));
    m_MinusBtn->show();
    m_Slider = new Slider(m_Parent);
    m_Slider->setTickMarksSize(QSize(40 * g_Widget->widthScalabilityFactor(), 40 * g_Widget->heightScalabilityFactor()));
    m_Slider->setBackgroundBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderBackground"));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderTickMarksBackground"));
    m_Slider->setAllowMove(false);
    m_Slider->show();
    m_PlusBtn = new BmpButton(m_Parent);
    m_PlusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderPlusNormal"));
    m_PlusBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderPlusNormal"));
    m_PlusBtn->show();
}

void VolumeSliderWidgetPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_MinusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,   SIGNAL(minusBtnRelease()),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent, SIGNAL(tickMarksMillesimalEnd(const int)),
                     type);
    QObject::connect(m_PlusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SIGNAL(plusBtnRelease()),
                     type); 
}
