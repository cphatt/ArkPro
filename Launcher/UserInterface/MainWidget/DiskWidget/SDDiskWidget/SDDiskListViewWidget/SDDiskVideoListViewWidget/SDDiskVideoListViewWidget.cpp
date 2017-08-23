#include "SDDiskVideoListViewWidget.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterface/Common/ScrollBar.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/BmpButton.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include <QVariant>
#include <QPainter>
#include <QDomDocument>
#include <QDebug>

namespace SourceString {
static const QString No_Video_Resource = QString(QObject::tr("No Video Resource..."));
}

class SDDiskVideoListViewWidgetPrivate
{
    Q_DISABLE_COPY(SDDiskVideoListViewWidgetPrivate)
public:
    explicit SDDiskVideoListViewWidgetPrivate(SDDiskVideoListViewWidget* parent);
    ~SDDiskVideoListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_VideoListView;
    MessageBox* m_SDDiskVideoMessageBox;
    BmpButton* m_ListBtn;
    bool m_RequestShow;
private:
    SDDiskVideoListViewWidget* m_Parent;
};

SDDiskVideoListViewWidget::SDDiskVideoListViewWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new SDDiskVideoListViewWidgetPrivate(this))
{
}

SDDiskVideoListViewWidget::~SDDiskVideoListViewWidget()
{
}

void SDDiskVideoListViewWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void SDDiskVideoListViewWidget::resizeEvent(QResizeEvent *event)
{

    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 186, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 176, 315, m_Private->m_SDDiskVideoMessageBox);
    g_Widget->geometryFit(278 - 278, 0, 615, 425 - 110, m_Private->m_VideoListView);
    QWidget::resizeEvent(event);
}

void SDDiskVideoListViewWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void SDDiskVideoListViewWidget::customEvent(QEvent *event)
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

void SDDiskVideoListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "SDDiskVideoListViewWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_SDDiskVideo: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_SDDiskImage:
    case Widget::T_SDDiskMusic:
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    default: {
        break;
    }
    }
}

void SDDiskVideoListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "SDDiskVideoListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_SDDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_SDDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDDiskVideoMessageBox->setVisible(false);
            m_Private->m_VideoListView->clearListView();
            m_Private->m_VideoListView->setVisible(false);
            if (m_Private->m_ListBtn->isVisible()) {
                g_Widget->setWidgetType(Widget::T_SDDisk, WidgetStatus::Show);
            }
            break;
        }
        default: {
            break;
        }
        }
    }
}

void SDDiskVideoListViewWidget::onVideoPlayerFileNames(const int type, const QString& xml)
{
    qDebug() << "SDDiskVideoListViewWidget::onVideoPlayerFileNames" << type << xml;
    if (DWT_SDDisk == type) {
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
                        if (QString("SDFileNames") == element.tagName()) {
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
                            qDebug() << __FUNCTION__ << "nodeList.length()" << nodeList.length();
                            if (0 == nodeList.length()) {
                                m_Private->m_SDDiskVideoMessageBox->setText(SourceString::No_Video_Resource);
                                m_Private->m_SDDiskVideoMessageBox->setVisible(true);
                                m_Private->m_VideoListView->setVisible(false);
                            } else {
                                m_Private->m_SDDiskVideoMessageBox->setVisible(false);
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

void SDDiskVideoListViewWidget::onVideoPlayerPlayStatus(const VideoPlayerPlayStatus status)
{
    qDebug() << "SDDiskVideoListViewWidget::onVideoPlayerPlayStatus" << status;
    if (VPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::VideoToolBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->setWidgetType(Widget::T_Video, WidgetStatus::RequestShow);
            g_Widget->geometryFit(713, 0 , 58, 58, m_Private->m_ListBtn);
        }
    }
}

void SDDiskVideoListViewWidget::onVideoListViewItemRelease(const int index)
{
    m_Private->m_RequestShow = true;
    g_Multimedia->videoPlayerPlayListViewIndex(DWT_SDDisk, index, 0, 0, g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor());
}

void SDDiskVideoListViewWidget::onToolButtonRelease()
{
    g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::RequestShow);
}

SDDiskVideoListViewWidgetPrivate::SDDiskVideoListViewWidgetPrivate(SDDiskVideoListViewWidget *parent)
    : m_Parent(parent)
{
    m_RequestShow = false;
    m_SDDiskVideoMessageBox = NULL;
    m_VideoListView = NULL;
    m_ListBtn = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

SDDiskVideoListViewWidgetPrivate::~SDDiskVideoListViewWidgetPrivate()
{
}

void SDDiskVideoListViewWidgetPrivate::initialize()
{
    m_SDDiskVideoMessageBox = new MessageBox(m_Parent);
    m_SDDiskVideoMessageBox->setAutoHide(false);
    m_SDDiskVideoMessageBox->hide();
    m_VideoListView = new MultimediaListView(m_Parent);
    m_VideoListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->hide();
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/VideoToolBarWidgetListNormal"));
    m_Parent->setVisible(false);
}

void SDDiskVideoListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void SDDiskVideoListViewWidgetPrivate::connectAllSlots()
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
