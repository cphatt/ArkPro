#-------------------------------------------------
#
# Project created by QtCreator 2017-01-03T14:11:00
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = RunnableThread
TEMPLATE = lib
CONFIG += staticlib

SOURCES += RunnableThread.cpp
HEADERS += RunnableThread.h

include(../ArkSdk.pri)
#QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
