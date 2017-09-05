#include "MusicShortCutWidget.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/BmpButton.h"
#include "EventEngine.h"
#include <QVariant>
#include <QDebug>
#include <QPainter>

class MusicShortCutWidgetPrivate
{
    Q_DISABLE_COPY(MusicShortCutWidgetPrivate)
public:
    explicit MusicShortCutWidgetPrivate(MusicShortCutWidget *parent);
    ~MusicShortCutWidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    void connectAllSlots();
    BmpButton* m_Background;
private:
    MusicShortCutWidget* m_Parent;
};

MusicShortCutWidget::MusicShortCutWidget(QWidget *parent)
    : QWidget(parent)
    , Multimedia::Interface()
    , m_Private(new MusicShortCutWidgetPrivate(this))
{
}

MusicShortCutWidget::~MusicShortCutWidget()
{
}

void MusicShortCutWidget::resizeEvent(QResizeEvent *event)
{
    int width(53);
    int height(53);
    g_Widget->geometryFit((104 - width) * 0.5, (g_Widget->baseTabBarHeight() - height) * 0.5 - 10, width, height, m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void MusicShortCutWidget::customEvent(QEvent *event)
{
    qDebug() << "ImageShortCutWidget::customEvent" << event->type();
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

void MusicShortCutWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    qDebug() << "MusicShortCutWidget::onMusicPlayerPlayStatus" << status;
    switch (status) {
    case MPPS_Start: {
        QVariant* variant = new QVariant();
        variant->setValue(static_cast<QWidget*>(this));
        EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::TabBarWidgetAddChild), variant);
        g_EventEngine->sendCustomEvent(event);
        g_Widget->geometryFit(0 + 84 * 3, 0, 104, g_Widget->baseTabBarHeight(), this);
        break;
    }
    case MPPS_Exit: {
        setVisible(false);
        break;
    }
    default: {
        break;
    }
    }
}

void MusicShortCutWidget::onBmpButtonRelease()
{
    g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::RequestShow);
}

MusicShortCutWidgetPrivate::MusicShortCutWidgetPrivate(MusicShortCutWidget* parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    initialize();
    receiveAllCustomEvent();
    connectAllSlots();
    m_Parent->setVisible(false);
}

MusicShortCutWidgetPrivate::~MusicShortCutWidgetPrivate()
{
}

void MusicShortCutWidgetPrivate::initialize()
{
    m_Background = new BmpButton(m_Parent);
    m_Background->show();
//    m_Background->setNormalBmpPath(QString(":/Images/Resources/Images/MusicShortCutWidgetBackground"));
//    m_Background->setPressBmpPath(QString(":/Images/Resources/Images/MusicShortCutWidgetBackground"));
}

void MusicShortCutWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}

void MusicShortCutWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
//    QObject::connect(m_Background, SIGNAL(bmpButtonRelease()),
//                     m_Parent,     SLOT(onBmpButtonRelease()),
//                     type);
}
