#ifndef MULTIMEDIALISTVIEW_H
#define MULTIMEDIALISTVIEW_H

#include "UserInterface/Common/CustomListView.h"
#include <QScopedPointer>

class MultimediaListViewPrivate;
class MultimediaListView : public CustomListView
{
    Q_OBJECT
    Q_DISABLE_COPY(MultimediaListView)
public:
    explicit MultimediaListView(QWidget* parent = NULL);
    ~MultimediaListView();
    void clearListView();
    void appendListView(QString path);
private:
    friend class MultimediaListViewPrivate;
    QScopedPointer<MultimediaListViewPrivate> m_Private;
};

#endif // MULTIMEDIALISTVIEW_H
