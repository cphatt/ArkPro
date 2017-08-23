#include "MessageBoxWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include <QEvent>
#include <QPainter>
#include <QDebug>
#include <QDebug>
#include <QVariant>

class MessageBoxWidgetPrivate
{
    Q_DISABLE_COPY(MessageBoxWidgetPrivate)
public:
    explicit MessageBoxWidgetPrivate(MessageBoxWidget *parent);
    ~MessageBoxWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    MessageBoxWidget* m_Parent;
};

MessageBoxWidget::MessageBoxWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MessageBoxWidgetPrivate(this))
{
}

MessageBoxWidget::~MessageBoxWidget()
{
}

void MessageBoxWidget::customEvent(QEvent *event)
{
    qDebug() << "MessageBoxWidget::customEvent" << event->type();
    if (CustomEventType::MessageBoxWidgetAddChild == event->type()) {
        EventEngine::CustomEvent<QVariant>* ptr = dynamic_cast<EventEngine::CustomEvent<QVariant>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)
                && (ptr->m_Data->canConvert<QWidget*>())
                && (ptr->m_Data->value<QWidget*>())) {
            ptr->m_Data->value<QWidget*>()->setParent(this);
            ptr->m_Data->value<QWidget*>()->setVisible(true);
        }
    } else if (CustomEventType::MessageBoxWidgetStatus == event->type()) {
        EventEngine::CustomEvent<QString>* ptr = dynamic_cast<EventEngine::CustomEvent<QString>*>(event);
        if ((NULL != ptr)
                && (ptr->m_Data)) {
            if (WidgetStatus::RequestShow == (*ptr->m_Data)) {
                setVisible(true);
            } else if (WidgetStatus::RequestHide == (*ptr->m_Data)) {
                setVisible(false);
            }
        }
    }
    QWidget::customEvent(event);
}

void MessageBoxWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void MessageBoxWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

MessageBoxWidgetPrivate::MessageBoxWidgetPrivate(MessageBoxWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
}

MessageBoxWidgetPrivate::~MessageBoxWidgetPrivate()
{
}

void MessageBoxWidgetPrivate::initialize()
{
}

void MessageBoxWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
