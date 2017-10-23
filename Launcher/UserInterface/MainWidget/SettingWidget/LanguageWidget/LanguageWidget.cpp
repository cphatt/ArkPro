#include "LanguageWidget.h"
#include "AutoConnect.h"
#include "UserInterface/Common/BmpButton.h"
#include "UserInterface/Common/TextWidget.h"
#include "BusinessLogic/Setting/Setting.h"
#include "UserInterface/Common/BmpWidget.h"
#include "ArkApplication.h"
#include <QDebug>
#include <QPainter>

namespace SourceString {
static const QString English = QString(QObject::tr("English"));
static const QString Chinese = QString(QObject::tr("Chinese"));
static const QString Japaness = QString(QObject::tr("Japaness"));
static const QString Korean = QString(QObject::tr("Korean"));
static const QString Spanish = QString(QObject::tr("Spanish"));
static const QString Portuguese = QString(QObject::tr("Portuguese"));
static const QString Russian = QString(QObject::tr("Russian"));
static const QString German = QString(QObject::tr("German"));
static const QString French = QString(QObject::tr("French"));
}

class LanguageWidgetPrivate
{
    Q_DISABLE_COPY(LanguageWidgetPrivate)
public:
    explicit LanguageWidgetPrivate(LanguageWidget* parent);
    ~LanguageWidgetPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background;
    BmpButton* m_EnglishBtn;
    TextWidget* m_EnglishText;
    BmpButton* m_ChineseBtn;
    TextWidget* m_ChineseText;
    BmpButton* m_JapanessBtn;
    TextWidget* m_JapanessText;
    BmpButton* m_KoreanBtn;
    TextWidget* m_KoreanText;
    BmpButton* m_SpanishBtn;
    TextWidget* m_SpanishText;
    BmpButton* m_PortugueseBtn;
    TextWidget* m_PortugueseText;
    BmpButton* m_RussianBtn;
    TextWidget* m_RussianText;
    BmpButton* m_GermanBtn;
    TextWidget* m_GermanText;
    BmpButton* m_FrenchBtn;
    TextWidget* m_FrenchText;
private:
    LanguageWidget* m_Parent;
};

LanguageWidget::LanguageWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new LanguageWidgetPrivate(this))
{
}

LanguageWidget::~LanguageWidget()
{
}

void LanguageWidget::showEvent(QShowEvent *event)
{
    g_Widget->setWidgetType(Widget::T_SettingLanguage, WidgetStatus::Show);
    QWidget::showEvent(event);
}

void LanguageWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(174, 64, 625, 355, this);
    g_Widget->geometryFit(0, 0, 625, 355, m_Private->m_Background);
    int width(102);
    int height(71);
    g_Widget->geometryFit(253 - 174, 101 - 64, width, height, m_Private->m_EnglishBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_EnglishText);
    g_Widget->geometryFit(435 - 174, 101 - 64, width, height, m_Private->m_ChineseBtn);
    g_Widget->geometryFit(0, 0, width, height, m_Private->m_ChineseText);
//    g_Widget->geometryFit(709, 57, width, height, m_Private->m_JapanessBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_JapanessText);
//    g_Widget->geometryFit(129, 222, width, height, m_Private->m_KoreanBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_KoreanText);
//    g_Widget->geometryFit(419, 222, width, height, m_Private->m_SpanishBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_SpanishText);
//    g_Widget->geometryFit(709, 222, width, height, m_Private->m_PortugueseBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_PortugueseText);
//    g_Widget->geometryFit(129, 387, width, height, m_Private->m_RussianBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_RussianText);
//    g_Widget->geometryFit(419, 387, width, height, m_Private->m_GermanBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_GermanText);
//    g_Widget->geometryFit(709, 387, width, height, m_Private->m_FrenchBtn);
//    g_Widget->geometryFit(0, 0, width, height, m_Private->m_FrenchText);
    QWidget::resizeEvent(event);
}

void LanguageWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void LanguageWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    qDebug() << "LanguageWidget::ontWidgetTypeChange" << type << status;
    switch (type) {
    case Widget::T_SettingLanguage: {
        if (WidgetStatus::RequestShow == status) {
            g_Widget->setWidgetType(Widget::T_SettingLanguage, WidgetStatus::Show);
        } else if (WidgetStatus::Show == status) {
            m_Private->m_Background->setVisible(true);
            m_Private->m_EnglishBtn->setVisible(true);
            m_Private->m_EnglishText->setVisible(true);
            m_Private->m_ChineseBtn->setVisible(true);
            m_Private->m_ChineseText->setVisible(true);
            m_Private->m_JapanessBtn->setVisible(true);
            m_Private->m_JapanessText->setVisible(true);
            m_Private->m_KoreanBtn->setVisible(true);
            m_Private->m_KoreanText->setVisible(true);
            m_Private->m_SpanishBtn->setVisible(true);
            m_Private->m_SpanishText->setVisible(true);
            m_Private->m_PortugueseBtn->setVisible(true);
            m_Private->m_PortugueseText->setVisible(true);
            m_Private->m_RussianBtn->setVisible(true);
            m_Private->m_RussianText->setVisible(true);
            m_Private->m_GermanBtn->setVisible(true);
            m_Private->m_GermanText->setVisible(true);
            m_Private->m_FrenchBtn->setVisible(true);
            m_Private->m_FrenchText->setVisible(true);
            setVisible(true);
        }
        break;
    }
    case Widget::T_SettingGeneral:
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

void LanguageWidget::onDateTimeChange(const QString &date, const QString &time)
{
}

void LanguageWidget::onLanguageTranslateChange(const LanguageType language)
{
    m_Private->m_EnglishBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_ChineseBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_JapanessBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_KoreanBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_SpanishBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_PortugueseBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_RussianBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_GermanBtn->setStatus(BmpButton::B_Normal);
    m_Private->m_FrenchBtn->setStatus(BmpButton::B_Normal);
    switch (language) {
    case LT_English: {
        m_Private->m_EnglishBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Chinese: {
        m_Private->m_ChineseBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Japaness: {
        m_Private->m_JapanessBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Korean: {
        m_Private->m_KoreanBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Spanish: {
        m_Private->m_SpanishBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Portuguese: {
        m_Private->m_PortugueseBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_Russian: {
        m_Private->m_RussianBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_German: {
        m_Private->m_GermanBtn->setStatus(BmpButton::B_Check);
        break;
    }
    case LT_French: {
        m_Private->m_FrenchBtn->setStatus(BmpButton::B_Check);
        break;
    }
    default: {
        break;
    }
    }
}

void LanguageWidget::onBrightnessChange(const int value)
{
}

void LanguageWidget::onContrastChange(const int value)
{
}

void LanguageWidget::onHueChange(const int value)
{
}

void LanguageWidget::onVolumeChange(const int type, const int value)
{
}

void LanguageWidget::onEffectChange(const int type, const int hight, const int middle, const int low)
{
}

void LanguageWidget::onTest()
{
    qDebug() << "LanguageWidget::onTest()";
}
void LanguageWidget::onTest1()
{
    qDebug() << "LanguageWidget::onTest1()";
}
void LanguageWidget::onToolButtonRelease()
{
    qDebug() << __FUNCTION__;
    if (sender() == m_Private->m_EnglishBtn) {
        g_Setting->setLanguage(LT_English);
    } else if (sender() == m_Private->m_ChineseBtn) {
        g_Setting->setLanguage(LT_Chinese);
    } else if (sender() == m_Private->m_JapanessBtn) {
        g_Setting->setLanguage(LT_Japaness);
    } else if (sender() == m_Private->m_KoreanBtn) {
        g_Setting->setLanguage(LT_Korean);
    } else if (sender() == m_Private->m_SpanishBtn) {
        g_Setting->setLanguage(LT_Spanish);
    } else if (sender() == m_Private->m_PortugueseBtn) {
        g_Setting->setLanguage(LT_Portuguese);
    } else if (sender() == m_Private->m_RussianBtn) {
        g_Setting->setLanguage(LT_Russian);
    } else if (sender() == m_Private->m_GermanBtn) {
        g_Setting->setLanguage(LT_German);
    } else if (sender() == m_Private->m_FrenchBtn) {
        g_Setting->setLanguage(LT_French);
    }
}

LanguageWidgetPrivate::LanguageWidgetPrivate(LanguageWidget *parent)
    : m_Parent(parent)
{
    m_ChineseBtn = NULL;
    m_ChineseText = NULL;
    m_EnglishBtn = NULL;
    m_EnglishText = NULL;
    m_JapanessBtn = NULL;
    m_JapanessText = NULL;
    m_KoreanBtn = NULL;
    m_KoreanText = NULL;
    m_SpanishBtn = NULL;
    m_SpanishText = NULL;
    m_PortugueseBtn = NULL;
    m_PortugueseText = NULL;
    m_RussianBtn = NULL;
    m_RussianText = NULL;
    m_GermanBtn = NULL;
    m_GermanText = NULL;
    m_FrenchBtn = NULL;
    m_FrenchText = NULL;
    initialize();
    connectAllSlots();
}

LanguageWidgetPrivate::~LanguageWidgetPrivate()
{
}

void LanguageWidgetPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->hide();
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/LanguageSoundWidgetBackground"));
    m_EnglishBtn = new BmpButton(m_Parent);
    m_EnglishBtn->hide();
    m_EnglishBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_EnglishBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_EnglishBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_EnglishText = new TextWidget(m_EnglishBtn);
    m_EnglishText->hide();
    m_EnglishText->setText(SourceString::English);
    m_ChineseBtn = new BmpButton(m_Parent);
    m_ChineseBtn->hide();
    m_ChineseBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ChineseBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
    m_ChineseBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_ChineseText = new TextWidget(m_ChineseBtn);
    m_ChineseText->hide();
    m_ChineseText->setText(SourceString::Chinese);
    m_JapanessBtn = new BmpButton(m_Parent);
//    m_JapanessBtn->hide();
//    m_JapanessBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_JapanessBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_JapanessBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_JapanessText = new TextWidget(m_JapanessBtn);
//    m_JapanessText->hide();
//    m_JapanessText->setText(SourceString::Japaness);
    m_KoreanBtn = new BmpButton(m_Parent);
//    m_KoreanBtn->hide();
//    m_KoreanBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_KoreanBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_KoreanBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_KoreanText = new TextWidget(m_KoreanBtn);
//    m_KoreanText->hide();
//    m_KoreanText->setText(SourceString::Korean);
    m_SpanishBtn = new BmpButton(m_Parent);
//    m_SpanishBtn->hide();
//    m_SpanishBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_SpanishBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_SpanishBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_SpanishText = new TextWidget(m_SpanishBtn);
//    m_SpanishText->hide();
//    m_SpanishText->setText(SourceString::Spanish);
    m_PortugueseBtn = new BmpButton(m_Parent);
//    m_PortugueseBtn->hide();
//    m_PortugueseBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_PortugueseBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_PortugueseBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_PortugueseText = new TextWidget(m_PortugueseBtn);
//    m_PortugueseText->hide();
//    m_PortugueseText->setText(SourceString::Portuguese);
    m_RussianBtn = new BmpButton(m_Parent);
//    m_RussianBtn->hide();
//    m_RussianBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_RussianBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_RussianBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_RussianText = new TextWidget(m_RussianBtn);
//    m_RussianText->hide();
//    m_RussianText->setText(SourceString::Russian);
    m_GermanBtn = new BmpButton(m_Parent);
//    m_GermanBtn->hide();
//    m_GermanBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_GermanBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_GermanBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_GermanText = new TextWidget(m_GermanBtn);
//    m_GermanText->hide();
//    m_GermanText->setText(SourceString::German);
    m_FrenchBtn = new BmpButton(m_Parent);
//    m_FrenchBtn->hide();
//    m_FrenchBtn->setNormalBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_FrenchBtn->setPressBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnNormal"));
//    m_FrenchBtn->setCheckBmpPath(QString(":/Images/Resources/Images/EffectWidgetToolBtnPress"));
    m_FrenchText = new TextWidget(m_FrenchBtn);
//    m_FrenchText->hide();
//    m_FrenchText->setText(SourceString::French);
//    m_Parent->setVisible(false);
}

void LanguageWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Setting, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_EnglishBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
    QObject::connect(m_ChineseBtn, SIGNAL(bmpButtonRelease()),
                     m_Parent,     SLOT(onToolButtonRelease()),
                     type);
//    QObject::connect(m_JapanessBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,      SLOT(onToolButtonRelease()),
//                     type);
//    QObject::connect(m_KoreanBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,    SLOT(onToolButtonRelease()),
//                     type);
//    QObject::connect(m_SpanishBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,     SLOT(onToolButtonRelease()),
//                     type);
//    QObject::connect(m_PortugueseBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,        SLOT(onToolButtonRelease()),
//                     type);
//    QObject::connect(m_RussianBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,     SLOT(onToolButtonRelease()),
//                     type);
//    QObject::connect(m_GermanBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,    SLOT(onToolButtonRelease()),
//                     type);
//    QObject::connect(m_FrenchBtn, SIGNAL(bmpButtonRelease()),
//                     m_Parent,    SLOT(onToolButtonRelease()),
//                     type);
}
