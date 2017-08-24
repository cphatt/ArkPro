#include "TabBarWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "AutoConnect.h"
#include <QEvent>
#include <QPainter>
#include <QDebug>
#include <QPixmap>
#include <QVariant>

class TabBarWidgetPrivate
{
    Q_DISABLE_COPY(TabBarWidgetPrivate)
public:
    explicit TabBarWidgetPrivate(TabBarWidget *parent);
    ~TabBarWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_TurnOffDisplayBtn;
    BmpButton* m_HomeBtn;
    BmpButton* m_BackBtn;
    BmpButton* m_FMBtn;
    BmpButton* m_EffectBtn;
    BmpButton* m_IRBtn;
    BmpButton* m_VolumeBtn;
    BmpWidget* m_Background;
private:
    TabBarWidget* m_Parent;
};

TabBarWidget::TabBarWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new TabBarWidgetPrivate(this))
{
}

TabBarWidget::~TabBarWidget()
{
}

void TabBarWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
}

void TabBarWidget::customEvent(QEvent *event)
{
    qDebug() << "TabBarWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::TabBarWidgetAddChild: {
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

void TabBarWidget::resizeEvent(QResizeEvent *event)
{
    int width(71);
    int height(53);
    g_Widget->geometryFit(0, g_Widget->baseWindowHeight() - height, g_Widget->baseWindowWidth(), height, this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), height, m_Private->m_Background);
    g_Widget->geometryFit((84 + (168 - 84 - width) * 0.5 )*0.625, 0, width, height, m_Private->m_HomeBtn);
    g_Widget->geometryFit((440 + (524 - 440 - width) * 0.5)*0.625, 0, width, height, m_Private->m_FMBtn);
   // g_Widget->geometryFit((608 + (692 - 608 - width) * 0.5)*0.625, 0, width, height, m_Private->m_EffectBtn);
   // g_Widget->geometryFit((776 + (860 - 776 - width) * 0.5)*0.625, 0, width, height, m_Private->m_IRBtn);
    g_Widget->geometryFit((944 + (1028 - 944 - width) * 0.5)*0.625, 0, width, height, m_Private->m_VolumeBtn);
    g_Widget->geometryFit((1112 + (1196 - 1112 - width) * 0.5)*0.625, 0, width, height, m_Private->m_BackBtn);
    g_Widget->geometryFit((1112 + (1196 - 1112 - width) * 0.5)*0.625, 0, width, height, m_Private->m_TurnOffDisplayBtn);
    QWidget::resizeEvent(event);
}

void TabBarWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    if (WidgetStatus::Show == status)
        switch (type) {
        case Widget::T_Home: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TurnOffDisplayBtn->setVisible(true);
            m_Private->m_HomeBtn->setVisible(false);
            m_Private->m_BackBtn->setVisible(false);
            m_Private->m_FMBtn->setVisible(true);
            m_Private->m_EffectBtn->setVisible(true);
            m_Private->m_IRBtn->setVisible(true);
            m_Private->m_VolumeBtn->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_SDDisk:
        case Widget::T_USBDisk:
        case Widget::T_Music:
        case Widget::T_AV1:
        case Widget::T_AV2:
        case Widget::T_SDDiskMusic:
        case Widget::T_SDDiskImage:
        case Widget::T_SDDiskVideo:
        case Widget::T_USBDiskMusic:
        case Widget::T_USBDiskImage:
        case Widget::T_USBDiskVideo:
        case Widget::T_Link:
        case Widget::T_Media:
        case Widget::T_SettingGeneral:
        case Widget::T_SettingLanguage:
        case Widget::T_SettingEffect:
        case Widget::T_SettingField: {
            m_Private->m_Background->setVisible(true);
            m_Private->m_TurnOffDisplayBtn->setVisible(false);
            m_Private->m_HomeBtn->setVisible(true);
            m_Private->m_BackBtn->setVisible(true);
            m_Private->m_FMBtn->setVisible(true);
            m_Private->m_EffectBtn->setVisible(true);
            m_Private->m_IRBtn->setVisible(true);
            m_Private->m_VolumeBtn->setVisible(true);
            setVisible(true);
            break;
        }
        case Widget::T_Mirror:
        case Widget::T_Carplay:
        case Widget::T_Carlife:
        case Widget::T_AV1FullScreen:
        case Widget::T_AV2FullScreen:
        case Widget::T_Image:
        case Widget::T_ImageFullScreen:
        case Widget::T_Video:
        case Widget::T_VideoFullScreen: {
            setVisible(false);
            m_Private->m_Background->setVisible(false);
            m_Private->m_TurnOffDisplayBtn->setVisible(false);
            m_Private->m_HomeBtn->setVisible(false);
            m_Private->m_BackBtn->setVisible(false);
            m_Private->m_FMBtn->setVisible(false);
            m_Private->m_EffectBtn->setVisible(false);
            m_Private->m_IRBtn->setVisible(false);
            m_Private->m_VolumeBtn->setVisible(false);
            break;
        }
        default: {
            break;
        }
        }
}

