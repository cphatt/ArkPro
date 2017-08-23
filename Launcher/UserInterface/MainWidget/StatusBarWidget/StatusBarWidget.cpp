#include "StatusBarWidget.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include <QPainter>
#include <QDebug>
#include <QDateTime>
#include <QEvent>
#include <QVariant>

namespace SourceString {
static const QString Home = QString(QObject::tr("Home"));
static const QString SD_Files = QString(QObject::tr("SD>Files"));
static const QString USB_Files = QString(QObject::tr("USB>Files"));
static const QString Music = QString(QObject::tr("Music"));
static const QString Link = QString(QObject::tr("Link"));
static const QString Setting_General = QString(QObject::tr("Setting>General"));
static const QString Setting_Language = QString(QObject::tr("Setting>Language"));
static const QString Setting_Effect = QString(QObject::tr("Setting>Effect"));
static const QString Setting_Field = QString(QObject::tr("Setting>Field"));
static const QString Setting_Info = QString(QObject::tr("Setting>Info"));
static const QString AV1 = QString(QObject::tr("AV1"));
static const QString AV2 = QString(QObject::tr("AV2"));
static const QString Media = QString(QObject::tr("Media"));

}

class StatusBarWidgetPrivate
{
    Q_DISABLE_COPY(StatusBarWidgetPrivate)
public:
    explicit StatusBarWidgetPrivate(StatusBarWidget *parent);
    ~StatusBarWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpWidget* m_Background;
    TextWidget* m_TitleText;
    TextWidget* m_TimeText;
    TextWidget* m_DateText;
private:
    StatusBarWidget* m_Parent;
};

StatusBarWidget::StatusBarWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Setting::Interface()
    , m_Private(new StatusBarWidgetPrivate(this))
{
}

StatusBarWidget::~StatusBarWidget()
{
}

void StatusBarWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
}

void StatusBarWidget::resizeEvent(QResizeEvent* event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseStatusBarHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseStatusBarHeight(), m_Private->m_Background);
    g_Widget->geometryFit(50, 0, 266, g_Widget->baseStatusBarHeight(), m_Private->m_TimeText);
    g_Widget->geometryFit(266, 0, 266, g_Widget->baseStatusBarHeight(), m_Private->m_TitleText);
    g_Widget->geometryFit(532, 0, 266, g_Widget->baseStatusBarHeight(), m_Private->m_DateText);
    QWidget::resizeEvent(event);
}

void StatusBarWidget::customEvent(QEvent* event)
{
    switch (event->type()) {
    case CustomEventType::StatusBarWidgetAddChild: {
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

void StatusBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "StatusBarWidget::ontWidgetTypeChange" << type << status;
    if (WidgetStatus::Show == status) {
        switch (type) {
        case Widget::T_Home: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Home);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_Link: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Link);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
		case Widget::T_Media: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Media);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_Music: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Music);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SDDisk:
        case Widget::T_SDDiskMusic:
        case Widget::T_SDDiskImage:
        case Widget::T_SDDiskVideo: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::SD_Files);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_USBDisk:
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::USB_Files);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingGeneral: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_General);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingLanguage: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Language);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingEffect: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Effect);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SettingField: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::Setting_Info);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_AV1: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::AV1);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_AV2: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TitleText->setText(SourceString::AV2);
            m_Private->m_TimeText->setVisible(true);
            m_Private->m_TitleText->setVisible(true);
            m_Private->m_DateText->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_AV1FullScreen:
        case Widget::T_AV2FullScreen:
        case Widget::T_Mirror:
        case Widget::T_Carplay:
        case Widget::T_Video:
        case Widget::T_VideoFullScreen:
        case Widget::T_Image:
        case Widget::T_ImageFullScreen: {
            setVisible(false);
            m_Private->m_Background->setVisible(false);
            m_Private->m_TimeText->setVisible(false);
            m_Private->m_TitleText->setVisible(false);
            m_Private->m_DateText->setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
    }
}

void StatusBarWidget::onDateTimeChange(const QString &date, const QString &time)
{
    m_Private->m_DateText->setText(date);
    m_Private->m_TimeText->setText(time);
}

void StatusBarWidget::onLanguageTranslateChange(const int language)
{
}

void StatusBarWidget::onBrightnessChange(const int value)
{
}

void StatusBarWidget::onContrastChange(const int value)
{
}

void StatusBarWidget::onHueChange(const int value)
{
}

StatusBarWidgetPrivate::StatusBarWidgetPrivate(StatusBarWidget* parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    m_TitleText = NULL;
    m_TimeText = NULL;
    m_DateText = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(true);
}

StatusBarWidgetPrivate::~StatusBarWidgetPrivate()
{
}

void StatusBarWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/StatusBarWidgetBackground"));
    int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    m_TitleText = new TextWidget(m_Parent);
    m_TitleText->setFontPointSize(fontPointSize);
    m_TitleText->setVisible(true);
    m_TimeText = new TextWidget(m_Parent);
    m_TimeText->setFontPointSize(fontPointSize);
    m_TimeText->setVisible(true);
    m_DateText = new TextWidget(m_Parent);
    m_DateText->setFontPointSize(fontPointSize);
    m_DateText->setVisible(true);
}

void StatusBarWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void StatusBarWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
}
