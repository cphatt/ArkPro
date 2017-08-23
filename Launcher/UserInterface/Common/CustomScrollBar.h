#ifndef CUSTOMSCROLLBAR_H
#define CUSTOMSCROLLBAR_H

#include <QScrollBar>

class CustomScrollBarPrivate;
class CustomScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit CustomScrollBar(QWidget *parent = NULL);
    ~CustomScrollBar();
private:
    friend class CustomScrollBarPrivate;
    QScopedPointer<CustomScrollBarPrivate> m_Private;
};

#endif // CUSTOMSCROLLBAR_H
