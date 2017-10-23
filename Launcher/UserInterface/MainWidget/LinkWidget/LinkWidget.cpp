#include "LinkWidget.h"
#include "MirrorLinkWidget/MirrorLinkWidget.h"
//#include "CarplayLinkWidget/CarplayLinkWidget.h"
#include "CarlifeLinkWidget/CarlifeLinkWidget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/MainWidget/MainWidget.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/TextWidget.h"
#include "EventEngine.h"
#include <QDebug>
#include <QVariant>

namespace SourceString {
static const QString Select_Connect_Mode = QString(QObject::tr("Select connect mode!"));
static const QString AndroidMirror = QString(QObject::tr("Android Mirror"));
static const QString AndroidMirrorTip = QString(QObject::tr("1:Enable developer USB debugging options!\n"
                                                            "2:Connect to bluetooth devices!\n"
                                                            "3:Connect usb cable!\n"
                                                            "4:Press Mirror icon!"));
static const QString AppleCarPlay = QString(QObject::tr("Apple CarPlay"));
static const QString AppleCarPlayTip = QString(QObject::tr(" \n"
                                                           "1:Connect usb cable!\n"
                                                           "2:Press Carplay icon!\n"
                                                           " "));
static const QString AppleCarLife = QString(QObject::tr("Andriod CarLife"));
static const QString AppleCarLifeTip = QString(QObject::tr(" \n"
                                                           "1:Connect usb cable!\n"
                                                           "2:Press Carplay icon!\n"
                                                           " "));
}

//步骤1:手机开启开发者USB调试模式！
//步骤2:手机连接设备蓝牙!
//步骤3:连接USB数据线!
//步骤4:点击Mirror图标开始连接!
class LinkWidgetPrivate
{
    Q_DISABLE_COPY(LinkWidgetPrivate)
public:
    explicit LinkWidgetPrivate(LinkWidget *parent);
    ~LinkWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpWidget* m_Background;
    BmpWidget* m_Titleground;
    TextWidget* m_TitleText;
    BmpWidget* m_MirrorLogo;
    BmpButton* m_MirrorBtn;
    TextWidget* m_MirrorBtnText;
    TextWidget* m_MirrorTipText;

    BmpButton* m_CarplayBtn;
    TextWidget* m_CarplayBtnText;
    TextWidget* m_CarplayTipText;
    BmpWidget* m_CarlifeLogo;
    BmpButton* m_CarlifeBtn;
    TextWidget* m_CarlifeBtnText;
    TextWidget* m_CarlifeTipText;

    MirrorLinkWidget* m_MirrorLinkWidget;
//    CarplayLinkWidget* m_CarplayLinkWidget;S
    CarlifeLinkWidget* m_CarlifeLinkWidget;
private:
    LinkWidget* m_Parent;
};

LinkWidget::LinkWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new LinkWidgetPrivate(this))
{
}

LinkWidget::~LinkWidget()
{
}

void LinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    g_Widget->geometryFit(0, 62, 800, 46, m_Private->m_Titleground);
    g_Widget->geometryFit(0, 0, 800, 46, m_Private->m_TitleText);
    int width(400);
    int height(310);
    g_Widget->geometryFit(0, 117, width, height, m_Private->m_MirrorBtn);
    g_Widget->geometryFit(100, 235, 200, 40, m_Private->m_MirrorBtnText);
    g_Widget->geometryFit(154, 50, 92, 92, m_Private->m_MirrorLogo);
 //   g_Widget->geometryFit(30, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_Private->m_MirrorTipText);

    g_Widget->geometryFit(400, 117, width, height, m_Private->m_CarlifeBtn);
    g_Widget->geometryFit(100, 235, 200, 40, m_Private->m_CarlifeBtnText);
    g_Widget->geometryFit(154, 50, 92, 92, m_Private->m_CarlifeLogo);
    //   g_Widget->geometryFit(678, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_Private->m_CarplayTipText);

//    g_Widget->geometryFit(540, 117, width, height, m_Private->m_CarplayBtn);
//    g_Widget->geometryFit(130 - 100 + 270 + 270, (g_Widget->baseWindowHeight() - height) * 0.4 + height, 200, 29, m_Private->m_CarplayBtnText);
   // g_Widget->geometryFit(678, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_Private->m_CarplayTipText);
    QWidget::resizeEvent(event);
}

void LinkWidget::customEvent(QEvent *event) //先不初始化，等到界面OK 了再初始化
{
    qDebug() << "LinkWidget::customEvent";
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->initialize();
        m_Private->connectAllSlots();
        break;
    }
    case CustomEventType::LinkMessageWidgetAddChild: {
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

void LinkWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "LinkWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        }
        break;
    }
    case Widget::T_Link: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_Mirror:
    //case Widget::T_Carplay:
    case Widget::T_Carlife:
    {
        if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    default : {
        setVisible(false);
        break;
    }

    }
}

