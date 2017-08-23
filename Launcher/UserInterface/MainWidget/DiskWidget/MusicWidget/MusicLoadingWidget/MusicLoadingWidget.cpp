#include "MusicLoadingWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/MainWidget/DiskWidget/MultimediaLoadingWidget.h"
#include <QPainter>

class MusicLoadingWidgetPrivate
{
public:
    explicit MusicLoadingWidgetPrivate(MusicLoadingWidget* parent);
    ~MusicLoadingWidgetPrivate();
    void initialize();
    void connectAllSlots();
    MultimediaLoadingWidget* m_Background;
private:
    MusicLoadingWidget* m_Parent;
};

MusicLoadingWidget::MusicLoadingWidget(QWidget* parent)
    : QWidget(parent)
    , Multimedia::Interface()
    , m_Private(new MusicLoadingWidgetPrivate(this))
{
}

MusicLoadingWidget::~MusicLoadingWidget()
{
}

void MusicLoadingWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), m_Private->m_Background);
    QWidget::resizeEvent(event);
}

void MusicLoadingWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1, 127));
    QWidget::paintEvent(event);
}

bool MusicLoadingWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove: {
        event->accept();
        return true;
        break;
    }
    default: {
        break;
    }
    }
    return QWidget::event(event);
}

void MusicLoadingWidget::onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status)
{
    switch (status) {
    case MPPS_Start: {
        setVisible(true);
        break;
    }
    default: {
        setVisible(false);
        break;
    }
    }
}

MusicLoadingWidgetPrivate::MusicLoadingWidgetPrivate(MusicLoadingWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(false);
}

MusicLoadingWidgetPrivate::~MusicLoadingWidgetPrivate()
{
}

void MusicLoadingWidgetPrivate::initialize()
{
    m_Background = new MultimediaLoadingWidget(m_Parent);
    m_Background->show();
}

void MusicLoadingWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
}
