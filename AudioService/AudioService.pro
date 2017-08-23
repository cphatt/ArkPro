QT += core  dbus
QT -= gui

TARGET = AudioService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    AudioService.cpp \
    AudioServiceProxy.cpp

HEADERS += \
    AudioService.h \
    AudioServiceProxy.h

include(../ArkSdk.pri)

QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
