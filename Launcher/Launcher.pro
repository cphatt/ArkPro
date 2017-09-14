QT += core gui svg xml dbus

CONFIG += C++0x serialport

TEMPLATE = app

TARGET = Launcher

RESOURCES += \
    Resources.qrc

CODECFORSRC     = UTF-8

TRANSLATIONS += \
    ./Resources/Languages/Launcher_EN.ts \
    ./Resources/Languages/Launcher_CN.ts \
    ./Resources/Languages/Launcher_DE.ts \
    ./Resources/Languages/Launcher_FR.ts \
    ./Resources/Languages/Launcher_JP.ts \
    ./Resources/Languages/Launcher_KO.ts \
    ./Resources/Languages/Launcher_PO.ts \
    ./Resources/Languages/Launcher_RU.ts \
    ./Resources/Languages/Launcher_SP.ts

SOURCES += \
    main.cpp \
    BusinessLogic/Widget/Widget.cpp \
    BusinessLogic/Common/BusinessLogicUtility.cpp \
    BusinessLogic/Setting/Setting.cpp \
    BusinessLogic/Link/Link.cpp \
    BusinessLogic/Link/MirrorLinkProxy.cpp \
    BusinessLogic/Link/CarplayLinkProxy.cpp \
    UserInterface/Common/BmpButton.cpp \
    UserInterface/Common/BmpWidget.cpp \
    UserInterface/Common/ListView.cpp \
    UserInterface/Common/MessageBox.cpp \
    UserInterface/Common/Scroll.cpp \
    UserInterface/Common/ScrollBar.cpp \
    UserInterface/Common/Slider.cpp \
    UserInterface/Common/TextWidget.cpp \
    UserInterface/Common/Utility.cpp \
    UserInterface/MainWidget/HomeWidget/HomeWidget.cpp \
    UserInterface/MainWidget/IdleWidget/IdleWidget.cpp \
    UserInterface/MainWidget/LinkWidget/CarplayLinkWidget/CarplayLinkWidget.cpp \
    UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorLinkWidget.cpp \
    UserInterface/MainWidget/LinkWidget/LinkWidget.cpp \
    UserInterface/MainWidget/MessageBoxWidget/MessageBoxWidget.cpp \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageStatusWidget/ImageStatusWidget.cpp \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageToolBarWidget/ImageToolBarWidget.cpp \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageWidget.cpp \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicShortCutWidget/MusicShortCutWidget.cpp \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicWidget.cpp \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoStatusWidget/VideoStatusWidget.cpp \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoToolBarWidget/VideoToolBarWidget.cpp \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoWidget.cpp \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectWidget.cpp \
    UserInterface/MainWidget/SettingWidget/FieldWidget/FieldWidget.cpp \
    UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralWidget.cpp \
    UserInterface/MainWidget/SettingWidget/LanguageWidget/LanguageWidget.cpp \
    UserInterface/MainWidget/SettingWidget/SettingWidget.cpp \
    UserInterface/MainWidget/StatusBarWidget/StatusBarWidget.cpp \
    UserInterface/MainWidget/TabBarWidget/TabBarWidget.cpp \
    UserInterface/MainWidget/MainWidget.cpp \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskWidget.cpp \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskImageListViewWidget/USBDiskImageListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskVideoListViewWidget/USBDiskVideoListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskToolWidget/USBDiskToolWidget.cpp \
    UserInterface/MainWidget/AVWidget/AV1Widget/AV1Widget.cpp \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskWidget.cpp \
    UserInterface/MainWidget/AVWidget/AV2Widget/AV2Widget.cpp \
    UserInterface/MainWidget/DiskWidget/DiskWidget.cpp \
    UserInterface/MainWidget/AVWidget/AVWidget.cpp \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskImageListViewWidget/SDDiskImageListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskMusicListViewWidget/SDDiskMusicListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskVideoListViewWidget/SDDiskVideoListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskListViewWidget.cpp \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskToolWidget/SDDiskToolWidget.cpp \
    BusinessLogic/Audio/Audio.cpp \
    UserInterface/MainWidget/DiskWidget/ImageWidget/PixmapWidget/PixmapWidget.cpp \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageShortCutWidget/ImageShortCutWidget.cpp \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoShortCutWidget/VideoShortCutWidget.cpp \
    BusinessLogic/Setting/SettingServiceProxy.cpp \
    BusinessLogic/Multimedia/Multimedia.cpp \
    BusinessLogic/AV/AV.cpp \
    UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralListView.cpp \
    UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralSlider/GeneralSlider.cpp \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundSlider/EffectSoundSlider.cpp \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundWidget.cpp \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectToolBarWidget/EffectToolBarWidget.cpp \
    UserInterface/MainWidget/FMWidget/FMWidget.cpp \
    UserInterface/MainWidget/FMWidget/FMToolWidget/FMToolWidget.cpp \
    UserInterface/MainWidget/CalibrateWidget/CalibrateWidget.cpp \
    UserInterface/MainWidget/VolumeWidget/VolumeWidget.cpp \
    UserInterface/MainWidget/VolumeWidget/VolumeToolWidget/VolumeToolWidget.cpp \
    UserInterface/MainWidget/VolumeWidget/VolumeToolWidget/VolumeSliderWidget/VolumeSliderWidget.cpp \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicToolWidget.cpp \
    UserInterface/MainWidget/DiskWidget/MultimediaLoadingWidget.cpp \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicLoadingWidget/MusicLoadingWidget.cpp \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoLoadingWidget/VideoLoadingWidget.cpp \
    UserInterface/MainWidget/LinkWidget/CarplayLinkWidget/CarplayShortCutWidget/CarplayShortCutWidget.cpp \
    UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorShortCutWidget/MirrorShortCutWidget.cpp \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageLoadingWidget/ImageLoadingWidget.cpp \
    UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorToolWidget/MirrorToolWidget.cpp \
    UserInterface/Common/CustomListView.cpp \
    UserInterface/Common/CustomItemDelegate.cpp \
    UserInterface/Common/CustomScrollBar.cpp \
    UserInterface/MainWidget/DiskWidget/MultimediaListView.cpp \
    UserInterface/MainWidget/MediaWidget/MediaWidget.cpp \
    UserInterface/MainWidget/LinkWidget/CarlifeLinkWidget/CarlifeLinkWidget.cpp \
    BusinessLogic/Link/CarlifeLinkProxy.cpp \
    UserInterface/MainWidget/LinkWidget/CarlifeLinkWidget/CarlifeShortCutWidget/CarlifeShortCutWidget.cpp \
    BusinessLogic/Port/Port.cpp \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicInformation/MusicInformation.cpp

