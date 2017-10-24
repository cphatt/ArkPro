#include "CustomListView.h"
#include "AutoConnect.h"
#include "UserInterface/Common/Utility.h"
#include <QEvent>
#include <QDebug>
#include <QMouseEvent>
#include <QScrollBar>
#include <QPoint>

class CustomListViewPrivate
{
public:
    explicit CustomListViewPrivate(CustomListView* parent);
    ~CustomListViewPrivate();
    QPoint m_StartMovePoint;
    unsigned int m_Threshold;
    bool m_Filter;
private:
    CustomListView* m_Parent;
};

CustomListView::CustomListView(QWidget *parent)
    : QListView(parent)
    , m_Private(new CustomListViewPrivate(this))
{
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base, QBrush(Qt::transparent));
    setPalette(palette);
    setFrameShape(QListView::NoFrame);
    setVerticalScrollMode(QListView::ScrollPerPixel);
    setEditTriggers(QListView::NoEditTriggers);
    setSpacing(0);
    setDragEnabled(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSelectionBehavior(QListView::SelectRows);
    setSelectionMode(QListView::SingleSelection);
}

CustomListView::~CustomListView()
{
}

void CustomListView::setItemDelegate(QAbstractItemDelegate *delegate)
{
    connectSignalAndSlotByNamesake(this, delegate);
    QListView::setItemDelegate(delegate);
}

void CustomListView::mousePressEvent(QMouseEvent *event)
{
    m_Private->m_StartMovePoint = event->pos();
    m_Private->m_Filter = false;
    QModelIndex modelIndex = indexAt(event->pos());
    if (modelIndex.isValid()) {
        emit onPressIndexChanged(modelIndex);

        update(modelIndex);
    }
    QListView::mousePressEvent(event);
}

void CustomListView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint relativePos = m_Private->m_StartMovePoint - event->pos();
    int deltaEnd = event->pos().y() - m_Private->m_StartMovePoint.y();
    if (m_Private->m_Filter) {
        m_Private->m_StartMovePoint = event->pos();
        verticalScrollBar()->setValue(verticalOffset() + relativePos.y());
    } else if ((qAbs(deltaEnd) > m_Private->m_Threshold)) {
        emit onPressIndexChanged(QModelIndex());
        m_Private->m_Filter = true;
        m_Private->m_StartMovePoint = event->pos();
        if (relativePos.y() > 0) {
            verticalScrollBar()->setValue(verticalOffset() + relativePos.y() - m_Private->m_Threshold);
        } else {
            verticalScrollBar()->setValue(verticalOffset() + relativePos.y() + m_Private->m_Threshold);
        }
    }
    QListView::mouseReleaseEvent(event);
}

void CustomListView::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_Private->m_Filter) {
        QModelIndex modelIndex = indexAt(event->pos());
        if (modelIndex.isValid()) {
            emit listViewItemRelease(modelIndex.row());
        }
    }
    emit onPressIndexChanged(QModelIndex());
    m_Private->m_Filter = false;
    QListView::mouseReleaseEvent(event);
}

CustomListViewPrivate::CustomListViewPrivate(CustomListView *parent)
    : m_Parent(parent)
{
    m_StartMovePoint = QPoint(0, 0);
    m_Threshold = 10;
    m_Filter = false;
}

CustomListViewPrivate::~CustomListViewPrivate()
{
}
