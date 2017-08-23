#include "BmpWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QSvgRenderer>
#include <QFile>
#include <QDebug>
#include <QScopedPointer>

class BmpWidgetPrivate
{
    Q_DISABLE_COPY(BmpWidgetPrivate)
public:
    explicit BmpWidgetPrivate(BmpWidget* parent);
    ~BmpWidgetPrivate();
    QScopedPointer<QPixmap> m_BackgroundPixmap;
    QScopedPointer<QSvgRenderer> m_BackgroundSvg;
private:
    BmpWidget* m_Parent;
};

BmpWidget::BmpWidget(QWidget *parent)
    : QWidget(parent)
    , m_Private(new BmpWidgetPrivate(this))
{
}

BmpWidget::~BmpWidget()
{
}

void BmpWidget::setBackgroundBmpPath(const QString &path)
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

void BmpWidget::paintEvent(QPaintEvent *event)
{
#ifdef gcc
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
    if (!m_Private->m_BackgroundPixmap.isNull()) {
        QPainter painter(this);
        painter.drawPixmap((width() - m_Private->m_BackgroundPixmap->width()) / 2, (height() - m_Private->m_BackgroundPixmap->height()) / 2, *m_Private->m_BackgroundPixmap);
    } else if (!m_Private->m_BackgroundSvg.isNull()) {
        QPainter painter(this);
        m_Private->m_BackgroundSvg->render(&painter, QRect((width() - m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2,
                                                           (height() - m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                           m_Private->m_BackgroundSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                           m_Private->m_BackgroundSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
    QWidget::paintEvent(event);
}

BmpWidgetPrivate::BmpWidgetPrivate(BmpWidget *parent)
    : m_Parent(parent)
{
    m_BackgroundPixmap.reset(NULL);
    m_BackgroundSvg.reset(NULL);
}

BmpWidgetPrivate::~BmpWidgetPrivate()
{
}
