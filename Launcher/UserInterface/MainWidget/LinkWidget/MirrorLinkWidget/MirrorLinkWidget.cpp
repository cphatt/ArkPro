#include "MirrorLinkWidget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "UserInterface/Common/BmpButton.h"
#include "MirrorShortCutWidget/MirrorShortCutWidget.h"
#include "MirrorToolWidget/MirrorToolWidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <QTouchEvent>
#include <QDomElement>

namespace SourceString {
static const QString No_Mirror_Device = QString(QObject::tr("No Mirror Device..."));
static const QString Conneting_Mirror_Device = QString(QObject::tr("Conneting Mirror Device..."));
static const QString Remove_Mirror_Device = QString(QObject::tr("Remove Mirror Device..."));
}

class MirrorLinkWidgetPrivate
{
    Q_DISABLE_COPY(MirrorLinkWidgetPrivate)
public:
    explicit MirrorLinkWidgetPrivate(MirrorLinkWidget* parent);
    ~MirrorLinkWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    void touchBeginEventHandler(QEvent* event);
    void touchUpdateEventHandler(QEvent* event);
    void touchEndEventHandler(QEvent* event);
    void onMirrorLinkStatus(const Link_STATUS status);
    QString translateTouchEvent(const QList<TouchEvent> &list);
    MirrorShortCutWidget* m_MirrorShortCutWidget;
    MessageBox* m_DeviceMessageBox;
    MirrorToolWidget* m_MirrorToolWidget;
    BmpButton* m_PopBtn;
    QPoint m_Src;
    QPoint m_Dest;
    bool m_Filter;
    QTimer* m_Timer;
private:
    MirrorLinkWidget* m_Parent;
};

MirrorLinkWidget::MirrorLinkWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Link::Interface()
    , m_Private(new MirrorLinkWidgetPrivate(this))
{
}

MirrorLinkWidget::~MirrorLinkWidget()
{
}

bool MirrorLinkWidget::event(QEvent *event)
{
    bool ret(true);
    switch (event->type()) {
    case QEvent::TouchBegin:
        m_Private->touchBeginEventHandler(event);
        ret = true;
        break;
    case QEvent::TouchUpdate: {
        m_Private->touchUpdateEventHandler(event);
        return true;
        break;
    }
    case QEvent::TouchEnd: {
        m_Private->touchEndEventHandler(event);
        ret = true;
        break;
    }
    default : {
        ret = QWidget::event(event);
        break;
    }
    }
    return ret;
}

void MirrorLinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, g_Widget->baseWindowHeight() - 40, 40, 40, m_Private->m_PopBtn);
    QWidget::resizeEvent(event);
}

void MirrorLinkWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
    QWidget::paintEvent(event);
}

void MirrorLinkWidget::mousePressEvent(QMouseEvent *event)
{
    qWarning() << __FUNCTION__ << event->pos() << QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty();
    if (QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointPressed;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
    }
}

void MirrorLinkWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointReleased;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
    }
}

void MirrorLinkWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointMoved;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
    }
}

void MirrorLinkWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::LinkMessageWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            if (m_Private->m_DeviceMessageBox != ptr->m_Data->value<QWidget*>()) {
                m_Private->m_DeviceMessageBox->setVisible(false);
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

void MirrorLinkWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Mirror: {
        if (WidgetStatus::RequestShow == status) {
            g_Link->requestLinkStatus(ANDROID_MIRROR, LINK_STARTING);
        } else if (WidgetStatus::Show == status) {
            if (!QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
                setAttribute(Qt::WA_AcceptTouchEvents, true);
            }
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

void MirrorLinkWidget::onMessageWidgetChange(const MessageBox::Type type)
{
    if (MessageBox::T_Hide == type) {
        m_Private->m_DeviceMessageBox->setVisible(false);
    }
}

void MirrorLinkWidget::onPopBtnRelease()
{
    if (m_Private->m_MirrorToolWidget->isVisible()) {
        m_Private->m_Timer->stop();
        m_Private->m_MirrorToolWidget->setVisible(false);
    } else {
        m_Private->m_Timer->start();
        m_Private->m_MirrorToolWidget->setVisible(true);
    }
}

void MirrorLinkWidget::onToolBtnRelease(const int type)
{
    qDebug() << "MirrorLinkWidget::onToolBtnRelease" << type;
    switch(type) {
    case MirrorToolWidget::T_Car: {
        m_Private->m_Timer->stop();
        m_Private->m_MirrorToolWidget->setVisible(false);
        g_Link->requestLinkStatus(ANDROID_MIRROR, LINK_EXITING);
        break;
    }
    case MirrorToolWidget::T_Back: {
        m_Private->m_Timer->start();
        break;
    }
    case MirrorToolWidget::T_Home: {
        m_Private->m_Timer->start();
        break;;
    }
    case MirrorToolWidget::T_Menu: {
        m_Private->m_Timer->start();
        break;
    }
    default: {
        break;
    }
    }
}

void MirrorLinkWidget::onTimeout()
{
    m_Private->m_MirrorToolWidget->setVisible(false);
}

void MirrorLinkWidget::onLinkStatusChange(const Link_Type type, const Link_STATUS status)
{
    qDebug() << "MirrorLinkWidget::onLinkStatusChange" << type << status;
    switch (type) {
    case ANDROID_MIRROR: {
        m_Private->onMirrorLinkStatus(status);
        break;
    }
    default: {
        break;
    }
    }
}

MirrorLinkWidgetPrivate::MirrorLinkWidgetPrivate(MirrorLinkWidget* parent)
    : m_Parent(parent)
{
    m_Timer = NULL;
    m_Src = QPoint(0, 0);
    m_Dest = QPoint(0, 0);
    m_MirrorShortCutWidget = NULL;
    m_DeviceMessageBox = NULL;
    m_PopBtn = NULL;
    m_MirrorToolWidget = NULL;
    m_Filter = false;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(false);
}

MirrorLinkWidgetPrivate::~MirrorLinkWidgetPrivate()
{
}

void MirrorLinkWidgetPrivate::initialize()
{
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(5000);
    m_MirrorToolWidget = new MirrorToolWidget(m_Parent);
    m_MirrorToolWidget->setVisible(false);
    m_MirrorShortCutWidget = new MirrorShortCutWidget(m_Parent);
    m_PopBtn = new BmpButton(m_Parent);
    m_PopBtn->setNormalBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorPotBtnNormal"));
    m_PopBtn->setPressBmpPath(QString(":/Images/Resources/Images/LinkWidgetMirrorPotBtnNormal"));
    m_PopBtn->setVisible(true);
    m_DeviceMessageBox = new MessageBox(m_Parent);
    m_DeviceMessageBox->hide();
    m_DeviceMessageBox->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
}

void MirrorLinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MirrorLinkWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Link, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_DeviceMessageBox, SIGNAL(messageWidgetChange(const MessageBox::Type)),
                     m_Parent,           SLOT(onMessageWidgetChange(const MessageBox::Type)),
                     type);
    QObject::connect(m_PopBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent, SLOT(onPopBtnRelease()),
                     type);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
    QObject::connect(m_MirrorToolWidget,  SIGNAL(toolBtnRelease(const int)),
                     m_Parent,            SLOT(onToolBtnRelease(const int)),
                     type);
}

void MirrorLinkWidgetPrivate::touchBeginEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        //        qWarning() << __FUNCTION__ << ptr->touchPointStates();
        QList<QTouchEvent::TouchPoint> touchPoints = ptr->touchPoints();
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        for (int i = 0; i < touchPoints.size(); ++i) {
            //            qWarning() << i << touchPoints.at(i).state() << touchPoints.at(i).pos().toPoint();
            TouchEvent touchEvent;
            touchEvent.state = static_cast<TouchEvent::TouchPointState>(touchPoints.at(i).state());
            touchEvent.x = touchPoints.at(i).pos().toPoint().x();
            touchEvent.y = touchPoints.at(i).pos().toPoint().y();
            touchPointList.append(touchEvent);
        }
        if (touchPointList.size() != 0) {
            QString touchPointXml = translateTouchEvent(touchPointList);
            g_Link->requestTouchStatus(ANDROID_MIRROR, TouchBegin, touchPointXml);
        }
    }
}

