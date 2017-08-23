#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QWidget>
#include <QVariant>
#include <QList>
#include <QScopedPointer>

class ListViewPrivate;
class ListView : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ListView)
public:
    explicit ListView(QWidget *parent = NULL);
    virtual ~ListView();
    void clearListView();
    void setCheckIndex(const int index);
    void appendListView(const QList<QVariant> &list);
public slots:
    void setScrollPersent(const float persent);
signals:
    void scrollPersent(const float persent);
    void listViewItemRelease(const int index);
    void disableScrollbar(const bool flag);
protected:
    void setItemHeight(const int height);
    void setVisibleItemMaxCount(const int count);
    virtual void normalPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list) = 0;
    virtual void pressPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list) = 0;
    virtual void checkPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list) = 0;
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    friend class ListViewPrivate;
    QScopedPointer<ListViewPrivate> m_Private;
};

#endif // LISTVIEW_H
