#ifndef SETTING_H
#define SETTING_H

#include "SettingService.h"
#include "DbusService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class SettingPrivate;
class Setting
        : public QObject
        , protected SettingService::Interface
        , protected DbusService::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(Setting)
#ifdef g_Setting
#undef g_Setting
#endif
#define g_Setting (Setting::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onDateTimeChange(const QString &date, const QString &time) = 0;
        virtual void onLanguageTranslateChange(const int language) = 0;
        //    void onLanguageTranslateChange(const LanguageType language);
        virtual void onBrightnessChange(const int value) = 0;
        virtual void onContrastChange(const int value) = 0;
        virtual void onHueChange(const int value) = 0;
        virtual void onTest() {};
    };
    inline static Setting* instance() {
        static Setting* setting(new Setting(qApp));
        return setting;
    }
    void setLanguage(const int language);
    //    void setLanguage(const LanguageType language);
    void setBrightness(const int type, const int value);
    //    void setBrightness(const SetType type, const int value);
    void setContrast(const int type, const int value);
    //    void setContrast(const SetType type, const int value);
    void setHue(const int type, const int value);
    //    void setHue(const SetType type, const int value);
    void test();

signals:
    void onDateTimeChange(const QString &date, const QString &time);
    void onLanguageTranslateChange(const int language);
    //    void onLanguageTranslateChange(const LanguageType language);
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onHueChange(const int value);
    void onTest();
protected:
    void customEvent(QEvent* event);
private slots:
    void onLanguageChange(const int language);
//    void onLanguageChange(const LanguageType language);
    void onServiceRegistered(const QString& service);
    void onServiceUnregistered(const QString& service);
private:
    explicit Setting(QObject *parent = NULL);
    ~Setting();
    friend class SettingPrivate;
    QScopedPointer<SettingPrivate> m_Private;
};

#endif // SETTING_H
