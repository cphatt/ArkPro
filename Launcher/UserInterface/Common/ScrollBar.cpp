#include "ScrollBar.h"
#include "Scroll.h"
#include "BmpWidget.h"
#include <QPainter>
#include <QDebug>
#include <QScopedPointer>

class ScrollBarPrivate
{
    Q_DISABLE_COPY(ScrollBarPrivate)
public:
    explicit ScrollBarPrivate(ScrollBar *parent);
    ~ScrollBarPrivate();
    void initialize();
    void connectAllSlots();
    BmpWidget* m_Background;
    Scroll* m_Scroll;
private:
    ScrollBar *m_Parent;
};

ScrollBar::ScrollBar(QWidget *parent)
    : QWidget(parent)
    , m_Private(new ScrollBarPrivate(this))
{
}

ScrollBar::~ScrollBar()
{
}

void ScrollBar::setScrollPercent(const float percent)
{
    m_Private->m_Scroll->setScrollPercent(percent);
}

void ScrollBar::setItemHeight(const int height)
{
    m_Private->m_Scroll->setItemHeight(height);
}

void ScrollBar::resizeEvent(QResizeEvent *event)
{
    m_Private->m_Background->setGeometry(0, 0, width(), height());
    if (NULL != m_Private->m_Scroll) {
        m_Private->m_Scroll->setGeometry(0, 0, width(), height());
    }
    QWidget::resizeEvent(event);
}

void ScrollBar::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
}

void ScrollBar::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);
}

void ScrollBar::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
}

ScrollBarPrivate::ScrollBarPrivate(ScrollBar *parent)
    : m_Parent(parent)
{
    m_Scroll = NULL;
    initialize();
    connectAllSlots();
}

ScrollBarPrivate::~ScrollBarPrivate()
{
}

void ScrollBarPrivate::initialize()
{
    m_Background = new BmpWidget(m_Parent);
    m_Background->setBackgroundBmpPath(QString(":/Images/Resources/Images/ScrollBackground"));
    m_Background->setVisible(true);
    m_Scroll = new Scroll(m_Parent);
    m_Scroll->show();
}

void ScrollBarPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Scroll, SIGNAL(scrollPersent(const float)),
                     m_Parent, SIGNAL(scrollPersent(const float)),
                     type);
}
