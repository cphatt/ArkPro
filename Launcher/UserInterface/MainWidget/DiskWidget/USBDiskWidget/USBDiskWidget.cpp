#include "USBDiskWidget.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "AutoConnect.h"
#include "UserInterface/Common/MessageBox.h"
#include "USBDiskListViewWidget/USBDiskListViewWidget.h"
#include "USBDiskToolWidget/USBDiskToolWidget.h"
#include "UserInterface/Common/BmpWidget.h"
#include "EventEngine.h"
#include <QDebug>
#include <QPainter>
#include <QDomDocument>
#include <QVariant>

namespace SourceString {
static const QString No_USB_Device = QString(QObject::tr("No USB Device..."));
static const QString Scanning_USB_Device = QString(QObject::tr("Scanning USB Device..."));
static const QString Remove_USB_Device = QString(QObject::tr("Remove USB Device..."));
}

class USBDiskWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskWidgetPrivate)
public:
    explicit USBDiskWidgetPrivate(USBDiskWidget* parent);
    ~USBDiskWidgetPrivate();
    void initialize();
    void connectAllSlots();
    USBDiskListViewWidget* m_USBDiskListViewWidget; //文件列表
    USBDiskToolWidget* m_USBDiskToolWidget; //音乐，图片，视频
    MessageBox* m_USBDiskDeviceMessageBox;  //提示框
    BmpWidget* m_USBDiskTip;    //左上角的提示
    bool m_RequestShow;
private:
    USBDiskWidget* m_Parent;
};

USBDiskWidget::USBDiskWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new USBDiskWidgetPrivate(this))
{   
}

USBDiskWidget::~USBDiskWidget()
{
}

void USBDiskWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_USBDiskDeviceMessageBox);
    QWidget::resizeEvent(event);
}

void USBDiskWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void USBDiskWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "USBDiskWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (m_Private->m_USBDiskDeviceMessageBox->isVisible()) {
                if (WidgetStatus::RequestShow == status) {
                    g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
                }
            }
        }
        break;
    }
        //    case Widget::T_SDDisk: {
        //        if (WidgetStatus::Show == status) {
        //            m_Private->m_USBDiskTip->hide();
        //        }
        //        break;
        //    }
    case Widget::T_USBDisk: {
        if (WidgetStatus::RequestShow == status) {
            m_Private->m_RequestShow = true;
            g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::Show);
            //            g_Multimedia->deviceWatcherCheckStatus(DWT_USBDisk);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestShow = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDiskMusic:
    case Widget::T_USBDiskImage:
    case Widget::T_USBDiskVideo: {
        if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_SDDisk:
    case Widget::T_SDDiskMusic:
    case Widget::T_SDDiskImage:
    case Widget::T_SDDiskVideo:
    case Widget::T_Music:
    case Widget::T_Image:
    case Widget::T_ImageFullScreen:
    case Widget::T_Video:
    case Widget::T_VideoFullScreen: {
        if (WidgetStatus::Show == status) {
            m_Private->m_RequestShow = false;
            setVisible(false);
        }
        break;
    }
    case Widget::T_Home: {
        if (WidgetStatus::Show == status) {
            //            if (m_Private->m_USBDiskTip->isHidden()) {
            //                QVariant* variant = new QVariant();
            //                variant->setValue(static_cast<QWidget*>(m_Private->m_USBDiskTip));
            //                EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
            //                g_EventEngine->sendCustomEvent(event);
            //                g_Widget->geometryFit(95, 0, 60, 60, m_Private->m_USBDiskTip);
            //            }
            m_Private->m_RequestShow = false;
            setVisible(false);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void USBDiskWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "USBDiskWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_RequestShow = false;
            m_Private->m_USBDiskDeviceMessageBox->setText(SourceString::No_USB_Device);
            m_Private->m_USBDiskDeviceMessageBox->setAutoHide(false);
            m_Private->m_USBDiskDeviceMessageBox->setVisible(true);
                       g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::Show);
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBDiskDeviceMessageBox->setText(SourceString::Scanning_USB_Device);
            m_Private->m_USBDiskDeviceMessageBox->setAutoHide(false);
            m_Private->m_USBDiskDeviceMessageBox->setVisible(true);
            qDebug() << "m_Private->m_RequestShow" << m_Private->m_RequestShow;
            if (m_Private->m_RequestShow) {
                //                g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::Show);
            }
            m_Private->m_USBDiskTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/USBDiskWidgetTipNormal"));
                m_Private->m_USBDiskTip->setVisible(true);
            break;
        }
        case DWS_Ready: {
            m_Private->m_USBDiskDeviceMessageBox->setVisible(false);
            if (m_Private->m_RequestShow) {
                                g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::Show);
            }
            m_Private->m_USBDiskTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/USBDiskWidgetTipNormal"));
                            m_Private->m_USBDiskTip->setVisible(true);
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBDiskTip->setBackgroundBmpPath(QString(""));
                            m_Private->m_USBDiskTip->setVisible(true);
            m_Private->m_USBDiskDeviceMessageBox->setText(SourceString::Remove_USB_Device);
            m_Private->m_USBDiskDeviceMessageBox->setAutoHide(false);
            m_Private->m_USBDiskDeviceMessageBox->setVisible(true);
            g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::Show);
            break;
        }
        default: {
            break;
        }
        }
    }
}

USBDiskWidgetPrivate::USBDiskWidgetPrivate(USBDiskWidget *parent)
    : m_Parent(parent)
{
    m_RequestShow = false;
    m_USBDiskDeviceMessageBox = NULL;
    m_USBDiskListViewWidget = NULL;
    m_USBDiskToolWidget = NULL;
    m_USBDiskTip = NULL;
    initialize();
    connectAllSlots();
}

USBDiskWidgetPrivate::~USBDiskWidgetPrivate()
{
}

void USBDiskWidgetPrivate::initialize()
{
    m_USBDiskListViewWidget = new USBDiskListViewWidget(m_Parent);
    m_USBDiskToolWidget = new USBDiskToolWidget(m_Parent);
    m_USBDiskDeviceMessageBox = new MessageBox(m_Parent);
    m_USBDiskDeviceMessageBox->setText(SourceString::No_USB_Device);
    m_USBDiskDeviceMessageBox->setAutoHide(false);
    m_USBDiskDeviceMessageBox->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_USBDiskDeviceMessageBox->setVisible(true);
    m_USBDiskTip = new BmpWidget(m_Parent);
    m_USBDiskTip->setVisible(true);
    QVariant* variant = new QVariant();
    variant->setValue(static_cast<QWidget*>(m_USBDiskTip));
    EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
    g_EventEngine->sendCustomEvent(event);
    g_Widget->geometryFit(70, 0, 50, 60, m_USBDiskTip);
    m_Parent->setVisible(false);
}

void USBDiskWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
