#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Setting/Setting.h"
#include <QWidget>
#include <QScopedPointer>

class StatusBarWidgetPrivate;
class StatusBarWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Setting::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(StatusBarWidget)
public:
    explicit StatusBarWidget(QWidget *parent = NULL);
    ~StatusBarWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Setting::Interface
    void onDateTimeChange(const QString &date, const QString &time);
    void onLanguageTranslateChange(const int language);
    //    void onLanguageTranslateChange(const LanguageType language);
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onHueChange(const int value);
private:
    friend class StatusBarWidgetPrivate;
    friend class TextWidget;
    QScopedPointer<StatusBarWidgetPrivate> m_Private;
};

#endif // STATUSBAR_H
