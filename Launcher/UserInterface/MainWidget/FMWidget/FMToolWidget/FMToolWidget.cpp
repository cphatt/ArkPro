#include "FMToolWidget.h"
#include "UserInterface/Common/BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/TextWidget.h"
#include "AutoConnect.h"
#include <QDebug>

namespace SourceString {
static const QString On = QString(QObject::tr("On"));
static const QString Off = QString(QObject::tr("Off"));
}

static const int FM1_Frequence(877);
static const int FM2_Frequence(881);
static const int FM3_Frequence(885);
static const int FM4_Frequence(889);
static const int FM5_Frequence(1067);
static const int FM6_Frequence(1071);
static const int FM7_Frequence(1075);
static const int FM8_Frequence(1079);

class FMToolWidgetPrivate
{
public:
    explicit FMToolWidgetPrivate(FMToolWidget* parent);
    ~FMToolWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background;
    BmpButton* m_FM1Btn;
    TextWidget* m_FM1Text;
    BmpButton* m_FM2Btn;
    TextWidget* m_FM2Text;
    BmpButton* m_FM3Btn;
    TextWidget* m_FM3Text;
    BmpButton* m_FM4Btn;
    TextWidget* m_FM4Text;
    BmpButton* m_FM5Btn;
    TextWidget* m_FM5Text;
    BmpButton* m_FM6Btn;
    TextWidget* m_FM6Text;
    BmpButton* m_FM7Btn;
    TextWidget* m_FM7Text;
    BmpButton* m_FM8Btn;
    TextWidget* m_FM8Text;
    BmpButton* m_ToggleBtn;
    TextWidget* m_ToggleText;
private:
    FMToolWidget* m_Parent;
};

FMToolWidget::FMToolWidget(QWidget* parent)
    : QWidget(parent)
    , Audio::Interface()
    , m_Private(new FMToolWidgetPrivate(this))
{
}

FMToolWidget::~FMToolWidget()
{
}

void FMToolWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(139, g_Widget->baseStatusBarHeight() + 12, 1002, 552, this);
    qDebug() << "FMToolWidget::resizeEvent" << geometry();
    g_Widget->geometryFit(0, 0, 1002, 552, m_Private->m_Background);
    int width(161);
    int height(108);
    g_Widget->geometryFit(129, 57, width, height, m_Private->m_FM1Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM1Text);
    g_Widget->geometryFit(419, 57, width, height, m_Private->m_FM2Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM2Text);
    g_Widget->geometryFit(709, 57, width, height, m_Private->m_FM3Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM3Text);
    g_Widget->geometryFit(129, 222, width, height, m_Private->m_FM4Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM4Text);
    g_Widget->geometryFit(419, 222, width, height, m_Private->m_FM5Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM5Text);
    g_Widget->geometryFit(709, 222, width, height, m_Private->m_FM6Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM6Text);
    g_Widget->geometryFit(129, 387, width, height, m_Private->m_FM7Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM7Text);
    g_Widget->geometryFit(419, 387, width, height, m_Private->m_FM8Btn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FM8Text);
    g_Widget->geometryFit(709, 387, width, height, m_Private->m_ToggleBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_ToggleText);
    QWidget::resizeEvent(event);
}

bool FMToolWidget::event(QEvent *event)
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

void FMToolWidget::onVolumeChange(const int volume)
{
}

