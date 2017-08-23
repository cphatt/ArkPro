#include "USBDiskImageListViewWidget.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/ScrollBar.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include <QPainter>
#include <QDomDocument>
#include <QDebug>

namespace SourceString {
static const QString No_Image_Resource = QString(QObject::tr("No Image Resource..."));
}

class USBDiskImageListViewWidgetPrivate
{
    Q_DISABLE_COPY(USBDiskImageListViewWidgetPrivate)
public:
    explicit USBDiskImageListViewWidgetPrivate(USBDiskImageListViewWidget* parent);
    ~USBDiskImageListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_ImageListView;
    MessageBox* m_USBDiskImageMessageBox;
    BmpButton* m_ListBtn;
    bool m_RequestShow;
private:
    USBDiskImageListViewWidget* m_Parent;
};

USBDiskImageListViewWidget::USBDiskImageListViewWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new USBDiskImageListViewWidgetPrivate(this))
{
}

USBDiskImageListViewWidget::~USBDiskImageListViewWidget()
{
}

void USBDiskImageListViewWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void USBDiskImageListViewWidget::resizeEvent(QResizeEvent *event)
{

    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 186, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 176, 315, m_Private->m_USBDiskImageMessageBox);
    g_Widget->geometryFit(278 - 278, 0, 615, 425 - 110, m_Private->m_ImageListView);
    QWidget::resizeEvent(event);
}

void USBDiskImageListViewWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void USBDiskImageListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::ImageStatusWidgetAddChild: {
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

void USBDiskImageListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "USBDiskImageListViewWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_USBDiskImage: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_USBDiskMusic:
    case Widget::T_USBDiskVideo:
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    default: {
        break;
    }
    }
}

void USBDiskImageListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "USBDiskImageListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_USBDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_USBDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->clearListView();
            m_Private->m_ImageListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_USBDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_USBDiskImageMessageBox->setVisible(false);
            m_Private->m_ImageListView->clearListView();
            m_Private->m_ImageListView->setVisible(false);
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

void USBDiskImageListViewWidget::onImagePlayerFileNames(const DeviceWatcherType type, const QString &xml)
{
    if (DWT_USBDisk == type) {
        QDomDocument document;
        document.setContent(xml);
        QDomElement root = document.documentElement();
        if ((!root.isNull())
                && (root.isElement())
                && (QString("ImagePlayer") == root.toElement().tagName())
                && (root.hasChildNodes())) {
            QDomNode node = root.firstChild();
            while (!node.isNull()) {
                if (node.isElement()) {
                    QDomElement element = node.toElement();
                    if (!element.isNull()) {
                        if (QString("USBFileNames") == element.tagName()) {
                            QDomNodeList nodeList = element.childNodes();
                            m_Private->m_ImageListView->clearListView();
                            for (int i = 0; i < nodeList.size(); ++i) {
                                QDomNode node = nodeList.at(i);
                                if (node.isElement()) {
                                    if (!node.toElement().isNull()) {
                                        if (node.isElement()) {
                                            m_Private->m_ImageListView->appendListView(node.toElement().text());
                                        }
                                    }
                                }
                            }
                            if (0 == nodeList.length()) {
                                m_Private->m_USBDiskImageMessageBox->setText(SourceString::No_Image_Resource);
                                m_Private->m_USBDiskImageMessageBox->setVisible(true);
                                m_Private->m_ImageListView->setVisible(false);
                            } else {
                                m_Private->m_USBDiskImageMessageBox->setVisible(false);
                                m_Private->m_ImageListView->setVisible(true);
                            }
                        }
                    }
                }
                node = node.nextSibling();
            }
        }
    }
}

void USBDiskImageListViewWidget::onImagePlayerPlayStatus(const ImagePlayerPlayStatus status)
{
    if (IPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::ImageStatusWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(713, 0, 58, 58, m_Private->m_ListBtn);
            g_Widget->setWidgetType(Widget::T_Image, WidgetStatus::RequestShow);
        }
    }
}

void USBDiskImageListViewWidget::onImageListViewItemRelease(const int index)
{
    m_Private->m_RequestShow = true;
    g_Multimedia->imagePlayerPlayListViewIndex(DWT_USBDisk, index);
}

void USBDiskImageListViewWidget::onListBtnRelease()
{
    g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::RequestShow);
}

USBDiskImageListViewWidgetPrivate::USBDiskImageListViewWidgetPrivate(USBDiskImageListViewWidget *parent)
    : m_Parent(parent)
{
    m_RequestShow = false;
    m_USBDiskImageMessageBox = NULL;
    m_ImageListView = NULL;
    m_ListBtn = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
}

USBDiskImageListViewWidgetPrivate::~USBDiskImageListViewWidgetPrivate()
{
}

void USBDiskImageListViewWidgetPrivate::initialize()
{
    m_USBDiskImageMessageBox = new MessageBox(m_Parent);
    m_USBDiskImageMessageBox->setAutoHide(false);
    m_USBDiskImageMessageBox->hide();
    m_ImageListView = new MultimediaListView(m_Parent);
    m_ImageListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/ImageStatusWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/ImageStatusWidgetListPress"));
    m_ListBtn->hide();
    m_Parent->setVisible(false);
}

void USBDiskImageListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void USBDiskImageListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_ImageListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onImageListViewItemRelease(const int)),
                     type);
    QObject::connect(m_ListBtn,  SIGNAL(bmpButtonRelease()),
                     m_Parent,   SLOT(onListBtnRelease()),
                     type);
}
