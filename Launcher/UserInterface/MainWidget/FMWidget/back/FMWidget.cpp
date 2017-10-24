#include "FMWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "FMToolWidget/FMToolWidget.h"
#include <QPainter>
#include <QEvent>

class FMWidgetPrivate
{
public:
    explicit FMWidgetPrivate(FMWidget* parent);
    ~FMWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    FMToolWidget* m_FMToolWidget;
private:
    FMWidget* m_Parent;
};

FMWidget::FMWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new FMWidgetPrivate(this))
{
}

FMWidget::~FMWidget()
{
}

void FMWidget::paintEvent(QPaintEvent *event)
{
#if defined(gcc)
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1, 127));
#endif
    QWidget::paintEvent(event);
}

void FMWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, g_Widget->baseStatusBarHeight(), g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - g_Widget->baseStatusBarHeight() - g_Widget->baseTabBarHeight(), this);
    QWidget::resizeEvent(event);
}

void FMWidget::customEvent(QEvent *event)
{
    qDebug() << "FMWidget::customEvent" << event->type();
    if (CustomEventType::FMWidgetStatus == event->type()) {
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

void FMWidget::mouseReleaseEvent(QMouseEvent *event)
{
    setVisible(false);
    QWidget::mouseReleaseEvent(event);
}

FMWidgetPrivate::FMWidgetPrivate(FMWidget *parent)
    : m_Parent(parent)
{
    initialize();
    receiveAllCustomEvent();
}

FMWidgetPrivate::~FMWidgetPrivate()
{
}

void FMWidgetPrivate::initialize()
{
//    m_FMToolWidget = new FMToolWidget(m_Parent);
    m_Parent->setVisible(false);
}

void FMWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
