#include "GeneralListView.h"
#include "UserInterface/Common/Utility.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QDebug>

class GeneralListViewPrivate
{
    Q_DISABLE_COPY(GeneralListViewPrivate)
public:
    explicit GeneralListViewPrivate(GeneralListView* parent);
    ~GeneralListViewPrivate();
private:
    GeneralListView* m_Parent;
};

GeneralListView::GeneralListView(QWidget *parent)
    : ListView(parent)
    , m_Private(new GeneralListViewPrivate(this))
{
    setItemHeight(94 * g_Widget->heightScalabilityFactor());
    setVisibleItemMaxCount(6);
}

GeneralListView::~GeneralListView()
{
}

void GeneralListView::normalPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list)
{
    painter.save();
    painter.fillRect(drawRect, Utility::listViewItemBrush());
    painter.setPen(Utility::customBlackColor());
    painter.drawRect(drawRect.x(), drawRect.y() + drawRect.height() - 1, drawRect.width(), 1);
    if (list.size() > 0) {
        if (list.at(0).canConvert<QString>()) {
            painter.setPen(Qt::white);
            QFont font;
            font.setPointSize(20 * g_Widget->widthScalabilityFactor());
            painter.setFont(font);
            QString text = list.at(0).value<QString>();
            painter.drawText(drawRect.adjusted(75 * g_Widget->widthScalabilityFactor(), 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, QObject::tr(text.toLocal8Bit().constData()));
        }
    }
    if (list.size() > 1) {
        if (list.at(1).canConvert<QWidget*>()) {
            QRect rect(drawRect.x() + (537 - 277) * g_Widget->widthScalabilityFactor(), drawRect.y(), (1071 - 537) * g_Widget->widthScalabilityFactor(), drawRect.height());
            list.at(1).value<QWidget*>()->setGeometry(rect);
        }
    }
    painter.restore();
}

void GeneralListView::pressPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list)
{
    normalPaint(painter, drawRect, list);
}

void GeneralListView::checkPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list)
{
    normalPaint(painter, drawRect, list);
}

GeneralListViewPrivate::GeneralListViewPrivate(GeneralListView *parent)
    : m_Parent(parent)
{
}

GeneralListViewPrivate::~GeneralListViewPrivate()
{
}
