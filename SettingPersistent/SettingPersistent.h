#ifndef SETTINGPERSISTENT_H
#define SETTINGPERSISTENT_H

#include <QtGlobal>

class SettingService;
class SettingPersistent
{
    Q_DISABLE_COPY(SettingPersistent)
public:
    static int getLanguage();
    static int getBrightness();        
    static int getContrast();
    static int getHue();
protected:
    friend class SettingService;
    static void setLanguage(const int value);
    static void setBrightness(const int value);
    static void setContrast(const int value);
    static void setHue(const int value);
private:
    SettingPersistent();
    ~SettingPersistent();
};

#endif // SETTINGPERSISTENT_H
