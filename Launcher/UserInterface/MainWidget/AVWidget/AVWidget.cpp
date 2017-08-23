#include "AVWidget.h"
#include "AV1Widget/AV1Widget.h"
#include "AV2Widget/AV2Widget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include <QTimer>
#include <QRect>
#include <QPainter>

class AVWidgetPrivate
{
    Q_DISABLE_COPY(AVWidgetPrivate)
public:
    explicit AVWidgetPrivate(AVWidget* parent);
    ~AVWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    AV1Widget* m_AV1Widget;
    AV2Widget* m_AV2Widget;
    QTimer* m_Timer;
    QRect m_TouchRect;
private:
    AVWidget* m_Parent;
};

AVWidget::AVWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new AVWidgetPrivate(this))
{
}

AVWidget::~AVWidget()
{
}

void AVWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void AVWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), Utility::mainWidgetBackgroundColor());
    QWidget::paintEvent(event);
}

void AVWidget::hideEvent(QHideEvent *event)
{
    if (isVisible()) {
        EventEngine::CustomEvent<QString> event1(CustomEventType::FMWidgetStatus, new QString(WidgetStatus::RequestHide));
        g_EventEngine->sendCustomEvent(event1);
    }
    QWidget::hideEvent(event);
}

void AVWidget::customEvent(QEvent *event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->initialize();
        m_Private->connectAllSlots();
        break;
    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void AVWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_AV1:
    case Widget::T_AV1FullScreen:
    case Widget::T_AV2:
    case Widget::T_AV2FullScreen: {
        if (WidgetStatus::Show == status) {
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

AVWidgetPrivate::AVWidgetPrivate(AVWidget *parent)
    : m_Parent(parent)
{
    m_AV1Widget = NULL;
    m_AV2Widget = NULL;
    receiveAllCustomEvent();
    m_Parent->setVisible(false);
}

AVWidgetPrivate::~AVWidgetPrivate()
{
}

void AVWidgetPrivate::initialize()
{
    m_AV1Widget = new AV1Widget(m_Parent);
    m_AV2Widget = new AV2Widget(m_Parent);
}

void AVWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void AVWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