HEADERS += \
    BusinessLogic/Widget/Widget.h \
    BusinessLogic/Common/BusinessLogicUtility.h \
    BusinessLogic/Setting/Setting.h \
    BusinessLogic/Link/Link.h \
    BusinessLogic/Link/MirrorLinkProxy.h \
    BusinessLogic/Link/CarplayLinkProxy.h \
    UserInterface/Common/BmpButton.h \
    UserInterface/Common/BmpWidget.h \
    UserInterface/Common/ListView.h \
    UserInterface/Common/MessageBox.h \
    UserInterface/Common/Scroll.h \
    UserInterface/Common/ScrollBar.h \
    UserInterface/Common/Slider.h \
    UserInterface/Common/TextWidget.h \
    UserInterface/Common/Utility.h \
    UserInterface/MainWidget/HomeWidget/HomeWidget.h \
    UserInterface/MainWidget/IdleWidget/IdleWidget.h \
    UserInterface/MainWidget/LinkWidget/CarplayLinkWidget/CarplayLinkWidget.h \
    UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorLinkWidget.h \
    UserInterface/MainWidget/LinkWidget/LinkWidget.h \
    UserInterface/MainWidget/MessageBoxWidget/MessageBoxWidget.h \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageStatusWidget/ImageStatusWidget.h \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageToolBarWidget/ImageToolBarWidget.h \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageWidget.h \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicShortCutWidget/MusicShortCutWidget.h \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicWidget.h \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoStatusWidget/VideoStatusWidget.h \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoToolBarWidget/VideoToolBarWidget.h \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoWidget.h \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectWidget.h \
    UserInterface/MainWidget/SettingWidget/FieldWidget/FieldWidget.h \
    UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralWidget.h \
    UserInterface/MainWidget/SettingWidget/LanguageWidget/LanguageWidget.h \
    UserInterface/MainWidget/SettingWidget/SettingWidget.h \
    UserInterface/MainWidget/StatusBarWidget/StatusBarWidget.h \
    UserInterface/MainWidget/TabBarWidget/TabBarWidget.h \
    UserInterface/MainWidget/MainWidget.h \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskWidget.h \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskMusicListViewWidget/USBDiskMusicListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskImageListViewWidget/USBDiskImageListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskVideoListViewWidget/USBDiskVideoListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskListViewWidget/USBDiskListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/USBDiskWidget/USBDiskToolWidget/USBDiskToolWidget.h \
    UserInterface/MainWidget/AVWidget/AV1Widget/AV1Widget.h \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskWidget.h \
    UserInterface/MainWidget/AVWidget/AV2Widget/AV2Widget.h \
    UserInterface/MainWidget/DiskWidget/DiskWidget.h \
    UserInterface/MainWidget/AVWidget/AVWidget.h \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskImageListViewWidget/SDDiskImageListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskMusicListViewWidget/SDDiskMusicListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskVideoListViewWidget/SDDiskVideoListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskListViewWidget/SDDiskListViewWidget.h \
    UserInterface/MainWidget/DiskWidget/SDDiskWidget/SDDiskToolWidget/SDDiskToolWidget.h \
    BusinessLogic/Audio/Audio.h \
    UserInterface/MainWidget/DiskWidget/ImageWidget/PixmapWidget/PixmapWidget.h \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageShortCutWidget/ImageShortCutWidget.h \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoShortCutWidget/VideoShortCutWidget.h \
    BusinessLogic/Setting/SettingServiceProxy.h \
    BusinessLogic/Multimedia/Multimedia.h \
    BusinessLogic/AV/AV.h \
    UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralListView.h \
    UserInterface/MainWidget/SettingWidget/GeneralWidget/GeneralListView/GeneralSlider/GeneralSlider.h \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundSlider/EffectSoundSlider.h \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectSoundWidget/EffectSoundWidget.h \
    UserInterface/MainWidget/SettingWidget/EffectWidget/EffectToolBarWidget/EffectToolBarWidget.h \
    UserInterface/MainWidget/FMWidget/FMWidget.h \
    UserInterface/MainWidget/FMWidget/FMToolWidget/FMToolWidget.h \
    UserInterface/MainWidget/CalibrateWidget/CalibrateWidget.h \
    UserInterface/MainWidget/VolumeWidget/VolumeWidget.h \
    UserInterface/MainWidget/VolumeWidget/VolumeToolWidget/VolumeToolWidget.h \
    UserInterface/MainWidget/VolumeWidget/VolumeToolWidget/VolumeSliderWidget/VolumeSliderWidget.h \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicToolWidget.h \
    UserInterface/MainWidget/DiskWidget/MultimediaLoadingWidget.h \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicLoadingWidget/MusicLoadingWidget.h \
    UserInterface/MainWidget/DiskWidget/VideoWidget/VideoLoadingWidget/VideoLoadingWidget.h \
    UserInterface/MainWidget/LinkWidget/CarplayLinkWidget/CarplayShortCutWidget/CarplayShortCutWidget.h \
    UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorShortCutWidget/MirrorShortCutWidget.h \
    UserInterface/MainWidget/DiskWidget/ImageWidget/ImageLoadingWidget/ImageLoadingWidget.h \
    UserInterface/MainWidget/LinkWidget/MirrorLinkWidget/MirrorToolWidget/MirrorToolWidget.h \
    UserInterface/Common/CustomListView.h \
    UserInterface/Common/CustomItemDelegate.h \
    UserInterface/Common/CustomScrollBar.h \
    UserInterface/MainWidget/DiskWidget/MultimediaListView.h \
    UserInterface/MainWidget/MediaWidget/MediaWidget.h \
    UserInterface/MainWidget/LinkWidget/CarlifeLinkWidget/CarlifeLinkWidget.h \
    BusinessLogic/Link/CarlifeLinkProxy.h \
    UserInterface/MainWidget/LinkWidget/CarlifeLinkWidget/CarlifeShortCutWidget/CarlifeShortCutWidget.h \
    BusinessLogic/Port/Port.h \
    UserInterface/MainWidget/DiskWidget/MusicWidget/MusicToolWidget/MusicInformation/MusicInformation.h

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

