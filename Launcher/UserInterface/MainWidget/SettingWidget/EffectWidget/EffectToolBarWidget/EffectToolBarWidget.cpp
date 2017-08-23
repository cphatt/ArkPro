#include "EffectToolBarWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/TextWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>

namespace SourceString {
static const QString Default = QString(QObject::tr("Default"));
static const QString Classical = QString(QObject::tr("Classical"));
static const QString Jazz = QString(QObject::tr("Jazz"));
static const QString Rock = QString(QObject::tr("Rock"));
static const QString Pop = QString(QObject::tr("Pop"));
static const QString Custom = QString(QObject::tr("Custom"));
}

class EffectToolBarWidgetPrivate //构造函数
{
    Q_DISABLE_COPY(EffectToolBarWidgetPrivate)
public:
    explicit EffectToolBarWidgetPrivate(EffectToolBarWidget* parent);
    ~EffectToolBarWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpButton* m_DefaultBtn;
    TextWidget* m_DefaultText;
    BmpButton* m_ClassicalBtn;
    TextWidget* m_ClassicalText;
    BmpButton* m_JazzBtn;
    TextWidget* m_JazzText;
    BmpButton* m_RockBtn;
    TextWidget* m_RockText;
    BmpButton* m_PopBtn;
    TextWidget* m_PopText;
    BmpButton* m_CustomBtn;
    TextWidget* m_CustomText;
private:
    EffectToolBarWidget* m_Parent;
};

EffectToolBarWidget::EffectToolBarWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new EffectToolBarWidgetPrivate(this))
{
}

EffectToolBarWidget::~EffectToolBarWidget()
{
}

void EffectToolBarWidget::resizeEvent(QResizeEvent *event) //控件位置
{
    int width(161);
    int height(108);
    g_Widget->geometryFit(0, 518 - 73, g_Widget->baseWindowWidth() - 278, 108, this);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_DefaultBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_DefaultText);
    g_Widget->geometryFit(445 + (606 - 445 - width) * 0.5 - 278, 0, width, height, m_Private->m_ClassicalBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_ClassicalText);
    g_Widget->geometryFit(613 + (773 - 613 - width) * 0.5 - 278, 0, width, height, m_Private->m_JazzBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_JazzText);
    g_Widget->geometryFit(781 + (942 - 781 - width) * 0.5 - 278, 0, width, height, m_Private->m_RockBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_RockText);
    g_Widget->geometryFit(950 + (1110 - 950 - width) * 0.5 - 278, 0, width, height, m_Private->m_PopBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_PopText);
    g_Widget->geometryFit(1117 + (g_Widget->baseWindowWidth() - 1117 - width) * 0.5 - 278, 0, width, height, m_Private->m_CustomBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_CustomText);
    QWidget::resizeEvent(event);
}

void EffectToolBarWidget::paintEvent(QPaintEvent *event) // ？？？
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

EffectToolBarWidgetPrivate::EffectToolBarWidgetPrivate(EffectToolBarWidget *parent)//初始化
    : m_Parent(parent)
{
    m_DefaultBtn = NULL;
    m_DefaultText = NULL;
    m_ClassicalBtn = NULL;
    m_ClassicalText = NULL;
    m_JazzBtn = NULL;
    m_JazzText = NULL;
    m_RockBtn = NULL;
    m_RockText = NULL;
    m_PopBtn = NULL;
    m_PopText = NULL;
    m_CustomBtn = NULL;
    m_CustomText = NULL;
    initialize();
    connectAllSlots();
}

EffectToolBarWidgetPrivate::~EffectToolBarWidgetPrivate()
{
}

void EffectToolBarWidgetPrivate::initialize()
{
    m_DefaultBtn = new BmpButton(m_Parent);
    m_DefaultBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_DefaultBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_DefaultBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_DefaultText = new TextWidget(m_DefaultBtn);
    m_DefaultText->setText(SourceString::Default);
    int fontPointSize(20 * g_Widget->widthScalabilityFactor());
    m_DefaultText->setFontPointSize(fontPointSize);
    m_ClassicalBtn = new BmpButton(m_Parent);
    m_ClassicalBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ClassicalBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_ClassicalBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_ClassicalText = new TextWidget(m_ClassicalBtn);
    m_ClassicalText->setText(SourceString::Classical);
    m_ClassicalText->setFontPointSize(fontPointSize);
    m_JazzBtn = new BmpButton(m_Parent);
    m_JazzBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_JazzBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_JazzBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_JazzText = new TextWidget(m_JazzBtn);
    m_JazzText->setText(SourceString::Jazz);
    m_JazzText->setFontPointSize(fontPointSize);
    m_RockBtn = new BmpButton(m_Parent);
    m_RockBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_RockBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_RockBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_RockText = new TextWidget(m_RockBtn);
    m_RockText->setText(SourceString::Rock);
    m_RockText->setFontPointSize(fontPointSize);
    m_PopBtn = new BmpButton(m_Parent);
    m_PopBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_PopBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_PopBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_PopText = new TextWidget(m_PopBtn);
    m_PopText->setText(SourceString::Pop);
    m_PopText->setFontPointSize(fontPointSize);
    m_CustomBtn = new BmpButton(m_Parent);
    m_CustomBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetCustomBtnNormal"));
    m_CustomBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetCustomBtnPress"));
    m_CustomBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetCustomBtnPress"));
    m_CustomText = new TextWidget(m_CustomBtn);
    m_CustomText->setText(SourceString::Custom);
    m_CustomText->setFontPointSize(fontPointSize);
    m_Parent->show();
}

void EffectToolBarWidgetPrivate::connectAllSlots()
{
}