void MirrorLinkWidgetPrivate::touchUpdateEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        //        qWarning() << __FUNCTION__ << ptr->touchPointStates();
        QList<QTouchEvent::TouchPoint> touchPoints = ptr->touchPoints();
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        for (int i = 0; i < touchPoints.size(); ++i) {
            //            qWarning() << i << touchPoints.at(i).state() << touchPoints.at(i).pos();
            TouchEvent touchEvent;
            touchEvent.state = static_cast<TouchEvent::TouchPointState>(touchPoints.at(i).state());
            touchEvent.x = touchPoints.at(i).pos().toPoint().x();
            touchEvent.y = touchPoints.at(i).pos().toPoint().y();
            touchPointList.append(touchEvent);
        }
        if (touchPointList.size() != 0) {
            QString touchPointXml = translateTouchEvent(touchPointList);
            g_Link->requestTouchStatus(ANDROID_MIRROR, TouchUpdate, touchPointXml);
        }
    }
}

void MirrorLinkWidgetPrivate::touchEndEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        //        qWarning() << __FUNCTION__ << ptr->touchPointStates();
        QList<QTouchEvent::TouchPoint> touchPoints = ptr->touchPoints();
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        for (int i = 0; i < touchPoints.size(); ++i) {
            //            qWarning() << i << touchPoints.at(i).state() << touchPoints.at(i).pos();
            TouchEvent touchEvent;
            touchEvent.state = static_cast<TouchEvent::TouchPointState>(touchPoints.at(i).state());
            touchEvent.x = touchPoints.at(i).pos().toPoint().x();
            touchEvent.y = touchPoints.at(i).pos().toPoint().y();
            touchPointList.append(touchEvent);
        }
        if (touchPointList.size() != 0) {
            QString touchPointXml = translateTouchEvent(touchPointList);
            g_Link->requestTouchStatus(ANDROID_MIRROR, TouchEnd, touchPointXml);
        }
    }
}

void MirrorLinkWidgetPrivate::onMirrorLinkStatus(const Link_STATUS status)
{
    qDebug() << "onMirrorLinkStatus" << status;
    switch (status) {
    case LINK_STARTING: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MessageBoxWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(false);
        m_DeviceMessageBox->setText(SourceString::Conneting_Mirror_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event2);
        break;
    }
    case LINK_DISCONNECTED: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(true);
        m_DeviceMessageBox->setText(SourceString::No_Mirror_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        break;
    }
    case LINK_EXITING: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        break;
    }
    case LINK_EXITED: {
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::LinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(true);
        m_DeviceMessageBox->setText(SourceString::Remove_Mirror_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        g_Widget->setWidgetType(Widget::T_Link, WidgetStatus::Show);
        break;
    }
    case LINK_SUCCESS: {
        EventEngine::CustomEvent<QString> event(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event);
        g_Widget->setWidgetType(Widget::T_Mirror, WidgetStatus::Show);
        m_MirrorToolWidget->setVisible(true);
        m_Timer->start();
        break;
    }
    default: {
        break;
    }
    }
}

QString MirrorLinkWidgetPrivate::translateTouchEvent(const QList<TouchEvent> &list)
{
    QString touchPointXml;
    touchPointXml.clear();
    QDomDocument domDocument;
    domDocument.appendChild(domDocument.createElement(QString("TouchEvent")));
    QDomElement root = domDocument.firstChildElement(QString("TouchEvent"));
    QDomElement touchPoint = domDocument.createElement(QString("TouchPoint"));
    root.appendChild(touchPoint);
    QDomElement positionState;
    QDomElement positionX;
    QDomElement positionY;
    QDomElement touchPointIndex;
    touchPointXml.clear();
    for (int i = 0; i < list.size(); ++i) {
        positionState = domDocument.createElement(QString("State"));
        positionState.appendChild(domDocument.createTextNode(QString::number(list.at(i).state)));
        touchPointIndex = domDocument.createElement(QString("Index:") + QString::number(i));
        touchPointIndex.appendChild(positionState);
        positionX = domDocument.createElement(QString("X"));
        positionX.appendChild(domDocument.createTextNode(QString::number(list.at(i).x)));
        touchPointIndex.appendChild(positionX);
        positionY = domDocument.createElement(QString("Y"));
        positionY.appendChild(domDocument.createTextNode(QString::number(list.at(i).y)));
        touchPointIndex.appendChild(positionY);
        touchPoint.appendChild(touchPointIndex);
    }
    touchPointXml = domDocument.toString();
    return touchPointXml;
}
