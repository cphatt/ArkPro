#include "Slider.h"
#include "BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QSvgRenderer>
#include <QPixmap>
#include <QScopedPointer>
#include <QFile>

class SliderPrivate
{
    Q_DISABLE_COPY(SliderPrivate)
public:
    explicit SliderPrivate(Slider* parent);
    ~SliderPrivate();
    QRect m_TickMarks;
    int m_TickMarksMillesimal;
    bool m_IsTracking;
    QScopedPointer<QPixmap> m_BackgroundPixmap;
    QScopedPointer<QSvgRenderer> m_BackgroundSvg;
    QScopedPointer<QPixmap> m_TickMarksPixmap;
    QScopedPointer<QSvgRenderer> m_TickMarksPSvg;
    int m_Minimum;
    int m_Maximum;
    bool m_AllowPress;
    bool m_AllowMove;
private:
    Slider* m_Parent;
};

Slider::Slider(QWidget *parent)
    : QWidget(parent)
    , m_Private(new SliderPrivate(this))
{
}

Slider::~Slider()
{
}

void Slider::setAllowPress(const bool flag)
{
    m_Private->m_AllowPress = flag;
    if (!m_Private->m_AllowPress) {
        m_Private->m_AllowMove = m_Private->m_AllowPress;
    }
}

void Slider::setAllowMove(const bool flag)
{
    if (!m_Private->m_AllowPress) {
        m_Private->m_AllowMove = m_Private->m_AllowPress;
    } else {
        m_Private->m_AllowMove = flag;
    }
}

void Slider::setBackgroundBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_BackgroundPixmap.reset(new QPixmap(path + QString(".png")));
    } else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_BackgroundSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    } else {
        if (!m_Private->m_BackgroundPixmap.isNull()) {
            m_Private->m_BackgroundPixmap.reset(NULL);
        } if (!m_Private->m_BackgroundSvg.isNull()) {
            m_Private->m_BackgroundSvg.reset(NULL);
        }
    }
    update();
}

void Slider::setTickMarkTickMarkslBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_TickMarksPixmap.reset(new QPixmap(path + QString(".png")));
    } else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_TickMarksPSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    } else {
        if (!m_Private->m_TickMarksPixmap.isNull()) {
            m_Private->m_TickMarksPixmap.reset(NULL);
        } if (!m_Private->m_TickMarksPSvg.isNull()) {
            m_Private->m_TickMarksPSvg.reset(NULL);
        }
    }
    update();
}

void Slider::setTickMarksSize(const QSize &size)
{
    m_Private->m_TickMarks.setSize(size);
    update();
}

void Slider::setTickMarksMillesimal(const int millesimal)
{
    int value(millesimal);
    if (millesimal < 0) {
        value = 0;
    } else if (millesimal > 1000) {
        value = 1000;
    }
    if (!m_Private->m_IsTracking) {
        m_Private->m_TickMarksMillesimal = value;
        update();
    }
}

void Slider::setRange(const int minimum, const int maxmum)
{

}

void Slider::resizeEvent(QResizeEvent *event)
{
    m_Private->m_TickMarks.setHeight(height());
    QWidget::resizeEvent(event);
}

