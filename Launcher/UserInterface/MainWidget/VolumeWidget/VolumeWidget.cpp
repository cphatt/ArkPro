#include "VolumeWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "BusinessLogic/Audio/Audio.h"
#include "BusinessLogic/Widget/Widget.h"
#include "AutoConnect.h"
#include "VolumeToolWidget/VolumeToolWidget.h"
#include <QPainter>
#include <QEvent>
#include <QTimer>
class VolumeWidgetPrivate
{
    Q_DISABLE_COPY(VolumeWidgetPrivate)
public:
    explicit VolumeWidgetPrivate(VolumeWidget* parent);
    ~VolumeWidgetPrivate();

    void initialize();
    void connectAllSlots();
    void receiveAllCustomEvent();
    VolumeToolWidget* m_VolumeToolWidget;
    QTimer* m_Timer;
private:
    VolumeWidget* m_Parent;
};

VolumeWidget::VolumeWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new VolumeWidgetPrivate(this))
{

}

VolumeWidget::~VolumeWidget()
{
}

void VolumeWidget::paintEvent(QPaintEvent *event)
{
#if defined(gcc)
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1, 127));
#endif
    QWidget::paintEvent(event);
}

void VolumeWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    qDebug() << "VolumeWidget::resizeEvent" << geometry();
    QWidget::resizeEvent(event);
}


void VolumeWidget::customEvent(QEvent *event)
{
    qDebug() << "VolumeWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->initialize();
        m_Private->connectAllSlots();
        break;
    }
    case CustomEventType::VolumeWidgetStatus: {
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
        m_Private->m_Timer->start();
        if (NULL != temp) {
            if (WidgetStatus::RequestShow == *temp) {
                setVisible(true);
            } else if (WidgetStatus::RequestHide == *temp) {
                setVisible(false);
            }
        }
        break;
    }
    case CustomEventType::VolumeWidgetClick:{
          m_Private->m_Timer->start();

    }
    default: {
        break;
    }
    }
    QWidget::customEvent(event);
}

void VolumeWidget::mouseReleaseEvent(QMouseEvent *event)
{
    setVisible(false);
    QWidget::mouseReleaseEvent(event);
}
void VolumeWidget::onTimeout()
{
    setVisible(false);
    qDebug() << "-----------------------------";
}

VolumeWidgetPrivate::VolumeWidgetPrivate(VolumeWidget *parent)
    : m_Parent(parent)
{
    m_VolumeToolWidget = NULL;
    m_Timer = NULL;
    initialize();
    receiveAllCustomEvent();


    m_Parent->setVisible(false);
    Q_UNUSED(g_Audio);
}

VolumeWidgetPrivate::~VolumeWidgetPrivate()
{
}


void VolumeWidgetPrivate::initialize()
{
    m_VolumeToolWidget = new VolumeToolWidget(m_Parent);

    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(3000);
}
void VolumeWidgetPrivate::connectAllSlots(){
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}
void VolumeWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
