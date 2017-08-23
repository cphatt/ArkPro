QT      += core
QT      -= gui

CONFIG += C++0x

TARGET = AutoConnect
TEMPLATE = lib
CONFIG += staticlib

SOURCES += AutoConnect.cpp
HEADERS += AutoConnect.h

include(../ArkSdk.pri)
#QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
