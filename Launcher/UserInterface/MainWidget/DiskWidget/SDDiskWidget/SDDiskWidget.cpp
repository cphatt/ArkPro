#include "SDDiskWidget.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "AutoConnect.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/MainWidget/DiskWidget/MusicWidget/MusicWidget.h"
#include "UserInterface/MainWidget/DiskWidget/ImageWidget/ImageWidget.h"
#include "UserInterface/MainWidget/DiskWidget/VideoWidget/VideoWidget.h"
#include "SDDiskListViewWidget/SDDiskListViewWidget.h"
#include "SDDiskToolWidget/SDDiskToolWidget.h"
#include "UserInterface/Common/BmpWidget.h"
#include "EventEngine.h"
#include <QDebug>
#include <QPainter>
#include <QDomDocument>
#include <QVariant>

namespace SourceString {
static const QString No_SD_Device = QString(QObject::tr("No SD Device..."));
static const QString Scanning_SD_Device = QString(QObject::tr("Scanning SD Device..."));
static const QString Remove_SD_Device = QString(QObject::tr("Remove SD Device..."));
}

class SDDiskWidgetPrivate
{
    Q_DISABLE_COPY(SDDiskWidgetPrivate)
public:
    explicit SDDiskWidgetPrivate(SDDiskWidget* parent);
    ~SDDiskWidgetPrivate();
    void initialize();
    void connectAllSlots();
    SDDiskListViewWidget* m_SDDiskListViewWidget;
    SDDiskToolWidget* m_SDDiskToolWidget;
    MessageBox* m_SDDiskDeviceMessageBox;
    BmpWidget* m_SDDiskTip;
    bool m_RequestShow;
private:
    SDDiskWidget* m_Parent;
};

SDDiskWidget::SDDiskWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new SDDiskWidgetPrivate(this))
{
}

SDDiskWidget::~SDDiskWidget()
{
}

void SDDiskWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_SDDiskDeviceMessageBox);
    QWidget::resizeEvent(event);
}

void SDDiskWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void SDDiskWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "SDDiskWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (m_Private->m_SDDiskDeviceMessageBox->isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_SDDisk: {
        if (WidgetStatus::RequestShow == status) {
            m_Private->m_RequestShow = true;
            g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::Show);
            //            g_Multimedia->deviceWatcherCheckStatus(DWT_SDDisk);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_RequestShow = false;
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDisk:
    case Widget::T_USBDiskMusic:
    case Widget::T_USBDiskImage:
    case Widget::T_USBDiskVideo:
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
    case Widget::T_SDDiskMusic:
    case Widget::T_SDDiskImage:
    case Widget::T_SDDiskVideo: {
        if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_Home: {
        if (WidgetStatus::Show == status) {
//            if (m_Private->m_SDDiskTip->isHidden()) {
//                QVariant* variant = new QVariant();
//                variant->setValue(static_cast<QWidget*>(m_Private->m_SDDiskTip));
//                EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
//                g_EventEngine->sendCustomEvent(event);
//                g_Widget->geometryFit(15, 0, 60, 60, m_Private->m_SDDiskTip);
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

void SDDiskWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "SDDiskWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_RequestShow = false;
            m_Private->m_SDDiskDeviceMessageBox->setText(SourceString::No_SD_Device);
            m_Private->m_SDDiskDeviceMessageBox->setAutoHide(false);
            m_Private->m_SDDiskDeviceMessageBox->setVisible(true);
            //g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::Show);
            break;
        }
        case DWS_Busy: {
            m_Private->m_SDDiskDeviceMessageBox->setText(SourceString::Scanning_SD_Device);
            m_Private->m_SDDiskDeviceMessageBox->setAutoHide(false);
            m_Private->m_SDDiskDeviceMessageBox->setVisible(true);
            if (m_Private->m_RequestShow) {
                g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::Show);
            }
            m_Private->m_SDDiskTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/SDDiskWidgetTipNormal"));
            m_Private->m_SDDiskTip->setVisible(true);
            break;
        }
        case DWS_Ready: {
            m_Private->m_SDDiskDeviceMessageBox->setVisible(false);
            if (m_Private->m_RequestShow) {
                g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::Show);
            }
            m_Private->m_SDDiskTip->setBackgroundBmpPath(QString(":/Images/Resources/Images/SDDiskWidgetTipNormal"));
            m_Private->m_SDDiskTip->setVisible(true);
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDDiskTip->setBackgroundBmpPath(QString(""));
            m_Private->m_SDDiskTip->setVisible(true);
            m_Private->m_SDDiskDeviceMessageBox->setText(SourceString::Remove_SD_Device);
            m_Private->m_SDDiskDeviceMessageBox->setAutoHide(false);
            m_Private->m_SDDiskDeviceMessageBox->setVisible(true);
            break;
        }
        default: {
            break;
        }
        }
    }
}

SDDiskWidgetPrivate::SDDiskWidgetPrivate(SDDiskWidget *parent)
    : m_Parent(parent)
{
    m_RequestShow = false;
    m_SDDiskDeviceMessageBox = NULL;
    m_SDDiskListViewWidget = NULL;
    m_SDDiskToolWidget = NULL;
    m_SDDiskTip = NULL;
    initialize();
    connectAllSlots();
}

SDDiskWidgetPrivate::~SDDiskWidgetPrivate()
{
}

void SDDiskWidgetPrivate::initialize()
{
    m_SDDiskListViewWidget = new SDDiskListViewWidget(m_Parent);
    m_SDDiskToolWidget = new SDDiskToolWidget(m_Parent);
    m_SDDiskDeviceMessageBox = new MessageBox(m_Parent);
    m_SDDiskDeviceMessageBox->setText(SourceString::No_SD_Device);
    m_SDDiskDeviceMessageBox->setAutoHide(false);
    m_SDDiskDeviceMessageBox->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
    m_SDDiskDeviceMessageBox->setVisible(true);
    m_SDDiskTip = new BmpWidget(m_Parent);
    m_SDDiskTip->setVisible(true);
    QVariant* variant = new QVariant();
    variant->setValue(static_cast<QWidget*>(m_SDDiskTip));
    EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::StatusBarWidgetAddChild), variant);
    g_EventEngine->sendCustomEvent(event);
    g_Widget->geometryFit(10, 0, 50, 60, m_SDDiskTip);
    m_Parent->setVisible(false);
}

void SDDiskWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
