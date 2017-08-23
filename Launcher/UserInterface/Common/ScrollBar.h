#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include <QWidget>
#include <QScopedPointer>

class ScrollBarPrivate;
class ScrollBar : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(ScrollBar)
public:
    explicit ScrollBar(QWidget *parent = NULL);
    ~ScrollBar();
public slots:
    void setScrollPercent(const float percent);
    void setItemHeight(const int height);
signals:
    void scrollPersent(const float persent);
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    friend class ScrollBarPrivate;
    QScopedPointer<ScrollBarPrivate> m_Private;
};

#endif // SCROLLBAR_H
