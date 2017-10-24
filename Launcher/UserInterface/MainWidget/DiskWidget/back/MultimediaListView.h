#ifndef MULTIMEDIALISTVIEW_H
#define MULTIMEDIALISTVIEW_H

#include "UserInterface/Common/ListView.h"
#include <QScopedPointer>

class MultimediaListViewPrivate;
class MultimediaListView : public ListView
{
    Q_OBJECT
    Q_DISABLE_COPY(MultimediaListView)
public:
    explicit MultimediaListView(QWidget *parent = NULL);
    ~MultimediaListView();
    void setFontPixelSize(const int size);
protected:
    void normalPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list);
    void pressPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list);
    void checkPaint(QPainter &painter, const QRect &drawRect, const QList<QVariant> &list);
private:
    QScopedPointer<MultimediaListViewPrivate> m_Private;
};

#endif // MULTIMEDIALISTVIEW_H
