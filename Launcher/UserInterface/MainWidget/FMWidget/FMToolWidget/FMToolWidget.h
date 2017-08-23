#ifndef FMTOOLWIDGETIDGET_H
#define FMTOOLWIDGETIDGET_H

#include "BusinessLogic/Audio/Audio.h"
#include <QWidget>
#include <QScopedPointer>

class FMToolWidgetPrivate;
class FMToolWidget
        : protected QWidget
        , protected Audio::Interface
{
    Q_OBJECT
public:
    explicit FMToolWidget(QWidget* parent = NULL);
    ~FMToolWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    bool event(QEvent* event);
protected slots:
    //AudioManager::Interface
    void onFMChange(int freq);
    void onFMIsOpen(int open);
    void onVolumeChange(int volume);
    void onVolumeRangeChange(int min, int max);
private slots:
    void onToolButtonRelease();
private:
    friend class FMToolWidgetPrivate;
    QScopedPointer<FMToolWidgetPrivate> m_Private;
};

#endif // FMTOOLWIDGETIDGET_H
