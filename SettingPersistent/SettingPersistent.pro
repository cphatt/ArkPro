#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T16:09:58
#
#-------------------------------------------------
QT       += core
QT       -= gui

TARGET = SettingPersistent
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    SettingPersistent.cpp
HEADERS += \
    SettingPersistent.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
