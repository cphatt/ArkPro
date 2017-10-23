#include "CarPlayWidget.h"

#include "CarplayLinkWidget/CarplayLinkWidget.h"
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
class CarPlayWidgetPrivate
{
    Q_DISABLE_COPY(CarPlayWidgetPrivate)
public:
    explicit CarPlayWidgetPrivate(CarPlayWidget *parent);
    ~CarPlayWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpWidget* m_Background;
    BmpWidget* m_Titleground;
    TextWidget* m_TitleText;


    BmpButton* m_CarplayBtn;
    TextWidget* m_CarplayBtnText;
    TextWidget* m_CarplayTipText;


    CarplayLinkWidget* m_CarplayLinkWidget;

private:
    CarPlayWidget* m_Parent;
};

CarPlayWidget::CarPlayWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new CarPlayWidgetPrivate(this))
{
}

CarPlayWidget::~CarPlayWidget()
{
}

void CarPlayWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    g_Widget->geometryFit(0, 62, 800, 46, m_Private->m_Titleground);
    g_Widget->geometryFit(0, 0, 800, 46, m_Private->m_TitleText);
    int width(260);
    int height(300);

    g_Widget->geometryFit(540, 117, width, height, m_Private->m_CarplayBtn);
    g_Widget->geometryFit(130 - 100 + 270 + 270, (g_Widget->baseWindowHeight() - height) * 0.4 + height, 200, 29, m_Private->m_CarplayBtnText);
   // g_Widget->geometryFit(678, (g_Widget->baseWindowHeight() - height) * 0.5 + height, 572, 120, m_Private->m_CarplayTipText);
    QWidget::resizeEvent(event);
}

void CarPlayWidget::customEvent(QEvent *event) //先不初始化，等到界面OK 了再初始化
{
    qDebug() << "CarPlayWidget::customEvent";
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->initialize();
        m_Private->connectAllSlots();
        break;
    }
    case CustomEventType::CarPlayLinkMessageWidgetAddChild: {
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

void CarPlayWidget::mousePressEvent(QMouseEvent *event)
{
    g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
    QWidget::mousePressEvent(event);
}

void CarPlayWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "CarPlayWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        }
        break;
    }
    case Widget::T_CarplayWidget: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_CarplayWidget, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
            m_Private->m_CarplayBtn->setVisible(false);
            m_Private->m_CarplayBtnText->setVisible(false) ;
            m_Private->m_CarplayTipText->setVisible(false) ;
            m_Private->m_TitleText->setVisible(false) ;
            m_Private->m_Titleground->setVisible(false) ;
            m_Private->m_Background->setVisible(false);


        }
        break;
    }
    case Widget::T_Mirror:
    case Widget::T_Carplay:
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

void CarPlayWidget::onToolButtonRelease()
{
    qDebug() << "onToolButtonRelease";
    if (sender() == m_Private->m_CarplayBtn) {
        g_Widget->setWidgetType(Widget::T_Carplay, WidgetStatus::RequestShow);
    }
}

CarPlayWidgetPrivate::CarPlayWidgetPrivate(CarPlayWidget *parent)
    : m_Parent(parent)
{
    qDebug() << "asda";
    m_Background = NULL;
    m_Titleground = NULL;
    m_TitleText = NULL;

    m_CarplayBtn = NULL;
    m_CarplayBtnText = NULL;
    m_CarplayTipText = NULL;

    m_CarplayLinkWidget = NULL;
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
    Q_UNUSED(g_Link);
}

CarPlayWidgetPrivate::~CarPlayWidgetPrivate()
{
}

void CarPlayWidgetPrivate::initialize()
{
        qDebug() << "-----------addasd";
    m_Background = new BmpWidget(m_Parent);
    m_Background->setVisible(true);

    m_Titleground = new BmpWidget(m_Parent);
    m_Titleground->setVisible(true);
    m_Titleground->setBackgroundBmpPath(QString(":/Images/Resources/Images/LinkTip"));
    m_TitleText = new TextWidget(m_Titleground);
    m_TitleText->setFontPointSize(26 * g_Widget->widthScalabilityFactor());
    m_TitleText->setText(SourceString::Select_Connect_Mode);
    m_TitleText->setVisible(true);


    m_CarplayBtn = new BmpButton(m_Parent);
    m_CarplayBtn->setVisible(true);
    m_CarplayBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnNormal"));
    m_CarplayBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetCarplayBtnPress"));
    m_CarplayBtnText = new TextWidget(m_Parent);
    m_CarplayBtnText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    m_CarplayBtnText->setText(SourceString::AppleCarPlay);
    m_CarplayBtnText->setVisible(true);
    m_CarplayTipText = new TextWidget(m_Parent);
    m_CarplayTipText->setAlignmentFlag(Qt::AlignLeft | Qt::AlignVCenter);
    m_CarplayTipText->setText(SourceString::AppleCarPlayTip);
    m_CarplayTipText->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
    m_CarplayTipText->setVisible(true);



    m_CarplayLinkWidget = new CarplayLinkWidget(m_Parent);

}

void CarPlayWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void CarPlayWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);

    QObject::connect(m_CarplayBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
}
