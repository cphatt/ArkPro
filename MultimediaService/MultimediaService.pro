QT      += core gui xml dbus

QMAKE_POST_LINK = $$PWD/Script.sh $$PWD/MultimediaService $$PWD/MultimediaServiceProxy

TARGET = MultimediaService
TEMPLATE = lib
CONFIG += staticlib

SOURCES += MultimediaService.cpp \
    DeviceWatcher/DiskScanner/DiskScanner.cpp \
    DeviceWatcher/DeviceWatcher.cpp \
    ImagePlayer/ImagePlayer.cpp \
    MusicPlayer/MusicPlayer.cpp \
    VideoPlayer/VideoPlayer.cpp \
    MultimediaServiceProxy.cpp
HEADERS += MultimediaService.h \
    DeviceWatcher/DiskScanner/DiskScanner.h \
    DeviceWatcher/DeviceWatcher.h \
    ImagePlayer/ImagePlayer.h \
    MusicPlayer/MusicPlayer.h \
    VideoPlayer/VideoPlayer.h \
    MultimediaServiceProxy.h

include(../ArkSdk.pri)
QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
