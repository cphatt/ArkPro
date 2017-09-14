#include "MusicWidget.h"
#include "BusinessLogic/Setting/Setting.h"
#include "UserInterface/Common/Utility.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/Slider.h"
#include "UserInterface/Common/TextWidget.h"
#include "MusicShortCutWidget/MusicShortCutWidget.h"
#include "MusicToolWidget/MusicToolWidget.h"
#include "MusicLoadingWidget/MusicLoadingWidget.h"
#include "EventEngine.h"
#include "AutoConnect.h"
#include <QPainter>
#include <QDebug>

class MusicWidgetPrivate
{
    Q_DISABLE_COPY(MusicWidgetPrivate)
public:
    explicit MusicWidgetPrivate(MusicWidget *parent);
    ~MusicWidgetPrivate();
    void initialize();
    void connectAllSlots();
    MusicToolWidget* m_MusicToolWidget;
    MusicLoadingWidget* m_MusicLoadingWidget;
    MusicShortCutWidget* m_MusicShortCutWidget;
private:
    MusicWidget* m_Parent;
};

MusicWidget::MusicWidget(QWidget *parent)
    : QWidget(parent)
    , Multimedia::Interface()
    , Widget::Interface()
    , m_Private(new MusicWidgetPrivate(this))
{
}

MusicWidget::~MusicWidget()
{
}

void MusicWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void MusicWidget::paintEvent(QPaintEvent *event)
{
    //    painter.setRenderHint(QPainter::Antialiasing, true);
    //    painter.drawPixmap(QRect(0, itemHeight * 2, 250, 250), m_Private->m_Conver);
    //    painter.drawRect(QRect(0, itemHeight * 2, 250, 250));
    QWidget::paintEvent(event);
}

void MusicWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "MusicWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_Music: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_Music, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);
        }
        break;
    }
    default : {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }

    }
}

void MusicWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    switch (status) {
    case MPPS_Start: {
        setVisible(true);
        break;
    }
    case MPPS_Play: {
        setVisible(true);
        break;
    }
    case MPPS_Pause:
    case MPPS_Stop: {
        setVisible(true);
        break;
    }
    default : {
        break;
    }
    }
}

MusicWidgetPrivate::MusicWidgetPrivate(MusicWidget *parent)
    : m_Parent(parent)
{
    m_MusicToolWidget = NULL;
    m_MusicLoadingWidget = NULL;
    m_MusicShortCutWidget = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

MusicWidgetPrivate::~MusicWidgetPrivate()
{
}

void MusicWidgetPrivate::initialize()
{
    m_MusicToolWidget = new MusicToolWidget(m_Parent);
    m_MusicLoadingWidget = new MusicLoadingWidget(m_Parent);
    m_MusicShortCutWidget = new MusicShortCutWidget(m_Parent);
}

void MusicWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