include(../ArkSdk.pri)

unix:!macx: LIBS += -L$$PWD/TagLib/Library/arm -ltag
unix:!macx: LIBS += -L$$PWD/TagLib/Library/arm -lConvert
unix:!macx: LIBS += -L$$PWD/TagLib/Library/arm -lQtConvert

unix:!macx: LIBS += -L$$SDKPATH/Package/ArkApplication/$$ARCHITECTURE -lArkApplication
unix:!macx: LIBS += -L$$SDKPATH/Package/AutoConnect/$$ARCHITECTURE -lAutoConnect
unix:!macx: LIBS += -L$$SDKPATH/Package/RunnableThread/$$ARCHITECTURE -lRunnableThread
unix:!macx: LIBS += -L$$SDKPATH/Package/Utility/$$ARCHITECTURE -lUtility
unix:!macx: LIBS += -L$$SDKPATH/Package/DiskDeviceWatcher/$$ARCHITECTURE -lDiskDeviceWatcher
unix:!macx: LIBS += -L$$SDKPATH/Package/EventEngine/$$ARCHITECTURE -lEventEngine
unix:!macx: LIBS += -L$$SDKPATH/Package/SettingService/$$ARCHITECTURE -lSettingService
unix:!macx: LIBS += -L$$SDKPATH/Package/SettingPersistent/$$ARCHITECTURE -lSettingPersistent
unix:!macx: LIBS += -L$$SDKPATH/Package/AVService/$$ARCHITECTURE -lAVService
if (contains(DEFINES, $$COMPILER)) {
} else {
unix:!macx: LIBS += -lz
}

