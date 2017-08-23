#include "GeneralWidget.h"
#include "UserInterface/Common/Utility.h"
#include "UserInterface/Common/TextWidget.h"
#include "AutoConnect.h"
#include "GeneralListView/GeneralListView.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/ScrollBar.h"
#include "BusinessLogic/Setting/Setting.h"
#include <QPainter>
#include <QDebug>

namespace SourceString {
static const QString Calibrate = QString(QObject::tr("Calibrate"));

}

class GeneralWidgetPrivate
{
    Q_DISABLE_COPY(GeneralWidgetPrivate)
public:
    explicit GeneralWidgetPrivate(GeneralWidget* parent);
    ~GeneralWidgetPrivate();
    void initialize();
    void connectAllSlots();
    GeneralListView* m_GeneralListView;
    TextWidget* m_CalibreteWidgetText;
    BmpWidget* m_CalibreteWidget;
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
void GeneralWidget::mousePressEvent(QMouseEvent *event)
{


    system("ts_calibrate");
    qDebug() << "finish Calibrate" ;

    g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
    g_Widget->setWidgetType(Widget::T_Setting, WidgetStatus::RequestShow);

    QWidget::mousePressEvent(event);
}

void GeneralWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(278, 73, g_Widget->baseWindowWidth() - 278, 626 - 73, this);
    g_Widget->geometryFit(174, 64, 800 - 174, 64, this);
    g_Widget->geometryFit(0, 0, 800 - 174, 64, m_Private->m_CalibreteWidget);
    g_Widget->geometryFit((800 - 174 -300) / 2, 0, 300, 64, m_Private->m_CalibreteWidgetText);
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
   // m_GeneralListView = NULL;
//    m_GeneralScrollBar = NULL;
    m_CalibreteWidget = NULL;
    m_CalibreteWidgetText = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

GeneralWidgetPrivate::~GeneralWidgetPrivate()
{
}

void GeneralWidgetPrivate::initialize()
{
  //  m_GeneralListView = new GeneralListView(m_Parent);
//    m_GeneralScrollBar = new ScrollBar(m_Parent);
//    m_GeneralScrollBar->hide();
//    m_GeneralScrollBar->setItemHeight(94 * g_Widget->widthScalabilityFactor());
    m_CalibreteWidget = new BmpWidget(m_Parent);
    m_CalibreteWidget->show();
    m_CalibreteWidget->setBackgroundBmpPath(QString(":/Images/Resources/Images/LanguageSoundWidgetBackground"));

    m_CalibreteWidgetText = new TextWidget(m_CalibreteWidget);
    m_CalibreteWidgetText->setVisible(true);
    m_CalibreteWidgetText->setText(SourceString::Calibrate);
    int fontPointSize(25 * g_Widget->widthScalabilityFactor());
    m_CalibreteWidgetText->setFontPointSize(fontPointSize);
    int flag(Qt::AlignHCenter | Qt::AlignVCenter);
    m_CalibreteWidgetText->setAlignmentFlag(flag);
}

void GeneralWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
