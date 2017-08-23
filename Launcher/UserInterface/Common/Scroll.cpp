#include "Scroll.h"
#include "BmpWidget.h"
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

class ScrollPrivate
{
    Q_DISABLE_COPY(ScrollPrivate)
public:
    explicit ScrollPrivate(Scroll *parent);
    ~ScrollPrivate();
    void initialize();
    int m_ItemHeight;
    int m_Offset;
    int m_DeltaStart;
private:
    Scroll* m_Parent;
};

Scroll::Scroll(QWidget *parent)
    : QWidget(parent)
    , m_Private(new ScrollPrivate(this))
{
}

Scroll::~Scroll()
{
}

void Scroll::setScrollPercent(const float percent)
{
    m_Private->m_Offset = static_cast<int>(percent * (height() - m_Private->m_ItemHeight));
    update();
}

void Scroll::setItemHeight(const int height)
{
    m_Private->m_ItemHeight = height;
    qDebug() << "Scroll::setItemHeight" << m_Private->m_ItemHeight;
    update();
}

void Scroll::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
}

void Scroll::mousePressEvent(QMouseEvent *event)
{
    if ((event->pos().y() >= m_Private->m_Offset)
            && (event->pos().y() <= (m_Private->m_Offset + m_Private->m_ItemHeight))) {
        m_Private->m_DeltaStart = event->pos().y();
    } else {
        m_Private->m_DeltaStart = -1;
    }
    QWidget::mousePressEvent(event);
}

void Scroll::mouseMoveEvent(QMouseEvent *event)
{
    if (-1 != m_Private->m_DeltaStart) {
        int deltaEnd = event->pos().y() - m_Private->m_DeltaStart;
        m_Private->m_DeltaStart = event->pos().y();
        m_Private->m_Offset += deltaEnd;
        if (m_Private->m_Offset < 0) {
            m_Private->m_Offset = 0;
            if (event->pos().y() < m_Private->m_Offset) {
                m_Private->m_DeltaStart = -1;
            }
        } else if (m_Private->m_Offset > height() - m_Private->m_ItemHeight) {
            m_Private->m_Offset = height() - m_Private->m_ItemHeight;
            if (event->pos().y() >= (m_Private->m_Offset + m_Private->m_ItemHeight)) {
                m_Private->m_DeltaStart = -1;
            }
        }
        emit scrollPersent(static_cast<float>(m_Private->m_Offset) / ((height() - m_Private->m_ItemHeight)));
#ifdef gcc
        update();
#endif
    }
    QWidget::mouseMoveEvent(event);
}

void Scroll::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.fillRect(QRect(0, m_Private->m_Offset, width(), m_Private->m_ItemHeight).adjusted(0, 0, -1, -1), QBrush(QColor(158, 158, 47)));
#endif
    QWidget::paintEvent(event);
}

ScrollPrivate::ScrollPrivate(Scroll *parent)
    : m_Parent(parent)
{
    m_ItemHeight = -1;
    m_Offset = -1;
    m_DeltaStart = -1;
    m_ItemHeight = 94;
    initialize();
}

ScrollPrivate::~ScrollPrivate()
{
}

void ScrollPrivate::initialize()
{
}
