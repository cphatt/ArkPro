#ifndef SCROLL_H
#define SCROLL_H

#include <QWidget>
#include <QScopedPointer>

class ScrollPrivate;
class Scroll : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(Scroll)
public:
    explicit Scroll(QWidget *parent = NULL);
    ~Scroll();
    void setScrollPercent(const float percent);
    void setItemHeight(const int height);
signals:
    void scrollPersent(const float persent);
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    QScopedPointer<ScrollPrivate> m_Private;
};

#endif // SCROLL_H
