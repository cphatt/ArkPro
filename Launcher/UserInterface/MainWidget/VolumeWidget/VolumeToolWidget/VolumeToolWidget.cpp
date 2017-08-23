#include "VolumeToolWidget.h"
#include "UserInterface/Common/BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/TextWidget.h"
#include "AutoConnect.h"
#include "VolumeSliderWidget/VolumeSliderWidget.h"
#include <QDebug>

namespace SourceString {
static const QString Volume = QString(QObject::tr("Volume"));
}

class VolumeToolWidgetPrivate
{
    Q_DISABLE_COPY(VolumeToolWidgetPrivate)
public:
    explicit VolumeToolWidgetPrivate(VolumeToolWidget* parent);
    ~VolumeToolWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background;
    TextWidget* m_TitleText;
    VolumeSliderWidget* m_VolumeSliderWidget;
    short int m_Volume;
private:
    VolumeToolWidget* m_Parent;
};

VolumeToolWidget::VolumeToolWidget(QWidget* parent)
    : QWidget(parent)
    , Audio::Interface()
    , m_Private(new VolumeToolWidgetPrivate(this))
{
}

VolumeToolWidget::~VolumeToolWidget()
{
}

void VolumeToolWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 50, 800, 360, this);
    g_Widget->geometryFit(0, 0, 853, 360, m_Private->m_Background);
    g_Widget->geometryFit(0, 0, 853, 180, m_Private->m_TitleText);
    QWidget::resizeEvent(event);
}

bool VolumeToolWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease: {
        event->accept();
        return true;
        break;
    }
    default: {
        break;
    }
    }
    QWidget::event(event);
}

void VolumeToolWidget::changeEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::LanguageChange: {
        m_Private->m_TitleText->setText(QString(QObject::tr(SourceString::Volume.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_Volume));
        break;
    }
    default: {
        break;
    }
    }
    QWidget::changeEvent(event);
}

void VolumeToolWidget::onFMChange(int freq)
{
    qDebug() << "VolumeToolWidget::onVolumeRangeChange" << freq;
}

void VolumeToolWidget::onFMIsOpen(int open)
{
    qDebug() << "VolumeToolWidget::onFMIsOpen" << open;
}

void VolumeToolWidget::onVolumeChange(int volume)  //z回调了
{
    qDebug() << "VolumeToolWidget::onVolumeChange" << volume;
    m_Private->m_Volume = volume;
    m_Private->m_TitleText->setText(QString(QObject::tr(SourceString::Volume.toLocal8Bit().constData())) + QString(" ") + QString::number(m_Private->m_Volume));
    m_Private->m_VolumeSliderWidget->setTickMarksMillesimal(1000 * volume / (40 - 0));
}

void VolumeToolWidget::onVolumeRangeChange(int min, int max)
{
    qDebug() << "VolumeToolWidget::onVolumeRangeChange" << min << max;
}

void VolumeToolWidget::onMinusBtnRelease()
{
    qDebug() << "VolumeToolWidget::onMinusBtnRelease";
    g_Audio->requestDecreaseVolume();
}

void VolumeToolWidget::onPlusBtnRelease()
{
    qDebug() << "VolumeToolWidget::onPlusBtnRelease";
    g_Audio->requestIncreaseVolume();
}

void VolumeToolWidget::onTickMarksMillesimalEnd(const int millesimal)
{
    int volume(((40 - 0) * millesimal / 1000));
    qDebug() << "VolumeToolWidget::onTickMarksMillesimalEnd" << volume;
    g_Audio->requestSetVolume(volume);
}

VolumeToolWidgetPrivate::VolumeToolWidgetPrivate(VolumeToolWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    m_TitleText = NULL;
    m_VolumeSliderWidget = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

VolumeToolWidgetPrivate::~VolumeToolWidgetPrivate()
{
}

void VolumeToolWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/MessageBackground"));
    m_Background->show();
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setAlignmentFlag(Qt::AlignCenter);
    m_TitleText->setLanguageType(TextWidget::T_NoTranslate);
    int fontPointSize(40 * g_Widget->widthScalabilityFactor());
    m_TitleText->setFontPointSize(fontPointSize);
    m_Volume = 0;
    m_TitleText->show();
    m_VolumeSliderWidget = new VolumeSliderWidget(m_Parent);
}

void VolumeToolWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_VolumeSliderWidget, SIGNAL(minusBtnRelease()),
                     m_Parent,             SLOT(onMinusBtnRelease()),
                     type);
    QObject::connect(m_VolumeSliderWidget, SIGNAL(plusBtnRelease()),
                     m_Parent,             SLOT(onPlusBtnRelease()),
                     type);
    QObject::connect(m_VolumeSliderWidget, SIGNAL(tickMarksMillesimalEnd(const int)),
                     m_Parent,             SLOT(onTickMarksMillesimalEnd(const int)),
                     type);
}
