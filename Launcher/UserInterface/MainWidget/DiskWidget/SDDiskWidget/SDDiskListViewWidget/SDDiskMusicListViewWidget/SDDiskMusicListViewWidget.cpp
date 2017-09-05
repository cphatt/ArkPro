#include "SDDiskMusicListViewWidget.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/MainWidget/DiskWidget/MultimediaListView.h"
#include "UserInterface/Common/ScrollBar.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/BmpButton.h"
#include "AutoConnect.h"
#include "EventEngine.h"
#include <QPainter>
#include <QDebug>
#include <QDomDocument>

namespace SourceString {
static const QString No_Music_Resource = QString(QObject::tr("No Music Resource..."));
}

class SDDiskMusicListViewWidgetPrivate
{
    Q_DISABLE_COPY(SDDiskMusicListViewWidgetPrivate)
public:
    explicit SDDiskMusicListViewWidgetPrivate(SDDiskMusicListViewWidget* parent);
    ~SDDiskMusicListViewWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    MultimediaListView* m_MusicListView;
    MessageBox* m_SDDiskMusicMessageBox;
    BmpButton* m_ListBtn;
    bool m_RequestShow;
    DeviceWatcherStatus USBStatus;
private:
    SDDiskMusicListViewWidget* m_Parent;
};

SDDiskMusicListViewWidget::SDDiskMusicListViewWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Multimedia::Interface()
    , m_Private(new SDDiskMusicListViewWidgetPrivate(this))
{
}

SDDiskMusicListViewWidget::~SDDiskMusicListViewWidget()
{
}

void SDDiskMusicListViewWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SDDiskMusic, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void SDDiskMusicListViewWidget::resizeEvent(QResizeEvent *event)
{

    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 186, g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 176, 315, m_Private->m_SDDiskMusicMessageBox);
    g_Widget->geometryFit(278 - 278, 0, 615, 425 - 110, m_Private->m_MusicListView);
    QWidget::resizeEvent(event);
}

void SDDiskMusicListViewWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::yellow);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void SDDiskMusicListViewWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MusicWidgetAddChild: {
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

void SDDiskMusicListViewWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Back: {
        if (isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        } else if (m_Private->m_ListBtn->isVisible()) {
            if (WidgetStatus::RequestShow == status) {
                g_Widget->setWidgetType(Widget::T_SDDiskMusic, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_SDDiskMusic: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SDDiskMusic, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    case Widget::T_SDDiskImage:
    case Widget::T_SDDiskVideo:
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    default: {
        break;
    }
    }
}

void SDDiskMusicListViewWidget::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "SDDiskMusicListViewWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
        case DWS_Empty: {
            m_Private->m_SDDiskMusicMessageBox->setVisible(false);
            m_Private->m_MusicListView->clearListView();
            m_Private->m_MusicListView->setVisible(false);
            break;
        }
        case DWS_Busy: {
            m_Private->m_SDDiskMusicMessageBox->setVisible(false);
            m_Private->m_MusicListView->setVisible(false);
            break;
        }
        case DWS_Ready: {
            break;
        }
        case DWS_Remove: {
            m_Private->m_SDDiskMusicMessageBox->setVisible(false);
            m_Private->m_MusicListView->clearListView();
            m_Private->m_MusicListView->setVisible(false);
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
    if (DWT_USBDisk == type)
        m_Private->USBStatus = status;
}

void SDDiskMusicListViewWidget::onMusicPlayerFileNames(const DeviceWatcherType type, const QString &xml)
{
    qDebug() << "SDDiskMusicListViewWidget::onMusicPlayerFileNames" << type;
    if (DWT_SDDisk == type) {
        QDomDocument document;
        document.setContent(xml);
        QDomElement root = document.documentElement();
        if ((!root.isNull())
                && (root.isElement())
                && (QString("MusicPlayer") == root.toElement().tagName())
                && (root.hasChildNodes())) {
            QDomNode node = root.firstChild();
            while (!node.isNull()) {
                if (node.isElement()) {
                    QDomElement element = node.toElement();
                    if (!element.isNull()) {
                        if (QString("SDFileNames") == element.tagName()) {
                            QDomNodeList nodeList = element.childNodes();
                            m_Private->m_MusicListView->clearListView();
                            for (int i = 0; i < nodeList.size(); ++i) {
                                QDomNode node = nodeList.at(i);
                                if (node.isElement()) {
                                    if (!node.toElement().isNull()) {
                                        if (node.isElement()) {
                                            m_Private->m_MusicListView->appendListView(node.toElement().text());
                                        }
                                    }
                                }
                            }
                            if (0 == nodeList.length()) {
                                m_Private->m_SDDiskMusicMessageBox->setText(SourceString::No_Music_Resource);
                                m_Private->m_SDDiskMusicMessageBox->setVisible(true);
                                m_Private->m_MusicListView->setVisible(false);
                            } else {
                                m_Private->m_SDDiskMusicMessageBox->setVisible(false);
                                m_Private->m_MusicListView->setVisible(true);

                                if(m_Private->USBStatus != DWS_Ready && m_Private->USBStatus != DWS_Busy)
                                    onMusicListViewItemRelease(0);
                            }
                        }
                    }
                }
                node = node.nextSibling();
            }
        }
    }
}

void SDDiskMusicListViewWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    qDebug() << "SDDiskMusicListViewWidget::onMusicPlayerPlayStatus" << status;
    if (MPPS_Start == status) {
        if (m_Private->m_RequestShow) {
            m_Private->m_RequestShow = false;
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ListBtn));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MusicWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(0, 352, 154, 72, m_Private->m_ListBtn);
            g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::RequestShow);
        }
    }
}

