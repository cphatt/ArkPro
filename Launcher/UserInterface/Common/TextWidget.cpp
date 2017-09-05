#include "TextWidget.h"
#include <QPainter>

class TextWidgetPrivate
{
    Q_DISABLE_COPY(TextWidgetPrivate)
public:
    TextWidgetPrivate();
    ~TextWidgetPrivate();
    QString m_Text;
    int m_Flags;
    QFont m_Font;
    TextWidget::Type m_LanguageType;
};

TextWidget::TextWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new TextWidgetPrivate())
{
}

TextWidget::~TextWidget()
{
}

void TextWidget::setText(const QString &text)
{
    m_Private->m_Text = text;
    update();
}

QString TextWidget::TextWidget::getText()
{
    return m_Private->m_Text;
}

void TextWidget::setLanguageType(const TextWidget::Type type)
{
    m_Private->m_LanguageType = type;
    update();
}

void TextWidget::setAlignmentFlag(const int flags)
{
    m_Private->m_Flags = flags;
    update();
}

void TextWidget::setFontPointSize(const int pointSize)
{
    m_Private->m_Font.setPointSize(pointSize);
    update();
}

void TextWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
#ifdef gcc
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    if (!m_Private->m_Text.isEmpty()) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::white));
        painter.setFont(m_Private->m_Font);
        if (TextWidget::T_Translate == m_Private->m_LanguageType) {
            painter.drawText(rect(), m_Private->m_Flags, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
        } else {
            painter.drawText(rect(), m_Private->m_Flags, m_Private->m_Text);
        }
    }
    QWidget::paintEvent(event);
}

TextWidgetPrivate::TextWidgetPrivate()
{
    m_Flags = Qt::AlignCenter;
    m_LanguageType = TextWidget::T_Translate;
}

TextWidgetPrivate::~TextWidgetPrivate()
{
}
