#include "FMWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "BusinessLogic/Widget/Widget.h"
#include "FMToolWidget/FMToolWidget.h"
#include "BusinessLogic/Audio/Audio.h"
#include <QPainter>
#include <QEvent>

class FMWidgetPrivate
{
    Q_DISABLE_COPY(FMWidgetPrivate)
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
    painter.fillRect(rect(), QColor(255, 0, 1, 127));
#endif
    QWidget::paintEvent(event);
}

void FMWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    qDebug() << "FMWidget::resizeEvent" << geometry();
    QWidget::resizeEvent(event);
}

void FMWidget::customEvent(QEvent *event)
{
    qDebug() << "FMWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->initialize();
        break;
    }
    case CustomEventType::FMWidgetStatus: {
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
                setVisible(true);
            } else if (WidgetStatus::RequestHide == *temp) {
                setVisible(false);
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

void FMWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (isVisible()) {
        setVisible(false);
    }
    QWidget::mouseReleaseEvent(event);
}

FMWidgetPrivate::FMWidgetPrivate(FMWidget *parent)
    : m_Parent(parent)
{
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
    Q_UNUSED(g_Audio);
}

FMWidgetPrivate::~FMWidgetPrivate()
{
}

void FMWidgetPrivate::initialize()
{
    m_FMToolWidget = new FMToolWidget(m_Parent);
}

void FMWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
