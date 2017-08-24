#ifndef EFFECTCONTROLS_H
#define EFFECTCONTROLS_H

#include <QWidget>
#include <QScopedPointer>
#include "BusinessLogic/Audio/Audio.h"

class EffectSoundWidgetPrivate;
class EffectSoundWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(EffectSoundWidget)
public:
    explicit EffectSoundWidget(QWidget *parent = NULL);
    ~EffectSoundWidget();
        void setTickMarksMillesimal(const int millesimal);
protected:
    void resizeEvent(QResizeEvent* event);
    void changeEvent(QEvent* event);
    void paintEvent(QPaintEvent* event);
protected slots:
    //AudioManager::Interface
//    void onFMChange(int freq);
//    void onFMIsOpen(int open);
    void onVolumeChange(int type ,int volume);
//    void onVolumeRangeChange(int min, int max);
private slots:
    void onMinusBtnRelease();
    void onPlusBtnRelease();
    void onTickMarksMillesimalEnd(const int millesimal);


private:
    friend class EffectSoundWidgetPrivate;
    QScopedPointer<EffectSoundWidgetPrivate> m_Private;
};

#endif // EFFECTCONTROLS_H
