#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T11:53:36
#
#-------------------------------------------------

QT       -= core
QT       -= gui

TARGET = Utility
TEMPLATE = lib
CONFIG += staticlib

SOURCES += Utility.cpp

HEADERS += Utility.h

include(../ArkSdk.pri)
#QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
