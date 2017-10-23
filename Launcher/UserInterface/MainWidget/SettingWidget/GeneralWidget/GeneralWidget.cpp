#include "GeneralWidget.h"
#include "UserInterface/Common/Utility.h"
#include "AutoConnect.h"
#include "GeneralListView/GeneralListView.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/ScrollBar.h"
#include "BusinessLogic/Setting/Setting.h"
#include <QPainter>
#include <QDebug>

class GeneralWidgetPrivate
{
    Q_DISABLE_COPY(GeneralWidgetPrivate)
public:
    explicit GeneralWidgetPrivate(GeneralWidget* parent);
    ~GeneralWidgetPrivate();
    void initialize();
    void connectAllSlots();
    GeneralListView* m_GeneralListView;
private:
    GeneralWidget* m_Parent;
};

GeneralWidget::GeneralWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new GeneralWidgetPrivate(this))
{
}

GeneralWidget::~GeneralWidget()
{
}


void GeneralWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::Show);
    QWidget::showEvent(event);
}


void GeneralWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(170, 63, g_Widget->baseWindowWidth() - 170, 626 - 63, this);
    QWidget::resizeEvent(event);
}

void GeneralWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::green);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void GeneralWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_SettingGeneral: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
//            m_Private->m_GeneralScrollBar->setVisible(true);
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingLanguage:
    case Widget::T_SettingEffect:
    case Widget::T_SettingField: {
        if (WidgetStatus::Show == status) {
            setVisible(false);
        }
        break;
    }
    default: {
        break;
    }
    }
}

GeneralWidgetPrivate::GeneralWidgetPrivate(GeneralWidget *parent)
    : m_Parent(parent)
{
    m_GeneralListView = NULL;
//    m_GeneralScrollBar = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

GeneralWidgetPrivate::~GeneralWidgetPrivate()
{
}

void GeneralWidgetPrivate::initialize()
{
    m_GeneralListView = new GeneralListView(m_Parent);
//    m_GeneralScrollBar = new ScrollBar(m_Parent);
//    m_GeneralScrollBar->hide();
//    m_GeneralScrollBar->setItemHeight(94 * g_Widget->widthScalabilityFactor());
}

void GeneralWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
