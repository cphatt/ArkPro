#-------------------------------------------------
#
# Project created by QtCreator 2017-01-14T08:23:55
#
#-------------------------------------------------

QT       -= gui

TARGET = EventEngine
TEMPLATE = lib
CONFIG += staticlib

SOURCES += EventEngine.cpp
HEADERS += EventEngine.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
