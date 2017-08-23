#include "SettingWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/Utility.h"
#include "GeneralWidget/GeneralWidget.h"
#include "LanguageWidget/LanguageWidget.h"
#include "EffectWidget/EffectWidget.h"
#include "FieldWidget/FieldWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include <QDebug>

namespace SourceString {
static const QString General = QString(QObject::tr("General"));
static const QString Language = QString(QObject::tr("Language"));
static const QString Effect = QString(QObject::tr("Effect"));
static const QString Field = QString(QObject::tr("Field"));
static const QString Info = QString(QObject::tr("Info"));
}

class SettingWidgetPrivate
{
public:
    explicit SettingWidgetPrivate(SettingWidget *parent);
    ~SettingWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_GeneralBtn;
    TextWidget* m_GeneralText;
    BmpButton* m_LanguageBtn;
    TextWidget* m_LanguageText;
    BmpButton* m_EffectBtn;
    TextWidget* m_EffectText;
    BmpButton* m_FieldBtn;
    TextWidget* m_FieldText;
    GeneralWidget* m_GeneralWidget;
    LanguageWidget* m_LanguageWidget;
    EffectWidget* m_EffectWidget;
    FieldWidget* m_FieldWidget;
private:
    SettingWidget* m_Parent;
};

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SettingWidgetPrivate(this))
    , Widget::Interface()
{
}

SettingWidget::~SettingWidget()
{
}

void SettingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    int width(165);
    int height(88);
//    g_Widget->geometryFit(0, 72, width, height, m_Private->m_GeneralBtn);
//    g_Widget->geometryFit(123, 0, width - 123, height, m_Private->m_GeneralText);
//    g_Widget->geometryFit(0, 212, width, height, m_Private->m_LanguageBtn);
//    g_Widget->geometryFit(123, 0, width - 123, height, m_Private->m_LanguageText);
//    g_Widget->geometryFit(0, 352, width, height, m_Private->m_EffectBtn);
//    g_Widget->geometryFit(123, 0, width - 123, height, m_Private->m_EffectText);
//    g_Widget->geometryFit(0, 493, width, height, m_Private->m_FieldBtn);
//    g_Widget->geometryFit(123, 0, width - 123, height, m_Private->m_FieldText);
    g_Widget->geometryFit(0, 63, width, height, m_Private->m_GeneralBtn);
    g_Widget->geometryFit(60, 0, width - 60, height, m_Private->m_GeneralText);
    g_Widget->geometryFit(0, 154, width, height, m_Private->m_LanguageBtn);
    g_Widget->geometryFit(60, 0, width - 60, height, m_Private->m_LanguageText);
    g_Widget->geometryFit(0, 244, width, height, m_Private->m_EffectBtn);
    g_Widget->geometryFit(60, 0, width - 60, height, m_Private->m_EffectText);
    g_Widget->geometryFit(0, 334, width, height, m_Private->m_FieldBtn);
    g_Widget->geometryFit(60, 0, width - 60, height, m_Private->m_FieldText);
    QWidget::resizeEvent(event);
}

void SettingWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        g_EventEngine->detachCustomEvent(this);
        m_Private->initialize();
        m_Private->connectAllSlots();
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void SettingWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "setting_ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        }
        break;
    }
    case Widget::T_Setting: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Setting, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_GeneralText->setVisible(true);
            m_Private->m_GeneralBtn->setVisible(true);
            m_Private->m_LanguageText->setVisible(true);
            m_Private->m_LanguageBtn->setVisible(true);
            m_Private->m_EffectText->setVisible(true);
            m_Private->m_EffectBtn->setVisible(true);
            m_Private->m_FieldText->setVisible(true);
            m_Private->m_FieldBtn->setVisible(true);
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingGeneral: {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Check);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_FieldBtn->setStatus(BmpButton::B_Normal);
        }
        break;
    }
    case Widget::T_SettingLanguage: {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Check);
            m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_FieldBtn->setStatus(BmpButton::B_Normal);
        }
        break;
    }
    case Widget::T_SettingEffect: {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_EffectBtn->setStatus(BmpButton::B_Check);
            m_Private->m_FieldBtn->setStatus(BmpButton::B_Normal);
        }
        break;
    }
    case Widget::T_SettingField:  {
        if (WidgetStatus::Show == status) {
            m_Private->m_GeneralBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_LanguageBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_EffectBtn->setStatus(BmpButton::B_Normal);
            m_Private->m_FieldBtn->setStatus(BmpButton::B_Check);
        }
        break;
    }
    default: {
        setVisible(false);
        break;
    }
    }
}

