#include "HomeWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include "BusinessLogic/Setting/Setting.h"
#include "UserInterface/Common/BmpWidget.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include <QDateTime>
#include <QDebug>
#include <QPainter>

namespace SourceString {
//static const QString SD = QString(QObject::tr("SD"));
//static const QString USB = QString(QObject::tr("USB"));
static const QString Media = QString(QObject::tr("Media"));
static const QString Link = QString(QObject::tr("Link"));
static const QString FM = QString(QObject::tr("FM"));
static const QString AUX = QString(QObject::tr("AUX"));
//static const QString AV1 = QString(QObject::tr("Carplay"));
//static const QString AV2 = QString(QObject::tr("Carlife"));
static const QString Setting = QString(QObject::tr("Setting"));
static const QString Nav = QString(QObject::tr("Nav"));
}

class HomeWidgetPrivate
{
    Q_DISABLE_COPY(HomeWidgetPrivate)
public:
    explicit HomeWidgetPrivate(HomeWidget *parent);
    ~HomeWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpWidget* m_Background;
    BmpButton* m_Link;
    TextWidget* m_LinkText;
    BmpButton* m_Media;
    TextWidget* m_MediaText;
    BmpButton* m_Setting;
    TextWidget* m_SettingText;
    BmpButton* m_Nav;
    TextWidget* m_NavText;
    BmpButton* m_FM;
    TextWidget* m_FMText;
    BmpButton* m_AUX;
    TextWidget* m_AUXText;
    bool isUSBAlive;
    bool isSDAlive;
private:
    HomeWidget* m_Parent;
};

HomeWidget::HomeWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new HomeWidgetPrivate(this))
{
}

HomeWidget::~HomeWidget()
{
}

void HomeWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}

void HomeWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    int bmpWidth(261);
    int bmpHeight(172);
    g_Widget->geometryFit(1, 62, 260, 175, m_Private->m_Media);
    g_Widget->geometryFit((260 - bmpWidth * 0.75) / 2 , (177 - 40), bmpWidth * 0.75,  40, m_Private->m_MediaText);
    g_Widget->geometryFit(269, 61, 261, 360, m_Private->m_Link);
    g_Widget->geometryFit((260 - bmpWidth * 0.75) / 2, (360 - 40)  , bmpWidth * 0.75, 40, m_Private->m_LinkText);
    g_Widget->geometryFit(539, 61,  261, 360, m_Private->m_Setting);
    g_Widget->geometryFit((260 - bmpWidth * 0.75) / 2, (360 - 40)  , bmpWidth * 0.75, 40, m_Private->m_SettingText);
//    g_Widget->geometryFit(0, 63,  261, 172, m_Private->m_FM);
//    g_Widget->geometryFit(0, 0, bmpWidth * 0.75, 40, m_Private->m_FMText);
//    g_Widget->geometryFit(0, 243,  396, 172, m_Private->m_AUX);
//    g_Widget->geometryFit(0, 0, bmpWidth * 0.75, 40, m_Private->m_AUXText);
    g_Widget->geometryFit(1, 246, 260, 177, m_Private->m_Nav);
    g_Widget->geometryFit((260 - bmpWidth * 0.75) / 2, (177 - 40) , bmpWidth * 0.75, 40, m_Private->m_NavText);
    QWidget::resizeEvent(event);
}

void HomeWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void HomeWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        g_EventEngine->detachCustomEvent(this);
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void HomeWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)  //啊
{

    switch (type) {
    case Widget::T_Home: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_Background->setVisible(true);
            m_Private->m_Media->setVisible(true);
            m_Private->m_MediaText->setVisible(true);
            m_Private->m_Link->setVisible(true);
            m_Private->m_LinkText->setVisible(true);
            m_Private->m_Setting->setVisible(true);
            m_Private->m_SettingText->setVisible(true);
            m_Private->m_Nav->setVisible(true);
            m_Private->m_NavText->setVisible(true);
            setVisible(true);
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
            m_Private->m_Background->setVisible(false);

            m_Private->m_Media->setVisible(false);
            m_Private->m_MediaText->setVisible(false);
            m_Private->m_Link->setVisible(false);
            m_Private->m_LinkText->setVisible(false);

            m_Private->m_Setting->setVisible(true);
            m_Private->m_SettingText->setVisible(true);

            m_Private->m_Nav->setVisible(true);
            m_Private->m_NavText->setVisible(true);
        }
        break;
    }
    }
}
void HomeWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "HomeWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
            case DWS_Empty: {
                m_Private->isSDAlive = false;
                break;
            }
            case DWS_Busy: {
                m_Private->isSDAlive = true;
                break;
            }
            case DWS_Ready: {
                m_Private->isSDAlive = true;
                break;
            }
            case DWS_Remove: {
                m_Private->isSDAlive = false;
                break;
            }
            default: {
                break;
            }
        }
    }
    if (DWT_USBDisk == type) {
        switch (status) {
            case DWS_Empty: {
                m_Private->isUSBAlive = false;
                break;
            }
            case DWS_Busy: {
                m_Private->isUSBAlive = true;
                break;
            }
            case DWS_Ready: {
                m_Private->isUSBAlive = true;
                break;
            }
            case DWS_Remove: {
                m_Private->isUSBAlive = false;
                break;
            }
            default: {
                break;
            }
        }
    }
}
HomeWidgetPrivate::HomeWidgetPrivate(HomeWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;

    m_Media = NULL;
    m_Media = NULL;
    m_Link = NULL;
    m_LinkText = NULL;

    m_Setting = NULL;
    m_SettingText = NULL;
    m_Setting = NULL;
    m_SettingText = NULL;
    m_FM = NULL;
    m_FMText = NULL;
    m_AUX = NULL;
    m_AUXText = NULL;

    isUSBAlive = false;
    isSDAlive = false;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(true);
}