void LinkWidget::onToolButtonRelease()
{
    qDebug() << "onToolButtonRelease";
    if (sender() == m_Private->m_MirrorBtn) {
        g_Widget->setWidgetType(Widget::T_Mirror, WidgetStatus::RequestShow);
    } /*else if (sender() == m_Private->m_CarplayBtn) {
        g_Widget->setWidgetType(Widget::T_Carplay, WidgetStatus::RequestShow);
    }*/ else if (sender() == m_Private->m_CarlifeBtn) {
        g_Widget->setWidgetType(Widget::T_Carlife, WidgetStatus::RequestShow);
    }

}

LinkWidgetPrivate::LinkWidgetPrivate(LinkWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    m_Titleground = NULL;
    m_TitleText = NULL;
    m_MirrorBtn = NULL;
    m_MirrorBtnText = NULL;
    m_MirrorTipText = NULL;
//    m_CarplayBtn = NULL;
//    m_CarplayBtnText = NULL;
//    m_CarplayTipText = NULL;
    m_CarlifeBtn = NULL;
    m_CarlifeBtnText = NULL;
    m_CarlifeTipText = NULL;
    m_MirrorLinkWidget = NULL;
//    m_CarplayLinkWidget = NULL;
    m_CarlifeLinkWidget = NULL;
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
    Q_UNUSED(g_Link);
}

LinkWidgetPrivate::~LinkWidgetPrivate()
{
}

void LinkWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);
   // m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkWidgetBackground"));

    m_Titleground = new BmpWidget(m_Parent);
    m_Titleground->setVisible(true);
    m_Titleground->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkTip"));
    m_TitleText = new TextWidget(m_Titleground);
    m_TitleText->setFontPointSize(26 * g_Widget->widthScalabilityFactor());
    m_TitleText->setText(SourceString::Select_Connect_Mode);
    m_TitleText->setVisible(true);

    m_MirrorBtn = new BmpButton(m_Parent);
    m_MirrorBtn->setVisible(true);
    m_MirrorBtn->setNormalBmpPath(QString(":/Images/Resources/Images/mirror"));
    m_MirrorBtn->setPressBmpPath(QString(":/Images/Resources/Images/mirror-p"));
    m_MirrorBtnText = new TextWidget(m_MirrorBtn);
    m_MirrorBtnText->setText(SourceString::AndroidMirror);
    m_MirrorBtnText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    m_MirrorBtnText->setVisible(true); 
    m_MirrorLogo = new BmpWidget(m_MirrorBtn);
    m_MirrorLogo->setVisible(true);
    m_MirrorLogo->setBackgroundBmpPath(QString(":/Images/Resources/Images/MirrorLogo"));
    m_MirrorTipText = new TextWidget(m_Parent);
    m_MirrorTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_MirrorTipText->setText(SourceString::AndroidMirrorTip);
    m_MirrorTipText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    m_MirrorTipText->setVisible(true);
//    m_CarplayBtn = new BmpButton(m_Parent);
//    m_CarplayBtn->setVisible(true);
//    m_CarplayBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnNormal"));
//    m_CarplayBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnPress"));
//    m_CarplayBtnText = new TextWidget(m_Parent);
//    m_CarplayBtnText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
//    m_CarplayBtnText->setText(SourceString::AppleCarPlay);
//    m_CarplayBtnText->setVisible(true);
//    m_CarplayTipText = new TextWidget(m_Parent);
//    m_CarplayTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
//    m_CarplayTipText->setText(SourceString::AppleCarPlayTip);
//    m_CarplayTipText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
//    m_CarplayTipText->setVisible(true);

    m_CarlifeBtn = new BmpButton(m_Parent);
    m_CarlifeBtn->setVisible(true);
    m_CarlifeBtn->setNormalBmpPath(QString(":/Images/Resources/Images/life"));
    m_CarlifeBtn->setPressBmpPath(QString(":/Images/Resources/Images/life-p"));
    m_CarlifeBtnText = new TextWidget(m_CarlifeBtn);
    m_CarlifeBtnText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    m_CarlifeBtnText->setText(SourceString::AppleCarLife);
    m_CarlifeBtnText->setVisible(true);
    m_CarlifeLogo = new BmpWidget(m_CarlifeBtn);
    m_CarlifeLogo->setVisible(true);
    m_CarlifeLogo->setBackgroundBmpPath(QString(":/Images/Resources/Images/CarlifeLogo"));
    m_CarlifeTipText = new TextWidget(m_Parent);
    m_CarlifeTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_CarlifeTipText->setText(SourceString::AppleCarPlayTip);
    m_CarlifeTipText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    m_CarlifeTipText->setVisible(true);

    m_MirrorLinkWidget = new MirrorLinkWidget(m_Parent);
//    m_CarplayLinkWidget = new CarplayLinkWidget(m_Parent);
    m_CarlifeLinkWidget = new CarlifeLinkWidget(m_Parent);
}

void LinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void LinkWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_MirrorBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
//    QObject::connect(m_CarplayBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,     SLOT(onToolButtonRelease()),
//                     type);
    QObject::connect(m_CarlifeBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
}
