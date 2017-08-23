#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QScopedPointer>

class SliderPrivate;
class Slider : public QWidget
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = NULL);
    ~Slider();
    void setAllowPress(const bool flag);
    void setAllowMove(const bool flag);
    void setBackgroundBmpPath(const QString &path);
    void setTickMarkTickMarkslBmpPath(const QString &path);
    void setTickMarksSize(const QSize &size);
    void setTickMarksMillesimal(const int millesimal);
    void setRange(const int minimum, const int maxmum);
signals:
    void tickMarksMillesimalStart(const int millesimal);
    void tickMarksMillesimalChange(const int millesimal);
    void tickMarksMillesimalEnd(const int millesimal);
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    friend class SliderPrivate;
    QScopedPointer<SliderPrivate> m_Private;
};

#endif // SLIDER_H
