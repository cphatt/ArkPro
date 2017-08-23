#include "CarplayShortCutWidget.h"
#include "AutoConnect.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "BusinessLogic/Widget/Widget.h"
#include "EventEngine.h"
#include <QVariant>
#include <QDebug>
#include <QPainter>

class CarplayShortCutWidgetPrivate
{
    Q_DISABLE_COPY(CarplayShortCutWidgetPrivate)
public:
    explicit CarplayShortCutWidgetPrivate(CarplayShortCutWidget* parent);
    ~CarplayShortCutWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_Background;
private:
    CarplayShortCutWidget* m_Parent;
};

CarplayShortCutWidget::CarplayShortCutWidget(QWidget *parent)
    : QWidget(parent)
    , Link::Interface()
    , m_Private(new CarplayShortCutWidgetPrivate(this))
{
}

CarplayShortCutWidget::~CarplayShortCutWidget()
{
}

void CarplayShortCutWidget::resizeEvent(QResizeEvent *event)
{
    int width(84);
    int height(84);
    g_Widget->geometryFit((104 - width) * 0.5, (g_Widget->baseTabBarHeight() - height) * 0.5, width, height, m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void CarplayShortCutWidget::customEvent(QEvent *event)
{
    qDebug() << "CarplayShortCutWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::TabBarWidgetAddChild: {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            if (this != ptr->m_Data->value<QWidget*>()) {
                this->setVisible(false);
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

void CarplayShortCutWidget::onLinkStatusChange(const Link_Type type, const Link_STATUS status)
{
    qDebug() << "CarplayShortCutWidget::onLinkStatusChange" << type << status;
    switch (type) {
    case CARPLAY: {
        if (LINK_EXITING == status) {
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(this));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
        } else {
            setVisible(false);
        }
        break;
    }
    default: {
        break;
    }
    }
}

void CarplayShortCutWidget::onBmpButtonRelease()
{
    g_Link->requestLinkStatus(CARPLAY, LINK_STARTING);
}

CarplayShortCutWidgetPrivate::CarplayShortCutWidgetPrivate(CarplayShortCutWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(false);
}

CarplayShortCutWidgetPrivate::~CarplayShortCutWidgetPrivate()
{
}

void CarplayShortCutWidgetPrivate::initialize()
{
    m_Background = new BmpButton(m_Parent);
    m_Background->show();
    m_Background->setNormalBmpPath(QString(":/Images/Resources/Images/CarplayShortCutWidgetBackground"));
    m_Background->setPressBmpPath(QString(":/Images/Resources/Images/CarplayShortCutWidgetBackground"));
}

void CarplayShortCutWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void CarplayShortCutWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Link, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Background, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onBmpButtonRelease()),
                     type);
}
