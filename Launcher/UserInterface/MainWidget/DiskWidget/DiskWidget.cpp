#include "DiskWidget.h"
#include "USBDiskWidget/USBDiskWidget.h"
#include "SDDiskWidget/SDDiskWidget.h"
#include "AutoConnect.h"
#include "UserInterface/MainWidget/DiskWidget/MusicWidget/MusicWidget.h"
#include "UserInterface/MainWidget/DiskWidget/ImageWidget/ImageWidget.h"
#include "UserInterface/MainWidget/DiskWidget/VideoWidget/VideoWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"

namespace SourceString {
static const QString SD = QString(QObject::tr("SD"));
static const QString USB = QString(QObject::tr("USB"));
}
class DiskWidgetPrivate
{
    Q_DISABLE_COPY(DiskWidgetPrivate)
public:
    explicit DiskWidgetPrivate(DiskWidget* parent);
    ~DiskWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    USBDiskWidget* m_USBDiskWidget;
    SDDiskWidget* m_SDDiskWidget;
    MusicWidget* m_MusicWidget;
    ImageWidget* m_ImageWidget;
    VideoWidget* m_VideoWidget;
    BmpButton* m_SDDisk;
    TextWidget* m_SDDiskText;
    BmpButton* m_USBDisk;
    TextWidget* m_USBDiskText;
    BmpButton* m_USBSD;
    bool isUSBAlive;
    bool isSDAlive;
private:
    DiskWidget* m_Parent;
};

DiskWidget::DiskWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new DiskWidgetPrivate(this))
{
}

DiskWidget::~DiskWidget()
{
}

void DiskWidget::resizeEvent(QResizeEvent *event)  //修改的界面 8.3
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    int width(200);
    int height(50);
    g_Widget->geometryFit(190 - 5, 56, 269, 50, m_Private->m_SDDisk);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_SDDiskText);
    g_Widget->geometryFit(503 - 5, 56, 269, 50, m_Private->m_USBDisk);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_USBDiskText);
    g_Widget->geometryFit(459 - 5, 56, 44, 50, m_Private->m_USBSD);
    QWidget::resizeEvent(event);
}

void DiskWidget::customEvent(QEvent *event)
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

void DiskWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Music:
    case Widget::T_Image:
    case Widget::T_ImageFullScreen:
    case Widget::T_Video:
    case Widget::T_VideoFullScreen:
        if (WidgetStatus::Show == status) {
            setVisible(true);
            m_Private->m_SDDisk->setVisible(false);
            m_Private->m_SDDiskText->setVisible(false);
            m_Private->m_USBDisk->setVisible(false);
            m_Private->m_USBDiskText->setVisible(false);
            m_Private->m_USBSD->setVisible(false);
        }
        break;
    case Widget::T_SDDiskMusic:
    case Widget::T_SDDiskImage:
    case Widget::T_SDDiskVideo:
    case Widget::T_USBDiskMusic:
    case Widget::T_USBDiskImage:
    case Widget::T_USBDiskVideo:
 {
        if (WidgetStatus::Show == status) {
            setVisible(true);
            m_Private->m_SDDisk->setVisible(true);
            m_Private->m_SDDiskText->setVisible(true);
            m_Private->m_USBDisk->setVisible(true);
            m_Private->m_USBDiskText->setVisible(true);
            m_Private->m_USBSD->setVisible(true);
        }

        break;
    }
    case Widget::T_SDDisk:
        if (WidgetStatus::Show == status) {
            m_Private->m_USBDisk->setStatus(BmpButton::B_Normal);
            m_Private->m_SDDisk->setStatus(BmpButton::B_Check);
            //m_Private->m_USBSD->setStatus(BmpButton::B_Normal);
            m_Private->m_USBSD->setNormalBmpPath(QString(":/Images/Resources/Images/SDPress"));
            m_Private->m_USBSD->setPressBmpPath(QString(":/Images/Resources/Images/SDPress"));
            m_Private->m_SDDisk->setPressBmpPath(QString(":/Images/Resources/Images/SD-p"));
            m_Private->m_USBDisk->setPressBmpPath(QString(":/Images/Resources/Images/USB"));


            setVisible(true);
        }
        break;
    case Widget::T_USBDisk:
        if (WidgetStatus::Show == status) {
            m_Private->m_USBDisk->setStatus(BmpButton::B_Check);
            m_Private->m_SDDisk->setStatus(BmpButton::B_Normal);
            //m_Private->m_USBSD->setStatus(BmpButton::B_Check);
            m_Private->m_USBSD->setNormalBmpPath(QString(":/Images/Resources/Images/USBPress"));
            m_Private->m_USBSD->setPressBmpPath(QString(":/Images/Resources/Images/USBPress"));
            m_Private->m_SDDisk->setPressBmpPath(QString(":/Images/Resources/Images/SD"));
            m_Private->m_USBDisk->setPressBmpPath(QString(":/Images/Resources/Images/USB-p"));
            setVisible(true);
        }
        break;
    default: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    }
}
void DiskWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "DiskWidget::onDeviceWatcherStatus" << type << status;
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
DiskWidgetPrivate::DiskWidgetPrivate(DiskWidget *parent)
    : m_Parent(parent)
{
    m_USBDiskWidget = NULL;
    m_SDDiskWidget = NULL;
    m_MusicWidget = NULL;
    m_ImageWidget = NULL;
    m_VideoWidget = NULL;
    m_SDDisk = NULL;
    m_SDDiskText = NULL;
    m_USBDisk = NULL;
    m_USBDiskText = NULL;
    m_USBSD = NULL;
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
    Q_UNUSED(g_Multimedia);
}

