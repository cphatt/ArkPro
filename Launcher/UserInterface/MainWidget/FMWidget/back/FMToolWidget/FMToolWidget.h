#ifndef FMTOOLWIDGETIDGET_H
#define FMTOOLWIDGETIDGET_H

#include "BusinessLogic/AudioManager/AudioManager.h"
#include <QWidget>
#include <QScopedPointer>

class FMToolWidgetPrivate;
class FMToolWidget
        : protected QWidget
        , protected AudioManager::Interface
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
    void onVolumeChange(const int volume);
    void onVolumeRangeChange(const int min, const int max);
    void onFMChange(int freq);
    void OnFMIsOpen(int open);
private slots:
    void onToolButtonRelease();
private:
    friend class FMToolWidgetPrivate;
    QScopedPointer<FMToolWidgetPrivate> m_Private;
};

#endif // FMTOOLWIDGETIDGET_H
