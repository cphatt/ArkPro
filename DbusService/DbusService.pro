QT += core  dbus
QT -= gui

TARGET = DbusService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    DbusService.cpp

HEADERS += \
    DbusService.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher

