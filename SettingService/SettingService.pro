QT += core  dbus
QT -= gui

QMAKE_POST_LINK = /opt/external-toolchain/bin/QDBusProxy $$PWD/SettingService
QMAKE_POST_LINK = $$PWD/Script.sh $$PWD/SettingService $$PWD/SettingServiceProxy

TARGET = SettingService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    SettingService.cpp \
    SettingServiceProxy.cpp

HEADERS += \
    SettingService.h \
    SettingServiceProxy.h

include(../ArkSdk.pri)

unix:!macx: LIBS += -L$$SDKPATH/Package/SettingPersistent/$$ARCHITECTURE -lSettingPersistent

SETTINGPERSISTENT = $$SDKPATH/SettingPersistent
INCLUDEPATH += $$SETTINGPERSISTENT
DEPENDPATH += $$SETTINGPERSISTENT

QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