void FMToolWidget::onFMChange(int freq)
{
    qDebug() << "FMToolWidget::onFMChange" << freq;
    m_Private->m_FM1Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM2Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM3Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM4Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM5Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM6Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM7Btn->setStatus(BmpButton::B_Normal);
    m_Private->m_FM8Btn->setStatus(BmpButton::B_Normal);
    switch (freq) {
    case FM1_Frequence: {
        m_Private->m_FM1Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM2_Frequence: {
        m_Private->m_FM2Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM3_Frequence: {
        m_Private->m_FM3Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM4_Frequence: {
        m_Private->m_FM4Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM5_Frequence: {
        m_Private->m_FM5Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM6_Frequence: {
        m_Private->m_FM6Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM7_Frequence: {
        m_Private->m_FM7Btn->setStatus(BmpButton::B_Check);
        break;
    }
    case FM8_Frequence: {
        m_Private->m_FM8Btn->setStatus(BmpButton::B_Check);
        break;
    }
    default: {
        break;
    }
    }
}

void FMToolWidget::onFMIsOpen(int open)
{
    qDebug() << "FMWidget::OnFMIsOpen" << open;
    if (1 == open) {
        m_Private->m_ToggleText->setText(SourceString::On);
    } else {
        m_Private->m_FM1Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM2Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM3Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM4Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM5Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM6Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM7Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_FM8Btn->setStatus(BmpButton::B_Normal);
        m_Private->m_ToggleText->setText(SourceString::Off);
    }
}

void FMToolWidget::onVolumeRangeChange(int min, int max)
{

}

//case 1://87.7M
//case 2://88.1M
//case 3://88.5M
//case 4://88.9M
//case 5//106.7M
//case 6://107.1M
//case 7://107.5M
//case 8://107.9M
//88.5M -->885  111.6M-->1115

void FMToolWidget::onToolButtonRelease()
{
    qDebug() << "FMToolWidget::onToolButtonRelease";
    if (sender() == m_Private->m_FM1Btn) {
        qDebug() << "m_Private->m_FM1Btn";
        g_Audio->requestSetFreqency(FM1_Frequence);
    } else if (sender() == m_Private->m_FM2Btn) {
        qDebug() << "m_Private->m_FM2Btn";
        g_Audio->requestSetFreqency(FM2_Frequence);
    } else if (sender() == m_Private->m_FM3Btn) {
        qDebug() << "m_Private->m_FM3Btn";
        g_Audio->requestSetFreqency(FM3_Frequence);
    } else if (sender() == m_Private->m_FM4Btn) {
        qDebug() << "m_Private->m_FM4Btn";
        g_Audio->requestSetFreqency(FM4_Frequence);
    } else if (sender() == m_Private->m_FM5Btn) {
        qDebug() << "m_Private->m_FM5Btn";
        g_Audio->requestSetFreqency(FM5_Frequence);
    } else if (sender() == m_Private->m_FM6Btn) {
        qDebug() << "m_Private->m_FM6Btn";
        g_Audio->requestSetFreqency(FM6_Frequence);
    } else if (sender() == m_Private->m_FM7Btn) {
        qDebug() << "m_Private->m_FM7Btn";
        g_Audio->requestSetFreqency(FM7_Frequence);
    } else if (sender() == m_Private->m_FM8Btn) {
        qDebug() << "m_Private->m_FM8Btn";
        g_Audio->requestSetFreqency(FM8_Frequence);
    } else if (sender() == m_Private->m_ToggleBtn) {
        qDebug() << "m_Private->m_ToggleBtn";
        g_Audio->requestFMToggle();
    }
}

FMToolWidgetPrivate::FMToolWidgetPrivate(FMToolWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    m_FM1Btn = NULL;
    m_FM1Text = NULL;
    m_FM2Btn = NULL;
    m_FM2Text = NULL;
    m_FM3Btn = NULL;
    m_FM3Text = NULL;
    m_FM4Btn = NULL;
    m_FM4Text = NULL;
    m_FM5Btn = NULL;
    m_FM5Text = NULL;
    m_FM6Btn = NULL;
    m_FM6Text = NULL;
    m_FM7Btn = NULL;
    m_FM7Text = NULL;
    m_FM8Btn = NULL;
    m_FM8Text = NULL;
    m_ToggleBtn = NULL;
    m_ToggleText = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

FMToolWidgetPrivate::~FMToolWidgetPrivate()
{
}

void FMToolWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/FMToolWidgetBackground"));
    m_Background->show();

    m_FM1Btn = new BmpButton(m_Parent);
    m_FM1Btn->show();
    m_FM1Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM1Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM1Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM1Text = new TextWidget(m_FM1Btn);
    m_FM1Text->show();
    m_FM1Text->setText(QString("87.7MHz"));

    m_FM2Btn = new BmpButton(m_Parent);
    m_FM2Btn->show();
    m_FM2Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM2Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM2Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM2Text = new TextWidget(m_FM2Btn);
    m_FM2Text->show();
    m_FM2Text->setText(QString("88.1MHz"));

    m_FM3Btn = new BmpButton(m_Parent);
    m_FM3Btn->show();
    m_FM3Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM3Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM3Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM3Text = new TextWidget(m_FM3Btn);
    m_FM3Text->show();
    m_FM3Text->setText(QString("88.5MHz"));

    m_FM4Btn = new BmpButton(m_Parent);
    m_FM4Btn->show();
    m_FM4Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM4Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM4Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM4Text = new TextWidget(m_FM4Btn);
    m_FM4Text->show();
    m_FM4Text->setText(QString("88.9MHz"));

    m_FM5Btn = new BmpButton(m_Parent);
    m_FM5Btn->show();
    m_FM5Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM5Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM5Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM5Text = new TextWidget(m_FM5Btn);
    m_FM5Text->show();
    m_FM5Text->setText(QString("106.7MHz"));

    m_FM6Btn = new BmpButton(m_Parent);
    m_FM6Btn->show();
    m_FM6Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM6Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM6Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM6Text = new TextWidget(m_FM6Btn);
    m_FM6Text->show();
    m_FM6Text->setText(QString("107.1MHz"));

    m_FM7Btn = new BmpButton(m_Parent);
    m_FM7Btn->show();
    m_FM7Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM7Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM7Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM7Text = new TextWidget(m_FM7Btn);
    m_FM7Text->show();
    m_FM7Text->setText(QString("107.5MHz"));


    m_FM8Btn = new BmpButton(m_Parent);
    m_FM8Btn->show();
    m_FM8Btn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM8Btn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_FM8Btn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FM8Text = new TextWidget(m_FM8Btn);
    m_FM8Text->show();
    m_FM8Text->setText(QString("107.9MHz"));

    m_ToggleBtn = new BmpButton(m_Parent);
    m_ToggleBtn->show();
    m_ToggleBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ToggleBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ToggleBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_ToggleText = new TextWidget(m_ToggleBtn);
    m_ToggleText->show();
}

void FMToolWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Audio, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_FM1Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM2Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM3Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM4Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM5Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM6Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM7Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_FM8Btn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ToggleBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);

}
