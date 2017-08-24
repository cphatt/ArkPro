#include "EffectSoundWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/TextWidget.h"
#include "EffectSoundSlider/EffectSoundSlider.h"
#include "UserInterface/Common/BmpWidget.h"
#include "AutoConnect.h"
#include <QEvent>
#include <QPainter>
#include <QDebug>

namespace SourceString {
static const QString High_Pitch = QString(QObject::tr("VOL"));

}

class EffectSoundWidgetPrivate
{
    Q_DISABLE_COPY(EffectSoundWidgetPrivate)
public:
    explicit EffectSoundWidgetPrivate(EffectSoundWidget* parent);
    ~EffectSoundWidgetPrivate();
    void initialize();
    void connectAllSlots();
    TextWidget* m_HighPitchText;
    short int m_HightPitchValue;
    EffectSoundSlider* m_HighPitchSlider;


    BmpWidget* m_Background;
private:
    EffectSoundWidget* m_Parent;
};

EffectSoundWidget::EffectSoundWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new EffectSoundWidgetPrivate(this))
{
}

EffectSoundWidget::~EffectSoundWidget()
{
}

void EffectSoundWidget::resizeEvent(QResizeEvent *event)
{

    g_Widget->geometryFit(0, 0, 625, 355, this);
    g_Widget->geometryFit(0, 0, 625, 355, m_Private->m_Background);
    int width(120);
    int height(50);
    g_Widget->geometryFit(273 + (433 - 333 - width) * 0.5 - 278, 154 + (187 - 154 - height) * 0.5 - 73, width, height, m_Private->m_HighPitchText);


    width = 500;
    height = 68;

    g_Widget->geometryFit(380 - 278,  72 - (height - 50), width, height, m_Private->m_HighPitchSlider);

    QWidget::resizeEvent(event);
}

void EffectSoundWidget::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange: {
        m_Private->m_HighPitchText->setText(QString(QObject::tr(SourceString::High_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_HightPitchValue));

        break;
    }
    default: {
        break;
    }
    }
    QWidget::changeEvent(event);
}

void EffectSoundWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void EffectSoundWidget::onVolumeChange(int type, int volume)  //z回调了
{
    qDebug() << "EffectSoundWidget::onVolumeChange" << volume;
    m_Private->m_HightPitchValue = volume;
    m_Private->m_HighPitchText->setText(QString(QObject::tr(SourceString::High_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_HightPitchValue));
    m_Private->m_HighPitchSlider->setTickMarksMillesimal(1000 * volume / (40 - 0));
}


void EffectSoundWidget::onMinusBtnRelease()
{
    qDebug() << "EffectSoundWidget::onMinusBtnRelease";
    g_Audio->requestDecreaseVolume();
}

void EffectSoundWidget::onPlusBtnRelease()
{
    qDebug() << "EffectSoundWidget::onPlusBtnRelease";
    g_Audio->requestIncreaseVolume();
}

void EffectSoundWidget::onTickMarksMillesimalEnd(const int millesimal)
{
    int volume(((40 - 0) * millesimal / 1000));
    qDebug() << "EffectSoundWidget::onTickMarksMillesimalEnd" << volume;
    g_Audio->requestSetVolume(volume);
}



EffectSoundWidgetPrivate::EffectSoundWidgetPrivate(EffectSoundWidget *parent)
    : m_Parent(parent)
{
    m_HighPitchText = NULL;
    m_HightPitchValue = 0;
    m_HighPitchSlider = NULL;

    m_Background = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

EffectSoundWidgetPrivate::~EffectSoundWidgetPrivate()
{
}

void EffectSoundWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->show();
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/EffectSoundWidgetBackground"));
    m_HighPitchText = new TextWidget(m_Parent);
    m_HighPitchText->setLanguageType(TextWidget::T_NoTranslate);
    int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    m_HighPitchText->setFontPointSize(fontPointSize);
    m_HighPitchText->show();
    m_HighPitchSlider = new EffectSoundSlider(m_Parent);
    m_HighPitchSlider->setMinimumValue(0);
    m_HighPitchSlider->setMaximumValue(40);
    m_HighPitchSlider->show();

    m_HighPitchText->setText(QString(QObject::tr(SourceString::High_Pitch.toLocal8Bit().constData())) + QString(" ") + QString::number(m_HightPitchValue));
  }

void EffectSoundWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_HighPitchSlider, SIGNAL(minusBtnRelease()),
                     m_Parent,             SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_HighPitchSlider, SIGNAL(plusBtnRelease()),
                     m_Parent,             SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_HighPitchSlider, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,             SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
}
