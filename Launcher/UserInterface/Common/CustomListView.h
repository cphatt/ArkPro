#ifndef CUSTOMLISTVIEW_H
#define CUSTOMLISTVIEW_H

#include <QListView>
#include <QScopedPointer>

class CustomListViewPrivate;
class CustomListView : public QListView
{
    Q_OBJECT
    Q_DISABLE_COPY(CustomListView)
public:
    explicit CustomListView(QWidget *parent = NULL);
    ~CustomListView();
    void setItemDelegate(QAbstractItemDelegate *delegate);
protected:
    void mousePressEvent(QMouseEvent* event) ;
    void mouseMoveEvent(QMouseEvent* event) ;
    void mouseReleaseEvent(QMouseEvent* event)  ;
signals:
    void onPressIndexChanged(const QModelIndex &index);
    void onCurrentIndexChange(const QModelIndex &index);
    void listViewItemRelease(const int index);
private:
    friend class CustomListViewPrivate;
    QScopedPointer<CustomListViewPrivate> m_Private;
};

#endif // CUSTOMLISTVIEW_H