void SDDiskMusicListViewWidget::onMusicListViewItemRelease(const int index)
{
    m_Private->m_RequestShow = true;
    g_Multimedia->musicPlayerPlayListViewIndex(DWT_SDDisk, index);
}

void SDDiskMusicListViewWidget::onToolButtonRelease()
{
    g_Widget->setWidgetType(Widget::T_SDDiskMusic, WidgetStatus::RequestShow);
}

SDDiskMusicListViewWidgetPrivate::SDDiskMusicListViewWidgetPrivate(SDDiskMusicListViewWidget *parent)
    : m_Parent(parent)
{
    m_SDDiskMusicMessageBox = NULL;
    m_MusicListView = NULL;
    m_ListBtn = NULL;
    m_RequestShow = false;
    USBStatus = DWS_Remove;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(true);
}

SDDiskMusicListViewWidgetPrivate::~SDDiskMusicListViewWidgetPrivate()
{
}

void SDDiskMusicListViewWidgetPrivate::initialize()
{
    m_SDDiskMusicMessageBox = new MessageBox(m_Parent);
    m_SDDiskMusicMessageBox->setAutoHide(false);
    m_SDDiskMusicMessageBox->hide();
    m_MusicListView = new MultimediaListView(m_Parent);
    m_MusicListView->hide();
    m_ListBtn = new BmpButton(m_Parent);
    m_ListBtn->hide();
    m_ListBtn->setNormalBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetListNormal"));
    m_ListBtn->setPressBmpPath(QString(":/Images/Resources/Images/MusicToolWidgetListPress"));
}

void SDDiskMusicListViewWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void SDDiskMusicListViewWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_MusicListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onMusicListViewItemRelease(const int)),
                     type);
    QObject::connect(m_MusicListView, SIGNAL(listViewItemRelease(const int)),
                     m_Parent,        SLOT(onMusicListViewItemRelease(const int)),
                     type);
    QObject::connect(m_ListBtn,   SIGNAL(bmpButtonRelease()),
                     m_Parent,    SLOT(onToolButtonRelease()),
                     type);
}