DiskWidgetPrivate::~DiskWidgetPrivate()
{
}

void DiskWidgetPrivate::initialize()
{
    m_USBDiskWidget = new USBDiskWidget(m_Parent);
    m_SDDiskWidget = new SDDiskWidget(m_Parent);
    m_ImageWidget = new ImageWidget(m_Parent);
    m_MusicWidget = new MusicWidget(m_Parent);
    m_VideoWidget = new VideoWidget(m_Parent);
    m_SDDisk = new BmpButton(m_Parent);
    m_SDDisk->hide();
    m_SDDisk->setNormalBmpPath(QString(":/Images/Resources/Images/SD"));
    m_SDDisk->setPressBmpPath(QString(":/Images/Resources/Images/SD"));
    m_SDDisk->setCheckBmpPath(QString(":/Images/Resources/Images/SD-p"));
    m_SDDiskText = new TextWidget(m_SDDisk);
    m_SDDiskText->show();
    //m_SDDiskText->setText(SourceString::SD);
    m_USBDisk = new BmpButton(m_Parent);
    m_USBDisk->show();
    m_USBDisk->setNormalBmpPath(QString(":/Images/Resources/Images/USB"));
    m_USBDisk->setPressBmpPath(QString(":/Images/Resources/Images/USB"));
    m_USBDisk->setCheckBmpPath(QString(":/Images/Resources/Images/USB-p"));
    m_USBDiskText = new TextWidget(m_USBDisk);
    m_USBDiskText->show();
   // m_USBDiskText->setText(SourceString::USB);
    m_USBSD = new BmpButton(m_Parent);
    m_USBSD->show();

//    m_USBSD->setNormalBmpPath(QString(":/Images/Resources/Images/SDPress"));
//    m_USBSD->setPressBmpPath(QString(":/Images/Resources/Images/SDPress"));
//    m_USBSD->setCheckBmpPath(QString(":/Images/Resources/Images/USBPress"));

}

void DiskWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void DiskWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_SDDisk, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onBmpButtonRelease()),
                     type);
    QObject::connect(m_USBDisk, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onBmpButtonRelease()),
                     type);
}
void DiskWidget::onBmpButtonRelease()
{
    if (sender() == m_Private->m_SDDisk && m_Private->isSDAlive) {
        g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_USBDisk && m_Private->isUSBAlive) {
        g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::RequestShow);
    }

}
