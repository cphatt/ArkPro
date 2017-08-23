#include "GeneralSlider.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/Slider.h"
#include "UserInterface/Common/TextWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QDebug>

class GeneralSliderPrivate
{
    Q_DISABLE_COPY(GeneralSliderPrivate)
public:
    explicit GeneralSliderPrivate(GeneralSlider* parent);
    ~GeneralSliderPrivate();
    void initialize();
    void connectAllSlots();
    TextWidget* m_MinimumText;
    TextWidget* m_MaxmumText;
    BmpButton* m_MinusBtn;
    BmpButton* m_PlusBtn;
    Slider* m_Slider;
private:
    GeneralSlider* m_Parent;
};

GeneralSlider::GeneralSlider(QWidget *parent)
    : QWidget(parent)
    , m_Private(new GeneralSliderPrivate(this))
{  
}

GeneralSlider::~GeneralSlider()
{
}

void GeneralSlider::setMinimumValue(const int value)
{
    m_Private->m_MinimumText->setText(QString::number(value));
}

void GeneralSlider::setMaximumValue(const int value)
{
    m_Private->m_MaxmumText->setText(QString::number(value));
}

void GeneralSlider::setTickMarksMillesimal(const int millesimal)
{
    m_Private->m_Slider->setTickMarksMillesimal(millesimal);
}

void GeneralSlider::resizeEvent(QResizeEvent *event)
{
    int width(100);
    int height(40);
    g_Widget->geometryFit(577 - 536, 0, width, height, m_Private->m_MinimumText);
    g_Widget->geometryFit(577 - 536 + (1027 - 577) - width, 0, width, height, m_Private->m_MaxmumText);
    width = 561 - 536;
    g_Widget->geometryFit(536 - 536, 0 + (93 - height) * 0.5, width, height, m_Private->m_MinusBtn);
    g_Widget->geometryFit(1043 - 536, 0 + (93 - height) * 0.5, width, height, m_Private->m_PlusBtn);
    g_Widget->geometryFit(577 - 536, 0 + (93 - height) * 0.5, 1027 - 577, height, m_Private->m_Slider);
    QWidget::resizeEvent(event);
}

void GeneralSlider::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

GeneralSliderPrivate::GeneralSliderPrivate(GeneralSlider *parent)
    : m_Parent(parent)
{
    m_MinimumText = NULL;
    m_MaxmumText = NULL;
    m_MinusBtn = NULL;
    m_PlusBtn = NULL;
    m_Slider = NULL;
    initialize();
    connectAllSlots();
}

GeneralSliderPrivate::~GeneralSliderPrivate()
{
}

void GeneralSliderPrivate::initialize()
{
    m_MinimumText = new TextWidget(m_Parent);
    m_MinimumText->setLanguageType(TextWidget::T_NoTranslate);
    m_MinimumText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_MinimumText->show();
    m_MaxmumText = new TextWidget(m_Parent);
    m_MaxmumText->setLanguageType(TextWidget::T_NoTranslate);
    m_MaxmumText->setAlignmentFlag(Qt::AlignRight | Qt::AlignVCenter);
    m_MaxmumText->show();
    m_MinusBtn = new BmpButton(m_Parent);
    m_MinusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/GeneralSliderMinusNormal"));
    m_MinusBtn->setPressBmpPath(QString(":/Images/Resources/Images/GeneralSliderMinusNormal"));
    m_MinusBtn->show();
    m_PlusBtn = new BmpButton(m_Parent);
    m_PlusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/GeneralSliderPlusNormal"));
    m_PlusBtn->setPressBmpPath(QString(":/Images/Resources/Images/GeneralSliderPlusNormal"));
    m_PlusBtn->show();
    m_Slider = new Slider(m_Parent);
    m_Slider->setTickMarksSize(QSize(40 * g_Widget->widthScalabilityFactor(), 40 * g_Widget->heightScalabilityFactor()));
    m_Slider->setBackgroundBmpPath(QString(":/Images/Resources/Images/GeneralSliderBackground"));
    m_Slider->setTickMarkTickMarkslBmpPath(QString(":/Images/Resources/Images/EffectSoundSliderTickMarksBackground"));
    m_Slider->setAllowPress(false);
    m_Slider->setAllowMove(false);
    m_Slider->show();
    m_Parent->setVisible(true);
}

void GeneralSliderPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_MinusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,   SIGNAL(minusBtnRelease()),
                     type);
    QObject::connect(m_PlusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SIGNAL(plusBtnRelease()),
                     type);
    QObject::connect(m_Slider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,  SIGNAL(tickMarksMillesimalEnd(const int)),
                     type);
}
