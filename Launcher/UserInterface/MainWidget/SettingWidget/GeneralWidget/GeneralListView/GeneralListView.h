#ifndef GENERALLISTVIEW_H
#define GENERALLISTVIEW_H

#include "UserInterface/Common/CustomListView.h"
#include "BusinessLogic/Audio/Audio.h"
#include "BusinessLogic/Setting/Setting.h"
#include <QScopedPointer>

class GeneralListViewPrivate;
class GeneralListView
        : protected CustomListView
        , protected Setting::Interface
        , protected Audio::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(GeneralListView)
public:

    enum GeneraSetType {
        Calibrate = 0,
        TimeSetting = 1,
    };

    explicit GeneralListView(QWidget* parent = NULL);
    ~GeneralListView();
protected:
    void changeEvent(QEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
protected slots:
    //Setting::Interface
    void onDateTimeChange(const QString &date, const QString &time);
    void onLanguageTranslateChange(const int language);
    //    void onLanguageTranslateChange(const LanguageType language);
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onHueChange(const int value);
    //AudioManager::Interface
    void onFMChange(int freq);
    void onFMIsOpen(int open);
    void onVolumeChange(int type ,int volume);
    void onVolumeRangeChange(int min, int max);
private slots:
    void onMinusBtnRelease();
    void onPlusBtnRelease();
    void onTickMarksMillesimalEnd(const int millesimal);
private:
    friend class GeneralListViewPrivate;
    QScopedPointer<GeneralListViewPrivate> m_Private;
};

#endif // GENERALLISTVIEW_H