void TabBarWidget::onTabBarButtonRelease()
{
    const BmpButton* ptr = dynamic_cast<const BmpButton*>(sender());
    if(ptr == m_Private->m_TurnOffDisplayBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::IdleWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_HomeBtn) {
        g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
    } else if (ptr == m_Private->m_FMBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::FMWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_EffectBtn) {

    } else if (ptr == m_Private->m_IRBtn) {

    } else if (ptr == m_Private->m_VolumeBtn) {
        EventEngine::CustomEvent<QString> event(CustomEventType::VolumeWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event);
    } else if (ptr == m_Private->m_BackBtn) {
        g_Widget->setWidgetType(Widget::T_Back, WidgetStatus::RequestShow);
    } else {
    }
}

TabBarWidgetPrivate::TabBarWidgetPrivate(TabBarWidget *parent)
    : m_Parent(parent)
{
    m_TurnOffDisplayBtn = NULL;
    m_HomeBtn = NULL;
    m_VolumeBtn = NULL;
    m_BackBtn = NULL;
    m_Background = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(true);
}

TabBarWidgetPrivate::~TabBarWidgetPrivate()
{
}

void TabBarWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/TabBarWidgetBackground"));
    m_TurnOffDisplayBtn = new BmpButton(m_Parent);
    m_TurnOffDisplayBtn->setVisible(true);
    m_TurnOffDisplayBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetTurnOffDisplayBtnNormal"));
    m_TurnOffDisplayBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetTurnOffDisplayBtnNormal"));
    m_HomeBtn = new BmpButton(m_Parent);
    m_HomeBtn->setVisible(false);
    m_HomeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetHomeBtnNormal"));
    m_HomeBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetHomeBtnNormal"));
    m_BackBtn = new BmpButton(m_Parent);
    m_BackBtn->setVisible(false);
    m_BackBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetBackBtnNormal"));
    m_BackBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetBackBtnNormal"));
    m_FMBtn = new BmpButton(m_Parent);
    m_FMBtn->setVisible(true);
    //m_FMBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetFMBtnNormal"));
    //m_FMBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetFMBtnNormal"));
    m_EffectBtn = new BmpButton(m_Parent);
    m_EffectBtn->setVisible(true);
   // m_EffectBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetEffectBtnNormal"));
    //m_EffectBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetEffectBtnNormal"));
    m_IRBtn = new BmpButton(m_Parent);
    m_IRBtn->setVisible(true);
   // m_IRBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetIRBtnNormal"));
    //m_IRBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetIRBtnNormal"));
    m_VolumeBtn = new BmpButton(m_Parent);
    m_VolumeBtn->setVisible(true);
    m_VolumeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
    m_VolumeBtn->setPressBmpPath(QString(":/Images/Resources/Images/TabBarWidgetVolumeBtnNormal"));
}

void TabBarWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void TabBarWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_TurnOffDisplayBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,            SLOT(onTabBarButtonRelease()),
                     type);
    QObject::connect(m_HomeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onTabBarButtonRelease()),
                     type);
    QObject::connect(m_FMBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onTabBarButtonRelease()),
                     type);
    QObject::connect(m_EffectBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onTabBarButtonRelease()),
                     type);
    QObject::connect(m_IRBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onTabBarButtonRelease()),
                     type);
    QObject::connect(m_VolumeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onTabBarButtonRelease()),
                     type);
    QObject::connect(m_BackBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onTabBarButtonRelease()),
                     type);
}
