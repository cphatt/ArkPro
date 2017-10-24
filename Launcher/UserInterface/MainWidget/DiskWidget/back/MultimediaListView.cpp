#include "MultimediaListView.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QDebug>
#include <QFont>
#include <QScopedPointer>

class MultimediaListViewPrivate
{
    Q_DISABLE_COPY(MultimediaListViewPrivate)
public:
    explicit MultimediaListViewPrivate(MultimediaListView* parent);
    ~MultimediaListViewPrivate();
    void initialize();
    QFont m_Font;
    QScopedPointer<QPixmap> m_Check;
private:
    MultimediaListView* m_Parent;
};

MultimediaListView::MultimediaListView(QWidget *parent)
    : ListView(parent)
    , m_Private(new MultimediaListViewPrivate(this))
{
    setItemHeight(94 * g_Widget->heightScalabilityFactor());
    setVisibleItemMaxCount(6);
}

MultimediaListView::~MultimediaListView()
{
}

void MultimediaListView::setFontPixelSize(const int size)
{
    m_Private->m_Font.setPixelSize(size);
    update();
}

void MultimediaListView::normalPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list)
{
    painter.save();
    if (list.size() > 1) {
        if (list.at(0).canConvert<QString>()
                && list.at(1).canConvert<QString>()) {
            QString text = list.at(0).value<QString>() + QString(".") + list.at(1).value<QString>();
            QRect rect(drawRect.adjusted(0, 0, 0, 0));
            painter.fillRect(drawRect, Utility::listViewItemBrush());
            painter.setPen(Utility::customBlackColor());
            painter.drawRect(drawRect.x(), drawRect.y() + drawRect.height() - 1, drawRect.width(), 1);
            painter.setFont(m_Private->m_Font);
            painter.setPen(Qt::white);
            painter.drawText(rect.adjusted(121 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
        }
    }
    painter.restore();
}

void MultimediaListView::pressPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list)
{
    painter.save();
    if (list.size() > 1) {
        if (list.at(0).canConvert<QString>()
                && list.at(1).canConvert<QString>()) {
            QString text = list.at(0).value<QString>() + QString(".") + list.at(1).value<QString>();
            QRect rect(drawRect.adjusted(0, 0, 0, 0));
            painter.fillRect(rect, Utility::listViewItemBrush());
            painter.setPen(Utility::customBlackColor());
            painter.drawRect(drawRect.x(), drawRect.y() + drawRect.height() - 1, drawRect.width(), 1);
            painter.setFont(m_Private->m_Font);
            painter.setPen(QColor(158, 158, 47));
            painter.drawText(rect.adjusted(121 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
        }
    }
    painter.restore();
}

void MultimediaListView::checkPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list)
{
    painter.save();
    if (list.size() > 1) {
        if (list.at(0).canConvert<QString>()
                && list.at(1).canConvert<QString>()) {
            QString text = list.at(0).value<QString>() + QString(".") + list.at(1).value<QString>();
            QRect rect(drawRect.adjusted(0, 0, 0, 0));
            painter.fillRect(rect, Utility::listViewItemBrush());
            painter.setPen(Utility::customBlackColor());
            painter.drawRect(drawRect.x(), drawRect.y() + drawRect.height() - 1, drawRect.width(), 1);
            painter.setFont(m_Private->m_Font);
            painter.setPen(Qt::white);
            painter.drawText(rect.adjusted(121 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text);
            if (m_Private->m_Check.isNull()) {
                painter.drawPixmap(320 - 278, rect.y() + (rect.height() - 51) * 0.5, *m_Private->m_Check);
            }
        }
    }
    painter.restore();
}

MultimediaListViewPrivate::MultimediaListViewPrivate(MultimediaListView *parent)
    : m_Parent(parent)
{
    m_Check.reset(NULL);
    initialize();
}

MultimediaListViewPrivate::~MultimediaListViewPrivate()
{
}

void MultimediaListViewPrivate::initialize()
{
    m_Font.setPixelSize(22 * g_Widget->widthScalabilityFactor());
    m_Check.reset(new QPixmap(QString(":/Images/Resources/Images/MultimediaListViewCheck")));
}
