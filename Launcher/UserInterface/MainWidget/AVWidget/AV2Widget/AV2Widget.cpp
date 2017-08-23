#include "AV2Widget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/Common/Utility.h"
#include "EventEngine.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/BmpWidget.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>

namespace SourceString {
static const QString No_AV2_Signal = QString(QObject::tr("No AV2 Signal..."));
static const QString Conneting_AV2_Signal = QString(QObject::tr("Conneting AV2 Signal..."));
}

class AV2WidgetPrivate
{
    Q_DISABLE_COPY(AV2WidgetPrivate)
public:
    explicit AV2WidgetPrivate(AV2Widget* parent);
    ~AV2WidgetPrivate();
    void initialize();
    void connectAllSlots();
    QColor m_BackgroundColor;
    BmpWidget* m_ShortCutWidget;
    QTimer* m_Timer;
    QRect m_TouchRect;
    MessageBox* m_DeviceMessageBox;
    bool m_ShowFlag;
private:
    AV2Widget* m_Parent;
};

AV2Widget::AV2Widget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new AV2WidgetPrivate(this))
{
}

AV2Widget::~AV2Widget()
{
}

void AV2Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(m_Private->m_BackgroundColor));
    QWidget::paintEvent(event);
}

void AV2Widget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_DeviceMessageBox);
    qDebug() << "m_Private->m_DeviceMessageBox" << m_Private->m_DeviceMessageBox->geometry();
    QWidget::resizeEvent(event);
}

void AV2Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "AV2Widget::mouseReleaseEvent" << event->pos();
    if (isVisible()) {
        if (m_Private->m_TouchRect.contains(event->pos())) {
            if (m_Private->m_TouchRect == g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight())) {
                g_Widget->setWidgetType(Widget::T_AV2, WidgetStatus::Show);
            } else {
                g_Widget->setWidgetType(Widget::T_AV2FullScreen, WidgetStatus::Show);
            }
        }
    }
    QWidget::mouseReleaseEvent(event);
}

void AV2Widget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_Back: {
        if (WidgetStatus::RequestShow == status) {
            if (isVisible()) {
                g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
            }
        }
        break;
    }
    case Widget::T_AV2: {
        if (WidgetStatus::RequestShow == status) {
            g_AV->startAV(AVT_2, g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor());
        } else if (WidgetStatus::Show == status) {
            m_Private->m_TouchRect = g_Widget->geometryFit(0, 50, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight() - 50 - 70);
            m_Private->m_Timer->start();
            m_Private->m_ShowFlag = true;
            setVisible(true);
        }
        break;
    }
    case Widget::T_AV2FullScreen: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_AV2FullScreen, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_TouchRect = g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight());
            m_Private->m_Timer->stop();
        }
        break;
    }
    default: {
        if (WidgetStatus::Show == status) {
            m_Private->m_DeviceMessageBox->setVisible(false);
            setVisible(false);
            if (m_Private->m_ShowFlag) {
                g_AV->stopAV(AVT_2);
                m_Private->m_ShortCutWidget->setVisible(false);
            }
            m_Private->m_ShowFlag = false;
            m_Private->m_Timer->stop();
        }
        break;
    }
    }
}

void AV2Widget::onAVStatus(const AVType type, const AVStatus status)
{
    if (AVT_2 == type) {
        if (AVS_Connecting == status) {
            m_Private->m_BackgroundColor = Utility::customBlackColor();
            m_Private->m_DeviceMessageBox->setVisible(true);
            m_Private->m_DeviceMessageBox->setText(SourceString::Conneting_AV2_Signal);
            g_Widget->setWidgetType(Widget::T_AV2, WidgetStatus::Show);
            QVariant* variant = new QVariant();
            variant->setValue(static_cast<QWidget*>(m_Private->m_ShortCutWidget));
            EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
            g_EventEngine->sendCustomEvent(event);
            g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), m_Private->m_ShortCutWidget);
            update();
        } else if (AVS_Connected == status) {
            m_Private->m_BackgroundColor = Utility::videoColor();
            m_Private->m_DeviceMessageBox->setVisible(false);
            update();
        } else if (AVS_Disconnect == status) {
            m_Private->m_BackgroundColor = Utility::customBlackColor();
            m_Private->m_DeviceMessageBox->setText(SourceString::No_AV2_Signal);
            m_Private->m_DeviceMessageBox->setVisible(true);
            if (isVisible()) {
                g_Widget->setWidgetType(Widget::T_AV2, WidgetStatus::Show);
            }
        }
    }
}

void AV2Widget::onTimeout()
{
    qDebug() << "AV2Widget::onTimeout";
    g_Widget->setWidgetType(Widget::T_AV2FullScreen, WidgetStatus::RequestShow);
}

AV2WidgetPrivate::AV2WidgetPrivate(AV2Widget *parent)
    : m_Parent(parent)
{
    m_ShowFlag = false;
    m_DeviceMessageBox = NULL;
    m_Timer = NULL;
    m_ShortCutWidget = NULL;
    m_TouchRect = QRect(0, 0, 0, 0);
    m_BackgroundColor = Utility::customBlackColor();
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

AV2WidgetPrivate::~AV2WidgetPrivate()
{
}

void AV2WidgetPrivate::initialize()
{
    m_ShortCutWidget = new BmpWidget(m_Parent);
    m_ShortCutWidget->hide();
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(5000);
    m_DeviceMessageBox = new MessageBox(m_Parent);
    m_DeviceMessageBox->hide();
    m_DeviceMessageBox->setAutoHide(false);
    m_DeviceMessageBox->setFontPointSize(18 * g_Widget->widthScalabilityFactor());
}

void AV2WidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_AV, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}
