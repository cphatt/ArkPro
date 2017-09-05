#include "FieldWidget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/BmpWidget.h"
#include "UserInterface/Common/TextWidget.h"
#include "UserInterface/Common/BmpButton.h"
#include <QPainter>
#include <QDebug>
#include <QtXml>
#include <QString>
#include <QTimer>

#define PATH "/home/user/Version.xml"

namespace SourceString {
static const QString MAN_Pitch = QString(QObject::tr("MAN:"));
static const QString BSP_Pitch = QString(QObject::tr("BSP:"));
static const QString APP_Pitch = QString(QObject::tr("APP:"));
}

class FieldWidgetPrivate
{
    Q_DISABLE_COPY(FieldWidgetPrivate)
public:
    explicit FieldWidgetPrivate(FieldWidget* parent);
    ~FieldWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void initFile();
    TextWidget* MANPitch;
    TextWidget* BSPPitch;
    TextWidget* APPPitch;
    TextWidget* MANText;
    TextWidget* BSPText;
    TextWidget* APPText;
    BmpButton* mcuUpdateBtn;
    TextWidget* mcuUpdateText;
    BmpButton* resetBtn;
    TextWidget* resetText;
    BmpWidget* m_Background;
    QString value[3];
    QTimer* m_Timer;


private:
    FieldWidget* m_Parent;
};

FieldWidget::FieldWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new FieldWidgetPrivate(this))
{
}

FieldWidget::~FieldWidget()
{
}
void FieldWidget::onTimeout()
{
    qDebug() << "-----------------------------";
    //将字体重新设置

    m_Private->MANText->setText(StringLeftMove(m_Private->MANText->getText()));
    m_Private->m_Timer->start();
}

QString FieldWidget::StringLeftMove(const QString string){
    QByteArray ba = string.toLatin1();
    char *text = ba.data();
    text++;
  //  QDebug() <<text << "  ";
    return QString(QLatin1String(text));
}

void FieldWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingField, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void FieldWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(174, 64, 625, 355, this);
    g_Widget->geometryFit(0, 0, 625, 355, m_Private->m_Background);
    //g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth() - 278, 505 - 73, m_Private->m_Background);
    int width(80);
    int height(80);
    g_Widget->geometryFit(174 - 165, 10, width, height, m_Private->MANPitch);
    g_Widget->geometryFit(174 - 165, 104, width, height, m_Private->BSPPitch);
    g_Widget->geometryFit(174 - 165, 194, width, height, m_Private->APPPitch);
    width = 500;
    height = 80;
    g_Widget->geometryFit(174 - 165 + 80, 10, width, height, m_Private->MANText);
    g_Widget->geometryFit(174 - 165 + 80, 104, width, height, m_Private->BSPText);
    g_Widget->geometryFit(174 - 165 + 80, 194, width, height, m_Private->APPText);
    width = 161;
    height = 108;
    g_Widget->geometryFit(200, this->height() - 100, width, height, m_Private->mcuUpdateBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->mcuUpdateText);
    g_Widget->geometryFit(400,this->height() - 100, width, height, m_Private->resetBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->resetText);
    QWidget::resizeEvent(event);
}

void FieldWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void FieldWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    switch (type) {
    case Widget::T_SettingField: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingField, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            setVisible(true);

        }
        break;
    }
    case Widget::T_SettingLanguage:
    case Widget::T_SettingGeneral:
    case Widget::T_SettingEffect: {
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

FieldWidgetPrivate::FieldWidgetPrivate(FieldWidget *parent)
    : m_Parent(parent)
{
    m_Background = NULL;
    MANText = NULL;
    BSPText = NULL;
    APPText = NULL;
    MANPitch = NULL;
    APPPitch = NULL;
    BSPPitch = NULL;
    mcuUpdateBtn = NULL;
    mcuUpdateText = NULL;
    resetBtn = NULL;
    resetText = NULL;
    m_Timer = NULL;
    initialize();
    connectAllSlots();
   // m_Timer->start();
}

FieldWidgetPrivate::~FieldWidgetPrivate()
{
}

void FieldWidgetPrivate::initialize()
{
    initFile();
    m_Background = new BmpWidget(m_Parent);
    m_Background->show();
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LanguageSoundWidgetBackground"));
    MANText = new TextWidget(m_Parent);
    MANText->setLanguageType(TextWidget::T_NoTranslate);
    int fontPointSize(16 * g_Widget->widthScalabilityFactor());
    MANText->setFontPointSize(fontPointSize);
    MANText->show();
    BSPText = new TextWidget(m_Parent);
    BSPText->setLanguageType(TextWidget::T_NoTranslate);
    BSPText->setFontPointSize(fontPointSize);
    BSPText->show();
    APPText = new TextWidget(m_Parent);
    APPText->setLanguageType(TextWidget::T_NoTranslate);
    APPText->setFontPointSize(fontPointSize);
    APPText->show();
    MANPitch = new TextWidget(m_Parent);
    MANPitch->setLanguageType(TextWidget::T_NoTranslate);
    MANPitch->setFontPointSize(fontPointSize);
    MANPitch->show();
    BSPPitch = new TextWidget(m_Parent);
    BSPPitch->setLanguageType(TextWidget::T_NoTranslate);
    BSPPitch->setFontPointSize(fontPointSize);
    BSPPitch->show();
    APPPitch = new TextWidget(m_Parent);
    APPPitch->setLanguageType(TextWidget::T_NoTranslate);
    APPPitch->setFontPointSize(fontPointSize);
    APPPitch->show();
    MANPitch->setText(QString(QObject::tr(SourceString::MAN_Pitch.toLocal8Bit().constData())) + QString(" ") );
    BSPPitch->setText(QString(QObject::tr(SourceString::BSP_Pitch.toLocal8Bit().constData())) + QString(" "));
    APPPitch->setText(QString(QObject::tr(SourceString::APP_Pitch.toLocal8Bit().constData())) + QString(" "));
    MANText->setText(value[0]);
    BSPText->setText(value[1]);
    APPText->setText(value[2]);
    mcuUpdateBtn = new BmpButton(m_Parent);
    mcuUpdateBtn->show();
    mcuUpdateBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    mcuUpdateBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    mcuUpdateBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    mcuUpdateText = new TextWidget(mcuUpdateBtn);
    mcuUpdateText->show();
    mcuUpdateText->setText(QString("update"));
    mcuUpdateText->setFontPointSize(fontPointSize);
    resetBtn = new BmpButton(m_Parent);
    resetBtn->show();
    resetBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    resetBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    resetBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    resetText = new TextWidget(resetBtn);
    resetText->show();
    resetText->setText(QString("reset"));
    resetText->setFontPointSize(fontPointSize);
    m_Parent->setVisible(false);

    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(3000);

}

void FieldWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
//    QObject::connect(m_Timer,  SIGNAL(timeout()),
//                     m_Parent, SLOT(onTimeout()),
//                     type);
}

void FieldWidgetPrivate::initFile(){

    QDomDocument doc;

#ifdef gcc
    QFile file("/home/user/Version1.xml");
#else
    QFile file("/usr/bin/Version.xml");
#endif

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<" open Verson.xml Fail";
        return;
    }

    if(!doc.setContent(&file)){
         qDebug()<<" add Verson.xml Fail";
        file.close();
        return;
    }

    file.close();

    QDomNode firstNode = doc.firstChild();
    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();
    int i= 0;
    while(!n.isNull()){
        if(n.isElement()){
            QDomElement e = n.toElement();

            //返回元素标记和ID属性的值
            qDebug()<<"11111111111111111"<<qPrintable(e.tagName()) << qPrintable(e.attribute("id"));
            QDomNodeList list = e.childNodes();
            QDomNode node = list.at(0);
            if(node.isElement())
                value[i++] = node.toElement().text();
        }
        n = n.nextSibling();
    }

}
