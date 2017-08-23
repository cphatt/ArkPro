#ifndef EFFECTSOUNDSLIDER_H
#define EFFECTSOUNDSLIDER_H

#include <QWidget>
#include <QScopedPointer>

class EffectSoundSliderPrivate;
class EffectSoundSlider : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(EffectSoundSlider)
public:
    explicit EffectSoundSlider(QWidget *parent = NULL);
    ~EffectSoundSlider();
    void setMinimumValue(const int value);
    void setMaximumValue(const int value);
        void setTickMarksMillesimal(const int millesimal);
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);

signals:
    void minusBtnRelease();
    void plusBtnRelease();
    void tickMarksMillesimalEnd(const int millesimal);

private:
    friend class EffectSoundSliderPrivate;
    QScopedPointer<EffectSoundSliderPrivate> m_Private;
};

#endif // EFFECTSOUNDSLIDER_H
