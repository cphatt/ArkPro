#include "SettingPersistent.h"
#include <QSettings>
#include <QDebug>
#include <QCoreApplication>

#ifdef gcc
static const QString persistentPath("/tmp/Setting.ini");
#else
static const QString persistentPath("/data/Setting.ini");
#endif
static const QString Language("Language");
static const QString Brightness("Brightness");
static const QString Contrast("Contrast");
static const QString Hue("Hue");
static QSettings settings(persistentPath, QSettings::IniFormat, qApp);

void SettingPersistent::setLanguage(const int value)
{
    qDebug() << "SettingPersistent::setLanguage" << value;
    settings.setValue(Language, value);
    settings.sync();
}

int SettingPersistent::getLanguage()
{
    int defaultValue(1); //默认的值
    bool flag(false);
    int ret = settings.value(Language, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setBrightness(const int value)
{
    qDebug() << "SettingPersistent::setBrightness" << value;
    settings.setValue(Brightness, value);
    settings.sync();
}

int SettingPersistent::getBrightness()
{
    int defaultValue(7);
    bool flag(false);
    int ret = settings.value(Brightness, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setContrast(const int value)
{
    qDebug() << "SettingPersistent::setContrast" << value;
    settings.setValue(Contrast, value);
    settings.sync();
}

int SettingPersistent::getContrast()
{
    int defaultValue(7);
    bool flag(false);
    int ret = settings.value(Contrast, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

void SettingPersistent::setHue(const int value)
{
    qDebug() << "SettingPersistent::setHue" << value;
    settings.setValue(Hue, value);
    settings.sync();
}

int SettingPersistent::getHue()
{
    int defaultValue(7);
    bool flag(false);
    int ret = settings.value(Hue, defaultValue).toInt(&flag);
    if (!flag) {
        ret = defaultValue;
    }
    return ret;
}

SettingPersistent::SettingPersistent()
{
}

SettingPersistent::~SettingPersistent()
{
}
