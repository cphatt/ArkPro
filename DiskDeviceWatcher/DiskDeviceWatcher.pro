#-------------------------------------------------
#
# Project created by QtCreator 2017-01-17T21:48:48
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = DiskDeviceWatcher
TEMPLATE = lib
CONFIG += staticlib

SOURCES += DiskDeviceWatcher.cpp
HEADERS += DiskDeviceWatcher.h

include(../ArkSdk.pri)
#QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
