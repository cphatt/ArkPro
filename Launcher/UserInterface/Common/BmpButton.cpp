#include "BmpButton.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QSvgRenderer>
#include <QDebug>
#include <QFile>
#include <QScopedPointer>

class BmpButtonPrivate
{
    Q_DISABLE_COPY(BmpButtonPrivate)
public:
    explicit BmpButtonPrivate(BmpButton* parent);
    ~BmpButtonPrivate();
    QString m_Text;
    QScopedPointer<QPixmap> m_NormalPixmap;
    QScopedPointer<QPixmap> m_PressPixmap;
    QScopedPointer<QPixmap> m_CheckPixmap;
    QScopedPointer<QSvgRenderer> m_NormalSvg;
    QScopedPointer<QSvgRenderer> m_PressSvg;
    QScopedPointer<QSvgRenderer> m_CheckSvg;
    BmpButton::ButtonStatus m_Status;
private:
    BmpButton* m_Parent;
};


BmpButton::BmpButton(QWidget *parent)
    : QWidget(parent)
    , m_Private(new BmpButtonPrivate(this))
{
}

BmpButton::~BmpButton()
{
}

void BmpButton::setText(const QString &text)
{
    m_Private->m_Text = text;
    update();
}

QString BmpButton::getText()
{
    return m_Private->m_Text;
}

void BmpButton::setNormalBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_NormalPixmap.reset(new QPixmap(path + QString(".png")));
    } else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_NormalSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    }
    update();
}

void BmpButton::setPressBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_PressPixmap.reset(new QPixmap(path + QString(".png")));
    } else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_PressSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    }
    update();
}

void BmpButton::setCheckBmpPath(const QString &path)
{
    if (QFile(path + QString(".png")).exists()) {
        m_Private->m_CheckPixmap.reset(new QPixmap(path + QString(".png")));
    } else if (QFile(path + QString(".svg")).exists()) {
        m_Private->m_CheckSvg.reset(new QSvgRenderer(path + QString(".svg"), this));
    }
    update();
}

void BmpButton::setStatus(const BmpButton::ButtonStatus &status)
{
    if (status != m_Private->m_Status) {
        m_Private->m_Status = status;
    }
    update();
}

BmpButton::ButtonStatus BmpButton::getStatus()
{
    return m_Private->m_Status;
}

void BmpButton::mousePressEvent(QMouseEvent *event)
{
    m_Private->m_Status = BmpButton::B_Press;
    update();
    emit bmpButtomPress();
    QWidget::mousePressEvent(event);
}

void BmpButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (isVisible()) {
        m_Private->m_Status = BmpButton::B_Normal;
        update();
        emit bmpButtonRelease();
    }
    QWidget::mouseReleaseEvent(event);
}

void BmpButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    switch (m_Private->m_Status) {
    case BmpButton::B_Check: {
        checkPaint(painter);
        break;
    }
    case BmpButton::B_Press: {
        pressPaint(painter);
        break;
    }
    case BmpButton::B_Normal:
    default : {
        normalPaint(painter);
        break;
    }
    }
    QWidget::paintEvent(event);
}

void BmpButton::normalPaint(QPainter &painter)
{
    if (NULL != m_Private->m_NormalPixmap) {
        painter.drawPixmap((width() - m_Private->m_NormalPixmap->width()) / 2, (height() - m_Private->m_NormalPixmap->height()) / 2, *m_Private->m_NormalPixmap);
    } else if (NULL != m_Private->m_NormalSvg) {
        m_Private->m_NormalSvg->render(&painter, QRect((width() - m_Private->m_NormalSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2,
                                                       (height() - m_Private->m_NormalSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                       m_Private->m_NormalSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                       m_Private->m_NormalSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
    if (!m_Private->m_Text.isEmpty()) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
    }
#ifdef gcc
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
#endif
}

void BmpButton::pressPaint(QPainter &painter)
{
    if (NULL != m_Private->m_PressPixmap) {
        painter.drawPixmap((width() - m_Private->m_PressPixmap->width()) / 2, (height() - m_Private->m_PressPixmap->height()) / 2, *m_Private->m_PressPixmap);
    } else if (NULL != m_Private->m_PressSvg) {
        m_Private->m_PressSvg->render(&painter, QRect((width() - m_Private->m_PressSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2,
                                                      (height() - m_Private->m_PressSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                      m_Private->m_PressSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                      m_Private->m_PressSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
    if (!m_Private->m_Text.isEmpty()) {
        painter.setPen(Qt::darkRed);
        painter.drawText(rect(), Qt::AlignCenter, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
    }
}

void BmpButton::checkPaint(QPainter &painter)
{
    if (NULL != m_Private->m_CheckPixmap) {
        painter.drawPixmap((width() - m_Private->m_CheckPixmap->width()) / 2, (height() - m_Private->m_CheckPixmap->height()) / 2, *m_Private->m_CheckPixmap);
    } else if (NULL != m_Private->m_CheckSvg) {
        m_Private->m_CheckSvg->render(&painter, QRect((width() - m_Private->m_CheckSvg->defaultSize().width() * g_Widget->widthScalabilityFactor()) / 2,
                                                      (height() - m_Private->m_CheckSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()) / 2,
                                                      m_Private->m_CheckSvg->defaultSize().width() * g_Widget->widthScalabilityFactor(),
                                                      m_Private->m_CheckSvg->defaultSize().height() * g_Widget->heightScalabilityFactor()));
    }
    if (!m_Private->m_Text.isEmpty()) {
        painter.setPen(Qt::darkGreen);
        painter.drawText(rect(), Qt::AlignCenter, QObject::tr(m_Private->m_Text.toLocal8Bit().constData()));
    }
}

BmpButtonPrivate::BmpButtonPrivate(BmpButton* parent)
    : m_Parent(parent)
{
    m_Text.clear();
    m_Status = BmpButton::B_Normal;
}

BmpButtonPrivate::~BmpButtonPrivate()
{
}
