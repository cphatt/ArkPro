#ifndef GENERALSLIDER_H
#define GENERALSLIDER_H

#include <QWidget>
#include <QScopedPointer>

class GeneralSliderPrivate;
class GeneralSlider : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralSlider)
public:
    explicit GeneralSlider(QWidget *parent = NULL);
    ~GeneralSlider();
    void setMinimumValue(const int value);
    void setMaximumValue(const int value);
    void setTickMarksMillesimal(const int millesimal);
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
signals:
    void tickMarksMillesimalEnd(const int millesimal);
    void minusBtnRelease();
    void plusBtnRelease();
private:
    friend class GeneralSliderPrivate;
    QScopedPointer<GeneralSliderPrivate> m_Private;
};

#endif // GENERALSLIDER_H
