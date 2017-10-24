#include "USBDiskVideoListViewWidget.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterface/Common/ScrollBar.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/BmpButton.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include <QPainter>
#include <QDomDocument>
#include <QDebug>

namespace SourceString {
static const QString No_Video_Resource = QString(QObject::tr("No Video Resource..."));
}

class USBDiskVideoListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskVideoListViewWidgetPrivate)
public:
    explicit USBDiskVideoListViewWidgetPrivate(USBDiskVideoListViewWidget* parent);
    ~USBDiskVideoListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_VideoListView;
    MessageBox* m_USBDiskVideoMessageBox;
    BmpButton* m_ListBtn;
    bool m_RequestShow;
    int m_LastIndex = -1;
private:
    USBDiskVideoListViewWidget* m_Parent;
};

USBDiskVideoListViewWidget::USBDiskVideoListViewWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new USBDiskVideoListViewWidgetPrivate(this))
{
}

USBDiskVideoListViewWidget::~USBDiskVideoListViewWidget()
{
}

void USBDiskVideoListViewWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void USBDiskVideoListViewWidget::resizeEvent(QResizeEvent *event)
{


    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 186, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 176, 315, m_Private->m_USBDiskVideoMessageBox);
    g_Widget->geometryFit(278 - 278, 0, 615, 425 - 110, m_Private->m_VideoListView);
    QWidget::resizeEvent(event);
}

void USBDiskVideoListViewWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void USBDiskVideoListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::VideoToolBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            if (m_Private->m_ListBtn != ptr->m_Data->value<QWidget*>()) {
                m_Private->m_ListBtn->setVisible(false);
            }
        }
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void USBDiskVideoListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_USBDiskVideo: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDiskImage:
    case Widget::T_USBDiskMusic:
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    default: {
        break;
    }
    }
}

void USBDiskVideoListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "USBDiskVideoListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            if (m_Private->m_ListBtn->isVisible()) {
                g_Widget->setWidgetType(Widget::T_USBDisk, WidgetStatus::Show);
            }
            break;
        }
        default: {
            break;
        }
        }
    }
}

void USBDiskVideoListViewWidget::onVideoPlayerFileNames(const int type, const QString& xml)
{
    if (DWT_USBDisk == type) {
        QDomDocument document;
        document.setContent(xml);
        QDomElement root = document.documentElement();
        if ((!root.isNull())
                && (root.isElement())
                && (QString("VideoPlayer") == root.toElement().tagName())
                && (root.hasChildNodes())) {
            QDomNode node = root.firstChild();
            while (!node.isNull()) {
                if (node.isElement()) {
                    QDomElement element = node.toElement();
                    if (!element.isNull()) {
                        if (QString("USBFileNames") == element.tagName()) {
                            QDomNodeList nodeList = element.childNodes();
                            m_Private->m_VideoListView->clearListView();
                            for (int i = 0; i < nodeList.size(); ++i) {
                                QDomNode node = nodeList.at(i);
                                if (node.isElement()) {
                                    if (!node.toElement().isNull()) {
                                        if (node.isElement()) {
                                            m_Private->m_VideoListView->appendListView(node.toElement().text());
                                        }
                                    }
                                }
                            }
                            if (0 == nodeList.length()) {
                                m_Private->m_USBDiskVideoMessageBox->setText(SourceString::No_Video_Resource);
                                m_Private->m_USBDiskVideoMessageBox->setVisible(true);
                                m_Private->m_VideoListView->setVisible(false);
                            } else {
                                m_Private->m_USBDiskVideoMessageBox->setVisible(false);
                                m_Private->m_VideoListView->setVisible(true);
                            }
                        }
                    }
                }
                node = node.nextSibling();
            }
        }
    }
}

void USBDiskVideoListViewWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    switch (status) {
    case VPPS_Start: {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::VideoToolBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(713, 0 , 58, 58, m_Private->m_ListBtn);
            g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::RequestShow);
        }
    }
    default: {
        break;
    }
    }
}
void USBDiskVideoListViewWidget::onVideoPlayerInformation(const DeviceWatcherType type, const int index, const QString &fileName, const int endTime)
{
    qDebug() << "USBDiskVideoListViewWidget::onVideoPlayerInformation" << index;
    if (DWT_USBDisk == type) {
        m_Private->m_LastIndex = index;
        m_Private->m_VideoListView->setCurrentIndex(m_Private->m_VideoListView->model()->index(index, 0, QModelIndex()));
    }
}
void USBDiskVideoListViewWidget::onVideoListViewItemRelease(const int index)
{
    m_Private->m_RequestShow = true;
    g_Multimedia->videoPlayerPlayListViewIndex(DWT_USBDisk, index, 0, 0, g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor());
}

void USBDiskVideoListViewWidget::onToolButtonRelease()
{
    g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::RequestShow);
}

USBDiskVideoListViewWidgetPrivate::USBDiskVideoListViewWidgetPrivate(USBDiskVideoListViewWidget *parent)
    : m_Parent(parent)
{
    m_RequestShow = false;
    m_USBDiskVideoMessageBox = NULL;
    m_VideoListView = NULL;
    m_ListBtn = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

USBDiskVideoListViewWidgetPrivate::~USBDiskVideoListViewWidgetPrivate()
{
}

void USBDiskVideoListViewWidgetPrivate::initialize()
{
    m_USBDiskVideoMessageBox = new MessageBox(m_Parent);
    m_USBDiskVideoMessageBox->setAutoHide(false);
    m_USBDiskVideoMessageBox->hide();
    m_VideoListView = new MultimediaListView(m_Parent);
    m_VideoListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->hide();
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
    m_Parent->setVisible(false);
}

void USBDiskVideoListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void USBDiskVideoListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_VideoListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onVideoListViewItemRelease(const int)),
                     type);
    QObject::connect(m_ListBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(onToolButtonRelease()),
                     type);
}
