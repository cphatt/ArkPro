include(./ArkSdk.pri)

TEMPLATE = subdirs

SUBDIRS += \
    ArkApplication \
    AutoConnect \
    RunnableThread \
    EventEngine \
    DbusService \
    Utility \
    AudioService \
    SettingPersistent \
    SettingService \
    DiskDeviceWatcher \
    MultimediaService \
    AVService \
    Launcher