void SettingWidget::onBmpButtonRelease()
{
    if (sender() == m_Private->m_GeneralBtn) {
        g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_LanguageBtn) {
        g_Widget->setWidgetType(Widget::T_SettingLanguage, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_EffectBtn) {
        g_Widget->setWidgetType(Widget::T_SettingEffect, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_FieldBtn) {
        g_Widget->setWidgetType(Widget::T_SettingField, WidgetStatus::RequestShow);
    }
}

SettingWidgetPrivate::SettingWidgetPrivate(SettingWidget *parent)
    : m_Parent(parent)
{
    m_GeneralBtn = NULL;
    m_LanguageBtn = NULL;
    m_EffectBtn = NULL;
    m_FieldBtn = NULL;
    m_GeneralWidget = NULL;
    m_LanguageWidget = NULL;
    m_EffectWidget = NULL;
    m_FieldWidget = NULL;
    m_GeneralText = NULL;
    m_LanguageText = NULL;
    m_EffectText = NULL;
    m_FieldText = NULL;
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
    Q_UNUSED(g_Setting);
}

SettingWidgetPrivate::~SettingWidgetPrivate()
{
}

void SettingWidgetPrivate::initialize()
{
    m_GeneralBtn = new BmpButton(m_Parent);
    m_GeneralBtn->hide();
    m_GeneralBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolSettingBtnNormal"));
    m_GeneralBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolSettingBtnNormal"));
    m_GeneralBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolSettingBtnPress"));
    m_GeneralText = new TextWidget(m_GeneralBtn);
    m_GeneralText->hide();
    m_GeneralText->setText(SourceString::General);
    int fontPointSize(17 * g_Widget->widthScalabilityFactor());
    m_GeneralText->setFontPointSize(fontPointSize);
    m_GeneralText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_LanguageBtn = new BmpButton(m_Parent);
    m_LanguageBtn->hide();
    m_LanguageBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolLanguageBtnNormal"));
    m_LanguageBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolLanguageBtnNormal"));
    m_LanguageBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolLanguageBtnPress"));
    m_LanguageText = new TextWidget(m_LanguageBtn);
    m_LanguageText->hide();
    m_LanguageText->setText(SourceString::Language);
    m_LanguageText->setFontPointSize(fontPointSize);
    m_LanguageText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_EffectBtn = new BmpButton(m_Parent);
    m_EffectBtn->hide();
    m_EffectBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolEffectBtnNormal"));
    m_EffectBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolEffectBtnNormal"));
    m_EffectBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolEffectBtnPress"));
    m_EffectText = new TextWidget(m_EffectBtn);
    m_EffectText->hide();
    m_EffectText->setText(SourceString::Effect);
    m_EffectText->setFontPointSize(fontPointSize);
    m_EffectText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_FieldBtn = new BmpButton(m_Parent);
    m_FieldBtn->hide();
    m_FieldBtn->setNormalBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnNormal"));
    m_FieldBtn->setPressBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnNormal"));
    m_FieldBtn->setCheckBmpPath(QString(":/Images/Resources/Images/SettingToolFieldBtnPress"));
    m_FieldText = new TextWidget(m_FieldBtn);
    m_FieldText->hide();
    m_FieldText->setText(SourceString::Info);
    m_FieldText->setFontPointSize(fontPointSize);
    m_FieldText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_GeneralWidget = new GeneralWidget(m_Parent);
    m_LanguageWidget = new LanguageWidget(m_Parent);
    m_EffectWidget = new EffectWidget(m_Parent);
    m_FieldWidget = new FieldWidget(m_Parent);
}

void SettingWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void SettingWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_GeneralBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onBmpButtonRelease()),
                     type);
    QObject::connect(m_LanguageBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,      SLOT(onBmpButtonRelease()),
                     type);
    QObject::connect(m_EffectBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onBmpButtonRelease()),
                     type);
    QObject::connect(m_FieldBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,   SLOT(onBmpButtonRelease()),
                     type);
}

