#include "TimeSelect.h"
#include "UserInterface/Common/BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/Slider.h"
#include "AutoConnect.h"
#include <QDebug>

class TimeSelectPrivate
{
    Q_DISABLE_COPY(TimeSelectPrivate)
public:
    explicit TimeSelectPrivate(TimeSelect* parent);
    ~TimeSelectPrivate();
    void initialize();
    void connectAllSlots();
    BmpButton* m_MinusBtn;
    BmpButton* m_PlusBtn;

    BmpWidget* m_Text;
    BmpWidget* m_Num;

    TextWidget *T_Text;
    TextWidget *T_Num;
    void setNum(int num){
        data = num;
    };
    int getNum(){
        return data;
    }
private:
    TimeSelect* m_Parent;
    int data;
};

TimeSelect::TimeSelect(QWidget* parent)
    : QWidget(parent)
    , m_Private(new TimeSelectPrivate(this))
{
}

TimeSelect::~TimeSelect()
{
}

void TimeSelect::setNum(const int data){
    m_Private->setNum(data);
    m_Private->T_Num->setText(QString::number(data, 10));
}
int  TimeSelect::getNum(){
    return m_Private->getNum();
}

void TimeSelect::setText(const QString text){
    m_Private->T_Text->setText(text);
}

void TimeSelect::resizeEvent(QResizeEvent *event)
{

//    g_Widget->geometryFit(0, 0, 100, 50, m_Private->m_Text);
//    g_Widget->geometryFit(0, 50, 100, 70, m_Private->m_PlusBtn);
//    g_Widget->geometryFit(0, 120, 100, 50, m_Private->m_Num);
//    g_Widget->geometryFit(0, 170, 100, 70, m_Private->m_MinusBtn);

    QWidget::resizeEvent(event);
}

void TimeSelect::minusBtnRelease(){
    m_Private->setNum(m_Private->getNum() - 1);
    m_Private->T_Num->setText(QString::number(m_Private->getNum(), 10));
}

void TimeSelect::plusBtnRelease(){
    m_Private->setNum(m_Private->getNum() + 1);
    m_Private->T_Num->setText(QString::number(m_Private->getNum(), 10));
}

TimeSelectPrivate::TimeSelectPrivate(TimeSelect *parent)
    : m_Parent(parent)
{
    m_MinusBtn = NULL;
    m_PlusBtn = NULL;
    m_Text = NULL;
    m_Num = NULL;
    T_Text = NULL;
    T_Num = NULL;
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
}

TimeSelectPrivate::~TimeSelectPrivate()
{
}

void TimeSelectPrivate::initialize()
{
    m_MinusBtn = new BmpButton(m_Parent);
    m_MinusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TimeSelectMinusNormal"));
    m_MinusBtn->setPressBmpPath(QString(":/Images/Resources/Images/TimeSelectMinusPress"));
    m_MinusBtn->show();
    m_PlusBtn = new BmpButton(m_Parent);
    m_PlusBtn->setNormalBmpPath(QString(":/Images/Resources/Images/TimeSelectPlusNormal"));
    m_PlusBtn->setPressBmpPath(QString(":/Images/Resources/Images/TimeSelectPlusPress"));
    m_PlusBtn->show();

    int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    m_Text = new BmpWidget(m_Parent);
    m_Text->setBackgroundBmpPath(QString(":/Images/Resources/Images/TimeSelectTextWidget"));
    m_Text->show();

    T_Text = new TextWidget(m_Text);
    T_Text->setAlignmentFlag(Qt::AlignCenter);
    T_Text->setLanguageType(TextWidget::T_NoTranslate);
    T_Text->setFontPointSize(fontPointSize);
    T_Text->setText("a");

    m_Num = new BmpWidget(m_Parent);
    m_Num->setBackgroundBmpPath(QString(":/Images/Resources/Images/TimeSelectNumberWidget"));
    m_Num->show();

    T_Num = new TextWidget(m_Num);
    T_Num->setAlignmentFlag(Qt::AlignCenter);
    T_Num->setLanguageType(TextWidget::T_NoTranslate);
    T_Num->setFontPointSize(fontPointSize);
    T_Num->setText("1");

    m_Text->setGeometry(0, 0, 100, 50);
    T_Text->setGeometry(25, 10, 50, 30);
    m_PlusBtn->setGeometry(0, 50, 100, 70);
    m_Num->setGeometry(0, 120, 100, 50);
    T_Num->setGeometry(20, 10, 60, 30);
    m_MinusBtn->setGeometry(0, 170, 100, 70);

}

void TimeSelectPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_MinusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,   SLOT(minusBtnRelease()),
                     type);

    QObject::connect(m_PlusBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,  SLOT(plusBtnRelease()),
                     type);
}