HomeWidgetPrivate::~HomeWidgetPrivate()
{
}

void HomeWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/HomeWidgetBackground"));

    m_Media = new BmpButton(m_Parent);
    m_Media->setVisible(true);
    m_Media->setNormalBmpPath(QString(":/Images/Resources/Images/HomeWidgetMediaNormall"));
    m_Media->setPressBmpPath(QString(":/Images/Resources/Images/HomeWidgetMediaPress"));
    m_MediaText = new TextWidget(m_Media);
    m_MediaText->setVisible(true);
    m_MediaText->setText(SourceString::Media);
    int fontPointSize(25 * g_Widget->widthScalabilityFactor());
    m_MediaText->setFontPointSize(fontPointSize);
    int flag(Qt::AlignHCenter | Qt::AlignVCenter);
    m_MediaText->setAlignmentFlag(flag);
    m_Link = new BmpButton(m_Parent);
    m_Link->setVisible(true);
    m_Link->setNormalBmpPath(QString(":/Images/Resources/Images/HomeWidgetLinkNormall"));
    m_Link->setPressBmpPath(QString(":/Images/Resources/Images/HomeWidgetLinkPress"));
    m_LinkText = new TextWidget(m_Link);
    m_LinkText->setVisible(true);
    m_LinkText->setText(SourceString::Link);
    m_LinkText->setFontPointSize(fontPointSize);
    m_LinkText->setAlignmentFlag(flag);

    m_Setting = new BmpButton(m_Parent);
    m_Setting->setVisible(true);
    m_Setting->setPressBmpPath(QString(":/Images/Resources/Images/HomeWidgetSettingPress"));
    m_Setting->setNormalBmpPath(QString(":/Images/Resources/Images/HomeWidgetSettingNormal"));
    m_SettingText = new TextWidget(m_Setting);
    m_SettingText->setVisible(true);
    m_SettingText->setText(SourceString::Setting);
    m_SettingText->setFontPointSize(fontPointSize);
    m_SettingText->setAlignmentFlag(flag);

    m_Nav = new BmpButton(m_Parent);
    m_Nav->setVisible(true);
    m_Nav->setPressBmpPath(QString(":/Images/Resources/Images/HomeWidgetNavPress"));
    m_Nav->setNormalBmpPath(QString(":/Images/Resources/Images/HomeWidgetNavNormal"));
    m_NavText = new TextWidget(m_Nav);
    m_NavText->setVisible(true);
    m_NavText->setText(SourceString::Nav);
    m_NavText->setFontPointSize(fontPointSize);
    m_NavText->setAlignmentFlag(flag);

    m_FM = new BmpButton(m_Parent);
    m_FM->setVisible(true);
    m_FM->setPressBmpPath(QString(":/Images/Resources/Images/HomeWidgetFMPress"));
    m_FM->setNormalBmpPath(QString(":/Images/Resources/Images/HomeWidgetFMNormall"));
    m_FMText = new TextWidget(m_FM);
    m_FMText->setVisible(true);
    m_FMText->setText(SourceString::FM);
    m_FMText->setFontPointSize(fontPointSize);
    m_FMText->setAlignmentFlag(flag);

    m_AUX = new BmpButton(m_Parent);
    m_AUX->setVisible(true);
    m_AUX->setPressBmpPath(QString(":/Images/Resources/Images/HomeWidgetAUXPress"));
    m_AUX->setNormalBmpPath(QString(":/Images/Resources/Images/HomeWidgetAUXNormal"));
    m_AUXText = new TextWidget(m_AUX);
    m_AUXText->setVisible(true);
    m_AUXText->setText(SourceString::AUX);
    m_AUXText->setFontPointSize(fontPointSize);
    m_AUXText->setAlignmentFlag(flag);
}

void HomeWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);//所
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);

    QObject::connect(m_Media, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onBmpButtonRelease()),
                     type);
    QObject::connect(m_Link,   SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onBmpButtonRelease()),
                     type);

    QObject::connect(m_Setting, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onBmpButtonRelease()),
                     type);
}

void HomeWidget::onBmpButtonRelease()
{
    if (sender() == m_Private->m_Media && (m_Private->isSDAlive || m_Private->isUSBAlive)) {
        //获得disk的状态，根据状态决定信号发不发
        //g_Widget->setWidgetType(Widget::T_Media, WidgetStatus::RequestShow); //
        if(m_Private->isUSBAlive){
            g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::RequestShow);
        }else if(m_Private->isSDAlive){
            g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::RequestShow);
        }
    } else if (sender() == m_Private->m_Link) {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);

    } else if (sender() == m_Private->m_Setting) {
        g_Widget->setWidgetType(Widget::T_Setting, WidgetStatus::RequestShow);
    }
}
