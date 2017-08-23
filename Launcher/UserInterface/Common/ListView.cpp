#include "ListView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QList>

class ListViewPrivate
{
    Q_DISABLE_COPY(ListViewPrivate)
public:
    ListViewPrivate();
    ~ListViewPrivate();
    void initialize();
    int m_Offset;
    int m_ItemHeight;
    int m_PressItem;
    int m_SelectedItem;
    int m_DeltaStart;
    int m_VisibleItemMaxCount;
    int m_ThresHold;
    QList< QList<QVariant> > m_ListList;
};

ListView::ListView(QWidget *parent)
    : QWidget(parent)
    , m_Private(new ListViewPrivate())
{
//    QList<QVariant> list;
//    list.clear();
//    list.append(QString("test"));
//    m_Private->m_ListList.replace(0, list);
}

ListView::~ListView()
{
}

void ListView::setScrollPersent(const float persent)
{
    if (m_Private->m_ListList.size() > m_Private->m_VisibleItemMaxCount) {
        m_Private->m_Offset = static_cast<int>(persent * (m_Private->m_ItemHeight * m_Private->m_ListList.size() - height()));
        update();
    }
}

void ListView::setItemHeight(const int height)
{
    m_Private->m_ItemHeight = height;
}

void ListView::setVisibleItemMaxCount(const int count)
{
    m_Private->m_VisibleItemMaxCount = count;
}

void ListView::clearListView()
{
    m_Private->m_ListList.clear();
    m_Private->m_Offset = 0;
    m_Private->m_PressItem = -1;
    m_Private->m_SelectedItem = -1;
    m_Private->m_DeltaStart = -1;
    update();
}

void ListView::setCheckIndex(const int index)
{
    m_Private->m_SelectedItem = index;
    update();
}

void ListView::appendListView(const QList<QVariant> &list)
{
    m_Private->m_ListList.append(list);
}

void ListView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int startItem = m_Private->m_Offset / m_Private->m_ItemHeight;
    int y = startItem * m_Private->m_ItemHeight - m_Private->m_Offset;
    int endItem = startItem + height() / m_Private->m_ItemHeight;
    if (endItem >= (m_Private->m_ListList.size() - 1)) {
        endItem = m_Private->m_ListList.size() - 1;
    } else {
        ++endItem;
    }
    for (int i = startItem; i <= endItem; ++i) {
        QRect rect = QRect(0, y + m_Private->m_ItemHeight * (i - startItem), width(), m_Private->m_ItemHeight);
//        qDebug() << "m_Private->m_SelectedItem" << m_Private->m_SelectedItem;
        if (m_Private->m_SelectedItem == i) {
            checkPaint(painter, rect, m_Private->m_ListList.at(i));
        } else if (m_Private->m_PressItem == i) {
            pressPaint(painter, rect, m_Private->m_ListList.at(i));
        } else {
            normalPaint(painter, rect, m_Private->m_ListList.at(i));
        }
    }
    QWidget::paintEvent(event);
}

void ListView::mousePressEvent(QMouseEvent *event)
{
    int y = event->pos().y() + m_Private->m_Offset;
    m_Private->m_PressItem = y / m_Private->m_ItemHeight;
    m_Private->m_DeltaStart = event->pos().y();
    update();
    QWidget::mousePressEvent(event);
}

void ListView::mouseMoveEvent(QMouseEvent *event)
{
    int deltaEnd = event->pos().y() - m_Private->m_DeltaStart;
    if (-1 != m_Private->m_PressItem) {
        if ((deltaEnd > m_Private->m_ThresHold)
                || (deltaEnd < -m_Private->m_ThresHold)) {
            m_Private->m_PressItem = -1;
            m_Private->m_DeltaStart = event->pos().y();
        }
    } else {
        if (m_Private->m_ListList.size() > m_Private->m_VisibleItemMaxCount) {
            m_Private->m_DeltaStart = event->pos().y();
            m_Private->m_Offset -= deltaEnd;
            if (m_Private->m_Offset < 0) {
                m_Private->m_Offset = 0;
            } else if ((m_Private->m_ListList.size() * m_Private->m_ItemHeight - height()) > 0) {
                if (m_Private->m_Offset > (m_Private->m_ListList.size() * m_Private->m_ItemHeight - height())) {
                    m_Private->m_Offset = m_Private->m_ListList.size() * m_Private->m_ItemHeight - height();
                }
            } else if ((m_Private->m_ListList.size() * m_Private->m_ItemHeight - height()) <= 0) {
                m_Private->m_Offset = 0;
            }
            update();
            emit scrollPersent(static_cast<float>(m_Private->m_Offset) / (m_Private->m_ItemHeight * m_Private->m_ListList.size() - height()));
        } else {
            update();
        }
    }
    QWidget::mouseMoveEvent(event);
}

void ListView::mouseReleaseEvent(QMouseEvent *event)
{
    if (isVisible()) {
        int index = (event->pos().y() + m_Private->m_Offset) / m_Private->m_ItemHeight;
        if (-1 != m_Private->m_PressItem) {
            //            if (index != m_Private->m_SelectedItem) {
            if (m_Private->m_ListList.size() > index) {
                m_Private->m_SelectedItem = index;
                update();
                emit listViewItemRelease(m_Private->m_SelectedItem);
            }
            //            }
        }
    }
    QWidget::mouseReleaseEvent(event);
}

ListViewPrivate::ListViewPrivate()
{
    m_Offset = 0;
    m_VisibleItemMaxCount = 6;
    m_ItemHeight = 60;
    m_PressItem = -1;
    m_SelectedItem = -1;
    m_DeltaStart = -1;
    m_ListList.clear();
    m_ThresHold = 10;
    initialize();
}

ListViewPrivate::~ListViewPrivate()
{
}

void ListViewPrivate::initialize()
{
}
