#include "IdleWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "UserInterface/Common/Utility.h"
#include <QPainter>
#include <QEvent>
#include <QDebug>

class IdleWidgetPrivate
{
    Q_DISABLE_COPY(IdleWidgetPrivate)
public:
    explicit IdleWidgetPrivate(IdleWidget* parent);
    ~IdleWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    IdleWidget* m_Parent;
};

IdleWidget::IdleWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new IdleWidgetPrivate(this))
{
}

IdleWidget::~IdleWidget()
{
}

void IdleWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Utility::customBlackColor());
    QWidget::paintEvent(event);
}

void IdleWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void IdleWidget::mouseReleaseEvent(QMouseEvent *event)
{
    setVisible(false);
    QWidget::mouseReleaseEvent(event);
}

void IdleWidget::customEvent(QEvent *event)
{
    qDebug() << "IdleWidget::customEvent" << event->type();
    if (CustomEventType::IdleWidgetStatus == event->type()) {
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
                setVisible(true);
            } else if (WidgetStatus::RequestHide == *temp) {
                setVisible(false);
            }
        }
    }
    QWidget::customEvent(event);
}

IdleWidgetPrivate::IdleWidgetPrivate(IdleWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
}

IdleWidgetPrivate::~IdleWidgetPrivate()
{
    g_EventEngine->detachCustomEvent(m_Parent);
}

void IdleWidgetPrivate::initialize()
{
}

void IdleWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
