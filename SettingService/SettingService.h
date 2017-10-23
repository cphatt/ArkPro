#ifndef SETTINGSERVICE_H
#define SETTINGSERVICE_H

#define SettingApplication           QString("-setting")
#define ArkMicroSettingService       QString("com.arkmicro.setting")
#define ArkMicroSettingPath          QString("/com/arkmicro/setting")
#define ArkMicroSettingInterface     QString("Local.DbusServer.Setting")

#include "SettingServiceProxy.h"
#include <QObject>
#include <QScopedPointer>

enum LanguageType {
    LT_English = 0,
    LT_Chinese = 1,
    LT_Japaness = 2,
    LT_Korean = 3,
    LT_Spanish = 4,
    LT_Portuguese = 5,
    LT_Russian = 6,
    LT_German = 7,
    LT_French = 8,
};
#define LanguageType int

enum SettingType {
    ST_Value = 0,
    ST_Plus = 1,
    ST_Minus = 2,
};
#define SettingType int

class SettingServicePrivate;
class SettingService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SettingService)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Setting")
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        //public slots:
        virtual void setLanguage(const int language) = 0;
        //    void setLanguage(const LanguageType language);
        virtual void setBrightness(const int type, const int value) = 0;
        //    void setBrightness(const SettingType type, const int value);
        virtual void setContrast(const int type, const int value) = 0;
        //    void setContrast(const SettingType type, const int value);
        virtual void setHue(const int type, const int value) = 0;
        //    void setHue(const SettingType type, const int value);
        virtual void test() = 0;
        //signals:
        virtual void onDateTimeChange(const QString &date, const QString &time) = 0;
        virtual void onLanguageChange(const int language) = 0;
        //    void onLanguageChange(const LanguageType language);
        virtual void onBrightnessChange(const int value) = 0;
        virtual void onContrastChange(const int value) = 0;
        virtual void onHueChange(const int value) = 0;
        virtual void onTest() = 0;
//                virtual void onTest1() = 0; //并不影响

    };
    explicit SettingService(QObject* parent = NULL);
    ~SettingService();
public slots:
    void synchronize();
    void setLanguage(const int language);
    //    void setLanguage(const LanguageType language);
    void setBrightness(const int type, const int value);
    //    void setBrightness(const SettingType type, const int value);
    void setContrast(const int type, const int value);
    //    void setContrast(const SettingType type, const int value);
    void setHue(const int type, const int value);
    //    void setHue(const SettingType type, const int value);
    void test();
    void test1();
signals:
    void onDateTimeChange(const QString &date, const QString &time);
    void onLanguageChange(const int language);
    //    void onLanguageChange(const LanguageType language);
    void onBrightnessChange(const int value);
    void onContrastChange(const int value);
    void onHueChange(const int value);
    void onTest();
    void onTest1();
private slots:
    void onTimeout();
private:
    friend class SettingServicePrivate;
    QScopedPointer<SettingServicePrivate> m_Private;
};

#endif // SETTINGSERVICE_H
