#ifndef GENERALLISTVIEW_H
#define GENERALLISTVIEW_H

#include "UserInterface/Common/ListView.h"
#include <QVariant>
#include <QList>
#include <QScopedPointer>

class GeneralListViewPrivate;
class GeneralListView : public ListView
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralListView)
public:
    explicit GeneralListView(QWidget* parent);
    ~GeneralListView();
protected:
    void normalPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list);
    void pressPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list);
    void checkPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list);
private:
    friend class GeneralListViewPrivate;
    QScopedPointer<GeneralListViewPrivate> m_Private;
};

#endif // GENERALLISTVIEW_H
