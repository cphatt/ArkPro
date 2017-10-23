#include "CarplayLinkWidget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "CarplayShortCutWidget/CarplayShortCutWidget.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QDomElement>

namespace SourceString {
static const QString No_Carplay_Device = QString(QObject::tr("No Carplay Device..."));
static const QString Conneting_Carplay_Device = QString(QObject::tr("Conneting Carplay Device..."));
static const QString Remove_Carplay_Device = QString(QObject::tr("Remove Carplay Device..."));
}

class CarplayLinkWidgetPrivate
{
    Q_DISABLE_COPY(CarplayLinkWidgetPrivate)
public:
    explicit CarplayLinkWidgetPrivate(CarplayLinkWidget* parent);
    ~CarplayLinkWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    void onCarplayLinkStatus(const Link_STATUS status);
    void touchBeginEventHandler(QEvent* event);
    void touchUpdateEventHandler(QEvent* event);
    void touchEndEventHandler(QEvent* event);
    QString translateTouchEvent(const QList<TouchEvent> &list);
    CarplayShortCutWidget* m_CarplayShortCutWidget;
    MessageBox* m_DeviceMessageBox;
    QPoint m_Src;
    QPoint m_Dest;
private:
    CarplayLinkWidget* m_Parent;
};

CarplayLinkWidget::CarplayLinkWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , Link::Interface()
    , m_Private(new CarplayLinkWidgetPrivate(this))
{
}

CarplayLinkWidget::~CarplayLinkWidget()
{
}

bool CarplayLinkWidget::event(QEvent *event)
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

void CarplayLinkWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void CarplayLinkWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(QColor(0x00, 0x00, 0x00)));
    QWidget::paintEvent(event);
}

void CarplayLinkWidget::mousePressEvent(QMouseEvent *event)
{
    if (QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
        QList<TouchEvent> touchPointList;
        touchPointList.clear();
        TouchEvent touchEvent;
        touchEvent.state = TouchEvent::TouchPointPressed;
        touchEvent.x = event->pos().x();
        touchEvent.y = event->pos().y();
        touchPointList.append(touchEvent);
        QString touchPointXml = m_Private->translateTouchEvent(touchPointList);
        g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
    }
}

void CarplayLinkWidget::mouseReleaseEvent(QMouseEvent *event)
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
        g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
    }
}

void CarplayLinkWidget::mouseMoveEvent(QMouseEvent *event)
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
        g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
    }
}

void CarplayLinkWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::CarPlayLinkMessageWidgetAddChild: {
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

void CarplayLinkWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Carplay: {
        if (WidgetStatus::RequestShow == status) {
            g_Link->requestLinkStatus(CARPLAY, LINK_STARTING);  //发送链接请求
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

void CarplayLinkWidget::onLinkStatusChange(const Link_Type type, const Link_STATUS status)
{
    qDebug() << "CarplayLinkWidget::onLinkStatusChange" << type << status;
    switch (type) {
        case CARPLAY: {
            m_Private->onCarplayLinkStatus(status);
            break;
        }
        default: {
            break;
        }
    }
}

CarplayLinkWidgetPrivate::CarplayLinkWidgetPrivate(CarplayLinkWidget* parent)
    : m_Parent(parent)

{
    m_CarplayShortCutWidget = NULL;
    m_DeviceMessageBox = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(false);
}

CarplayLinkWidgetPrivate::~CarplayLinkWidgetPrivate()
{
}

void CarplayLinkWidgetPrivate::initialize()
{
    m_CarplayShortCutWidget = new CarplayShortCutWidget(m_Parent);
    m_DeviceMessageBox = new MessageBox(m_Parent);
   // m_DeviceMessageBox->hide();
    m_DeviceMessageBox->setFontPointSize(15 * g_Widget->widthScalabilityFactor());
}

void CarplayLinkWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void CarplayLinkWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Link, m_Parent);
}

void CarplayLinkWidgetPrivate::onCarplayLinkStatus(const int status)  //具体做法和
{
    qDebug() << "onCarplayLinkStatus" << status;
    switch (status) {
    case LINK_STARTING: {
        g_Widget->setWidgetType(Widget::T_CarplayWidget, WidgetStatus::RequestShow);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::MessageBoxWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(false);
        m_DeviceMessageBox->setText(SourceString::Conneting_Carplay_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestShow));
        g_EventEngine->sendCustomEvent(event2);
        break;
    }
    case LINK_DISCONNECTED: {

        g_Widget->setWidgetType(Widget::T_CarplayWidget, WidgetStatus::RequestShow);
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::CarPlayLinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(false);
        m_DeviceMessageBox->setText(SourceString::No_Carplay_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        break;
    }
    case LINK_EXITING: {
        g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
        break;
    }
    case LINK_EXITED: {
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(m_DeviceMessageBox));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::CarPlayLinkMessageWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        m_DeviceMessageBox->setAutoHide(false);
        m_DeviceMessageBox->setText(SourceString::Remove_Carplay_Device);
        g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_DeviceMessageBox);
        g_Widget->setWidgetType(Widget::T_CarplayWidget, WidgetStatus::Show);
        break;
    }
    case LINK_SUCCESS: {
        EventEngine::CustomEvent<QString> event2(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event2);
        g_Widget->setWidgetType(Widget::T_Carplay, WidgetStatus::Show);
        break;
    }
    default: {
        break;
    }
    }
}

void CarplayLinkWidgetPrivate::touchBeginEventHandler(QEvent *event)
{
    QTouchEvent* ptr = static_cast<QTouchEvent*>(event);
    if (NULL != ptr) {
        qWarning() << __FUNCTION__ << ptr->touchPointStates();
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
            g_Link->requestTouchStatus(CARPLAY, TouchBegin, touchPointXml);
        }
    }
}

void CarplayLinkWidgetPrivate::touchUpdateEventHandler(QEvent *event)
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
            g_Link->requestTouchStatus(CARPLAY, TouchUpdate, touchPointXml);
        }
    }
}

void CarplayLinkWidgetPrivate::touchEndEventHandler(QEvent *event)
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
            g_Link->requestTouchStatus(CARPLAY, TouchEnd, touchPointXml);
        }
    }
}

QString CarplayLinkWidgetPrivate::translateTouchEvent(const QList<TouchEvent> &list)
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
