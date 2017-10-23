#include "MessageBox.h"
#include "Utility.h"
#include "BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QTimer>
#include <QDebug>
#include <QFont>
#include <QSvgRenderer>

class MessageBoxPrivate
{
    Q_DISABLE_COPY(MessageBoxPrivate)
public:
    explicit MessageBoxPrivate(MessageBox *parent);
    ~MessageBoxPrivate();
    void initialize();
    void connectAllSlots();
    QString m_Text;
    QTimer* m_Timer;
    QScopedPointer<QSvgRenderer> m_BackgroundSvg;
    QFont m_Font;
    bool m_AutoHide;
private:
    MessageBox *m_Parent;
};

MessageBox::MessageBox(QWidget *parent)
    : QWidget(parent)
    , m_Private(new MessageBoxPrivate(this))
{
}

MessageBox::~MessageBox()
{
}

void MessageBox::setText(const QString &text)
{
    if (text != m_Private->m_Text) {
        m_Private->m_Text = text;
        update();
    }
}

void MessageBox::setAutoHide(const bool flag)
{
    if (flag != m_Private->m_AutoHide) {
        m_Private->m_AutoHide = flag;
    }
}

void MessageBox::setFontPointSize(const int pointSize)
{
    m_Private->m_Font.setPointSize(pointSize);
    update();
}

void MessageBox::showEvent(QShowEvent *event)
{
    m_Private->m_Timer->start();
    emit messageWidgetChange(MessageBox::T_Show);
    QWidget::showEvent(event);
}

void MessageBox::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void MessageBox::hideEvent(QHideEvent *event)
{
    if (isVisible()) {
        if (m_Private->m_Timer->isActive()) {
            m_Private->m_Timer->stop();
        }
        emit messageWidgetChange(MessageBox::T_Hide);
    }
    QWidget::hideEvent(event);
}

void MessageBox::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(0, 0, 1, 127));
    if (!m_Private->m_BackgroundSvg.isNull()) {
        m_Private->m_BackgroundSvg->render(&painter, QRect((width() - m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor() * 800 / 1280) / 2,
                                                           (height() - m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) ,
                                                           m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor() * 800 / 1280,
                                                           m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor() * 480 / 720)) ;
    }
    if (!m_Private->m_Text.isEmpty()) {
        painter.setFont(m_Private->m_Font);
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
    }
    QWidget::paintEvent(event);
}

void MessageBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_Private->m_AutoHide && isVisible()) {
        setVisible(false);
    }
    QWidget::mouseReleaseEvent(event);
}

MessageBoxPrivate::MessageBoxPrivate(MessageBox *parent)
    : m_Parent(parent)
{
    m_Text.clear();
    m_Timer = NULL;
    m_AutoHide = true;
    m_BackgroundSvg.reset(NULL);
    initialize();
    connectAllSlots();
}

MessageBoxPrivate::~MessageBoxPrivate()
{
}

void MessageBoxPrivate::initialize()
{
    m_Text.clear();
    m_Timer = new QTimer(m_Parent);
    m_Timer->setSingleShot(true);
    m_Timer->setInterval(3000);
    m_BackgroundSvg.reset(new QSvgRenderer(QString(":/Images/Resources/Images/MessageBackground.svg"), m_Parent));
}

void MessageBoxPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeOut()),
                     type);
}

void MessageBox::onTimeOut()
{
    if (m_Private->m_AutoHide && isVisible()) {
        setVisible(false);
    }
    emit messageShowTimeout();
}