ARKAPPLICATION = $$SDKPATH/ArkApplication
INCLUDEPATH += $$ARKAPPLICATION
DEPENDPATH += $$ARKAPPLICATION

EVENENGINE = $$SDKPATH/EventEngine
INCLUDEPATH += $$EVENENGINE
DEPENDPATH += $$EVENENGINE

DISKDEVICEWATCHER = $$SDKPATH/DiskDeviceWatcher
INCLUDEPATH += $$DISKDEVICEWATCHER
DEPENDPATH += $$DISKDEVICEWATCHER

AUTOCONNECT = $$SDKPATH/AutoConnect
INCLUDEPATH += $$AUTOCONNECT
DEPENDPATH += $$AUTOCONNECT

RUNNABLETHREAD = $$SDKPATH/RunnableThread
INCLUDEPATH += $$RUNNABLETHREAD
DEPENDPATH += $$RUNNABLETHREAD

UTILITY = $$SDKPATH/Utility
INCLUDEPATH += $$UTILITY
DEPENDPATH += $$UTILITY

SETTINGPERSISTENT = $$SDKPATH/SettingPersistent
INCLUDEPATH += $$SETTINGPERSISTENT
DEPENDPATH += $$SETTINGPERSISTENT

SETTINGSERVICE = $$SDKPATH/SettingService
INCLUDEPATH += $$SETTINGSERVICE
DEPENDPATH += $$SETTINGSERVICE

DISTFILES += \
    Resources/Images/HomeWidgetAUXNormal.png \
    Resources/Images/HomeWidgetAUXPress.png \
    Resources/Images/MusicSliderBlock.png

