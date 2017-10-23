#include "DateTimeWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "UserInterface/Common/Utility.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/TextWidget.h"
#include "EventEngine.h"
#include "BusinessLogic/Audio/Audio.h"
#include "BusinessLogic/Widget/Widget.h"
#include "AutoConnect.h"
#include <QPainter>
#include <QEvent>
#include <QTimer>
#include <QDateTime>
#include <QDateTimeEdit>
#include <time.h>
#include "TimeSelect/TimeSelect.h"
class DateTimeWidgetPrivate
{
    Q_DISABLE_COPY(DateTimeWidgetPrivate)
public:
    explicit DateTimeWidgetPrivate(DateTimeWidget* parent);
    ~DateTimeWidgetPrivate();

    void initialize();
    void connectAllSlots();
    void receiveAllCustomEvent();

    TimeSelect *m_TimeSeclet_Year;
    TimeSelect *m_TimeSeclet_Mouth;
    TimeSelect *m_TimeSeclet_Day;
    TimeSelect *m_TimeSeclet_Hour;
    TimeSelect *m_TimeSeclet_Minute;
    BmpButton *m_OKBtn;
    TextWidget*m_OKText;
private:
    DateTimeWidget* m_Parent;
};

DateTimeWidget::DateTimeWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new DateTimeWidgetPrivate(this))
{
    qDebug() << "------------------------as";
}

DateTimeWidget::~DateTimeWidget()
{
}

void DateTimeWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
            setVisible(false);
}
void DateTimeWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Utility::mainWidgetBackgroundColor()));
    QWidget::paintEvent(event);
}
void DateTimeWidget::resizeEvent(QResizeEvent *event)
{
    int hight(39);
    int weight(20);
    g_Widget->geometryFit(172, 64, 625, 355, this);

    g_Widget->geometryFit(  0 + weight, hight, 100, 240, m_Private->m_TimeSeclet_Year);
    g_Widget->geometryFit(120 + weight, hight, 100, 240, m_Private->m_TimeSeclet_Mouth);
    g_Widget->geometryFit(240 + weight, hight, 100, 240, m_Private->m_TimeSeclet_Day);
    g_Widget->geometryFit(360 + weight, hight, 100, 240, m_Private->m_TimeSeclet_Hour);
    g_Widget->geometryFit(480 + weight, hight, 100, 240, m_Private->m_TimeSeclet_Minute);
    g_Widget->geometryFit(240 + weight, 300, 100, 42, m_Private->m_OKBtn);
    g_Widget->geometryFit(0, 5, 100, 32, m_Private->m_OKText);
    qDebug() << "DateTimeWidget::resizeEvent" << geometry();
    QWidget::resizeEvent(event);
}

void DateTimeWidget::OkBtnRelease(){
    int y  = m_Private->m_TimeSeclet_Year->getNum();
    int m  = m_Private->m_TimeSeclet_Mouth->getNum();
    int d  = m_Private->m_TimeSeclet_Day->getNum();
    int h  = m_Private->m_TimeSeclet_Hour->getNum();
    int min  = m_Private->m_TimeSeclet_Minute->getNum();
        QDateTime dt(QDate(y,m,d), QTime(h,min));
    qDebug() << dt;
            time_t ttNewTime = (time_t)dt.toTime_t();
    #ifndef gcc
        int r = stime(&ttNewTime);

    #endif
         g_Setting->setDateTime(dt);
         perror("stime :");
        setVisible(false);
        g_Widget->setWidgetType(Widget::T_SettingGeneral, WidgetStatus::RequestShow);
}
void DateTimeWidget::customEvent(QEvent *event)
{
    qDebug() << "DateTimeWidget::customEvent" << event->type();
    switch (event->type()) {
    case CustomEventType::MainWidgetShow: {
        m_Private->initialize();
        m_Private->connectAllSlots();
        break;
    }
    case CustomEventType::ShowDateTimeWidget: {
        QString* temp = static_cast<EventEngine::CustomEvent<QString>*>(event)->m_Data;
       // m_Private->m_Timer->start();
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

void DateTimeWidget::mouseReleaseEvent(QMouseEvent *event)
{

    QWidget::mouseReleaseEvent(event);
}

DateTimeWidgetPrivate::DateTimeWidgetPrivate(DateTimeWidget *parent)
    : m_Parent(parent)
{
    m_TimeSeclet_Year = NULL;
    m_TimeSeclet_Mouth = NULL;
    m_TimeSeclet_Day = NULL;
    m_TimeSeclet_Minute = NULL;
    m_TimeSeclet_Hour = NULL;

    receiveAllCustomEvent();

    m_Parent->setVisible(false);
}

DateTimeWidgetPrivate::~DateTimeWidgetPrivate()
{
}


void DateTimeWidgetPrivate::initialize()
{

    m_TimeSeclet_Year = new TimeSelect(m_Parent);
    m_TimeSeclet_Year->setText(QString(QObject::tr("Year")));
    m_TimeSeclet_Year->setNum(2017);
    m_TimeSeclet_Mouth = new TimeSelect(m_Parent);
    m_TimeSeclet_Mouth->setText(QString(QObject::tr("Mouth")));
    m_TimeSeclet_Mouth->setNum(10);
    m_TimeSeclet_Day = new TimeSelect(m_Parent);
    m_TimeSeclet_Day->setText(QString(QObject::tr("Day")));
    m_TimeSeclet_Day->setNum(16);
    m_TimeSeclet_Hour = new TimeSelect(m_Parent);
    m_TimeSeclet_Hour->setText(QString(QObject::tr("Hour")));
    m_TimeSeclet_Hour->setNum(10);
    m_TimeSeclet_Minute = new TimeSelect(m_Parent);
    m_TimeSeclet_Minute->setText(QString(QObject::tr("Minute")));
    m_TimeSeclet_Minute->setNum(10);

    int fontPointSize(25 * g_Widget->widthScalabilityFactor());
    m_OKBtn = new BmpButton(m_Parent);
    m_OKBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TimeSelectOKNormal"));
    m_OKBtn->setPressBmpPath(QString(":/Images/Resources/Images/TimeSelectOKPress"));
    m_OKBtn->show();
    m_OKText = new TextWidget(m_OKBtn);
    m_OKText->setAlignmentFlag(Qt::AlignCenter);
    m_OKText->setLanguageType(TextWidget::T_NoTranslate);
    m_OKText->setFontPointSize(fontPointSize);
    m_OKText->setText(QString(QObject::tr("OK")));
}

void DateTimeWidgetPrivate::connectAllSlots(){
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_OKBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(OkBtnRelease()),
                     type);
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
void DateTimeWidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
