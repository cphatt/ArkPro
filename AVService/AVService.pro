QT += core  dbus
QT -= gui

TARGET = AVService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    AVService.cpp

HEADERS += \
    AVService.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
