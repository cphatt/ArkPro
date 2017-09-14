#ifndef LANGUAGEWIDGET_H
#define LANGUAGEWIDGET_H

#include "BusinessLogic/Setting/Setting.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class LanguageWidgetPrivate;
class LanguageWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Setting::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(LanguageWidget)
public:
    explicit LanguageWidget(QWidget *parent = NULL);
    ~LanguageWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
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
    void onVolumeChange(const int type, const int value);
    void onEffectChange(const int type, const int hight, const int middle, const int low);
    void onTest();
private slots:
    void onToolButtonRelease();
private:
    friend class LanguageWidgetPrivate;
    QScopedPointer<LanguageWidgetPrivate> m_Private;
};

#endif // LANGUAGEWIDGET_H
