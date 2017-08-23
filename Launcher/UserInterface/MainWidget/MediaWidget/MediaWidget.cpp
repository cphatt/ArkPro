#include "MediaWidget.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include <QDebug>
#include <QEvent>
#include <QPainter>
namespace SourceString {
static const QString SD = QString(QObject::tr("SD1"));
static const QString USB = QString(QObject::tr("USB1"));
}
class MediaWidgetPrivate
{
    Q_DISABLE_COPY(MediaWidgetPrivate)
public:
    explicit MediaWidgetPrivate(MediaWidget* parent);
    ~MediaWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpWidget* m_Background;
    BmpButton* m_SDDisk;
    TextWidget* m_SDDiskText;
    BmpButton* m_USBDisk;
    TextWidget* m_USBDiskText;
    bool isUSBAlive;
    bool isSDAlive;

private:
    MediaWidget* m_Parent;
};

MediaWidget::MediaWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MediaWidgetPrivate(this))
{

}

MediaWidget::~MediaWidget()
{

}
void MediaWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_Media, WidgetStatus::Show);
    QWidget::showEvent(event);
}
void MediaWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
 //   g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    int width(200);
    int height(50);
    g_Widget->geometryFit(200, 57, width, height, m_Private->m_SDDisk);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_SDDiskText);
    g_Widget->geometryFit(400, 57, width, height, m_Private->m_USBDisk);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_USBDiskText);

    QWidget::resizeEvent(event);
}
void MediaWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void MediaWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "MediaWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
        case Widget::T_Back: {
               if (WidgetStatus::RequestShow == status) {
                   if (isVisible()) {
                       g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
                   }
               }
               break;
           }
        case Widget::T_Media: {
            //接受服务的消息
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Media, WidgetStatus::Show);
            } else if (WidgetStatus::Show == status) {

                setVisible(true);

            }

            break;
        }
        default: {

            if (WidgetStatus::Show == status) {
                setVisible(false);
            }
            break;
        }
    }
}
void MediaWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "MediaWidget::onDeviceWatcherStatus" << type << status;
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
MediaWidgetPrivate::MediaWidgetPrivate(MediaWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    m_SDDisk = NULL;
    m_SDDiskText = NULL;
    m_USBDisk = NULL;
    m_USBDiskText = NULL;
    isUSBAlive = false;
    isSDAlive = false;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(false);
}

MediaWidgetPrivate::~MediaWidgetPrivate()
{
}

void MediaWidgetPrivate::initialize(){
   //  int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    m_Background = new BmpWidget(m_Parent);
    m_Background->show();
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/EffectSoundWidgetBackground"));
    m_SDDisk = new BmpButton(m_Parent);
  //  m_SDDisk->setVisible(true);
    m_SDDisk->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_SDDisk->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_SDDisk->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_SDDiskText = new TextWidget(m_SDDisk);
  //  m_SDDiskText->setVisible(true);
    m_SDDiskText->setText(SourceString::SD);
    m_USBDisk = new BmpButton(m_Parent);
   // m_USBDisk->setVisible(true);
    m_USBDisk->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_USBDisk->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_USBDisk->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_USBDiskText = new TextWidget(m_USBDisk);
   // m_USBDiskText->setVisible(true);
    m_USBDiskText->setText(SourceString::USB);
    m_Parent->setVisible(false);
}

void MediaWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MediaWidgetPrivate::connectAllSlots()
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

void MediaWidget::onBmpButtonRelease()
{
    if (sender() == m_Private->m_SDDisk) {
        g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::RequestShow);
    } else if (sender() == m_Private->m_USBDisk) {
        g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::RequestShow);
    }

}