void Slider::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
#ifdef gcc
    painter.setPen(Qt::white);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    m_Private->m_TickMarks.moveLeft((m_Private->m_TickMarksMillesimal * (width() - m_Private->m_TickMarks.width())) / 1000);
    if (!m_Private->m_BackgroundPixmap.isNull()) {
        QPainter painter(this);
        painter.drawPixmap((width() - m_Private->m_BackgroundPixmap->width()) / 2, (height() - m_Private->m_BackgroundPixmap->height()) / 2, *m_Private->m_BackgroundPixmap);
    } else if (!m_Private->m_BackgroundSvg.isNull()) {
        m_Private->m_BackgroundSvg->render(&painter, QRect((width() - m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2,
                                                           (height() - m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                           m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                           m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
    if (!m_Private->m_TickMarksPixmap.isNull()) {
        painter.drawPixmap((m_Private->m_TickMarks.width() - m_Private->m_BackgroundPixmap->width()) / 2 + m_Private->m_TickMarks.x(),
                           (m_Private->m_TickMarks.height() - m_Private->m_BackgroundPixmap->height()) / 2 + + m_Private->m_TickMarks.y(),
                           *(m_Private->m_BackgroundPixmap.data()));
    } else if (!m_Private->m_TickMarksPSvg.isNull()) {
        m_Private->m_TickMarksPSvg->render(&painter, QRect((m_Private->m_TickMarks.width() - m_Private->m_TickMarksPSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2 + m_Private->m_TickMarks.x(),
                                                           (height() - m_Private->m_TickMarksPSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                           m_Private->m_TickMarksPSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                           m_Private->m_TickMarksPSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
#ifdef gcc
    painter.setPen(Qt::gray);
    painter.drawRect(m_Private->m_TickMarks.adjusted(0, 0, -1, -1));
#endif
    QWidget::paintEvent(event);
}

void Slider::mousePressEvent(QMouseEvent *event)
{
    if (m_Private->m_AllowPress) {
        m_Private->m_IsTracking = true;
        int x = event->pos().x();
        if (x < m_Private->m_TickMarks.width() / 2) {
            x = m_Private->m_TickMarks.width() / 2;
        } else if (x > (width() - m_Private->m_TickMarks.width() / 2)) {
            x = width() - m_Private->m_TickMarks.width() / 2;
        }
        if (m_Private->m_TickMarks.left() != (x - m_Private->m_TickMarks.width() / 2)) {
            m_Private->m_TickMarks.moveLeft(x - m_Private->m_TickMarks.width() / 2);
            update();
        }
        m_Private->m_TickMarksMillesimal = 1000 * m_Private->m_TickMarks.left() / (width() - m_Private->m_TickMarks.width());
        emit tickMarksMillesimalStart(m_Private->m_TickMarksMillesimal);
    }
    QWidget::mousePressEvent(event);
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    if ((m_Private->m_AllowPress)
            && (m_Private->m_AllowMove)) {
        if (m_Private->m_TickMarks.contains(event->pos())) {
            int x = event->pos().x();
            if (x < m_Private->m_TickMarks.width() / 2) {
                x = m_Private->m_TickMarks.width() / 2;
            } else if (x > (width() - m_Private->m_TickMarks.width() / 2)) {
                x = width() - m_Private->m_TickMarks.width() / 2;
            }
            if (m_Private->m_TickMarks.left() != (x - m_Private->m_TickMarks.width() / 2)) {
                m_Private->m_TickMarks.moveLeft(x - m_Private->m_TickMarks.width() / 2);
                update();
            }
        }
        m_Private->m_TickMarksMillesimal = 1000 * m_Private->m_TickMarks.left() / (width() - m_Private->m_TickMarks.width());
        emit tickMarksMillesimalChange(m_Private->m_TickMarksMillesimal);
    }
    QWidget::mouseMoveEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_Private->m_AllowPress) {
        m_Private->m_IsTracking = false;
        m_Private->m_TickMarksMillesimal = 1000 * m_Private->m_TickMarks.left() / (width() - m_Private->m_TickMarks.width());
        emit tickMarksMillesimalEnd(m_Private->m_TickMarksMillesimal);
    }
    QWidget::mouseReleaseEvent(event);
}

SliderPrivate::SliderPrivate(Slider* parent)
    : m_Parent(parent)
{
    m_Minimum = 0;
    m_Maximum = 40;
    m_TickMarks.moveLeft(0);
    m_TickMarksMillesimal = 500;
    m_AllowPress = true;
    m_AllowMove = true;
    m_IsTracking = false;
    m_BackgroundPixmap.reset(NULL);
    m_BackgroundSvg.reset(NULL);
    m_TickMarksPixmap.reset(NULL);
    m_TickMarksPSvg.reset(NULL);
}

SliderPrivate::~SliderPrivate()
{
}

