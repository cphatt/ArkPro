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

TAGLIB = $$PWD/TagLib/Header
INCLUDEPATH += $$TAGLIB
DEPENDPATH += $$TAGLIB
INCLUDEPATH += $$TAGLIB/toolkit
DEPENDPATH += $$TAGLIB/toolkit
INCLUDEPATH += $$TAGLIB/flac
DEPENDPATH += $$TAGLIB/flac
INCLUDEPATH += $$TAGLIB/ape
DEPENDPATH += $$TAGLIB/ape
INCLUDEPATH += $$TAGLIB/mpeg
DEPENDPATH += $$TAGLIB/mpeg
INCLUDEPATH += $$TAGLIB/mpeg/id3v1
DEPENDPATH += $$TAGLIB/mpeg/id3v1
INCLUDEPATH += $$TAGLIB/mpeg/id3v2
DEPENDPATH += $$TAGLIB/mpeg/id3v2
INCLUDEPATH += $$TAGLIB/mpeg/id3v2/frames
DEPENDPATH += $$TAGLIB/mpeg/id3v2/frames
INCLUDEPATH += $$TAGLIB/ogg
DEPENDPATH += $$TAGLIB/ogg
INCLUDEPATH += $$TAGLIB/ogg/flac
DEPENDPATH += $$TAGLIB/ogg/flac
INCLUDEPATH += $$TAGLIB/ogg/opus
DEPENDPATH += $$TAGLIB/ogg/opus
INCLUDEPATH += $$TAGLIB/ogg/speex
DEPENDPATH += $$TAGLIB/ogg/speex
INCLUDEPATH += $$TAGLIB/ogg/vorbis
DEPENDPATH += $$TAGLIB/ogg/vorbis
INCLUDEPATH += $$TAGLIB/mp4
DEPENDPATH += $$TAGLIB/mp4

unix:!macx: LIBS += -L$$PWD/TagLib/Library/arm -ltag
unix:!macx: LIBS += -L$$PWD/TagLib/Library/arm -lConvert
unix:!macx: LIBS += -L$$PWD/TagLib/Library/arm -lQtConvert
include(../ArkSdk.pri)
QMAKE_POST_LINK = rm -f $$SDKPATH/Package/Launcher/$$ARCHITECTURE/Launcher
