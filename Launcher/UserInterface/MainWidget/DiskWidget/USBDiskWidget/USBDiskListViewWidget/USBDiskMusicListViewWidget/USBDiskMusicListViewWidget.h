#ifndef USBDISKMUSICLISTVIEWWIDGET_H
#define USBDISKMUSICLISTVIEWWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class USBDiskMusicListViewWidgetPrivate;
class USBDiskMusicListViewWidget
        : protected QWidget
        , protected Widget::Interface
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(USBDiskMusicListViewWidget)
public:
    explicit USBDiskMusicListViewWidget(QWidget *parent = 0);
    ~USBDiskMusicListViewWidget();
protected:
    void showEvent(QShowEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void customEvent(QEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
    //Multimedia::Interface
    void onDeviceWatcherStatus(const int type, const int status);
    //        void onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status);
    void onMusicPlayerFileNames(const int type, const QString &xml);
    void onMusicPlayerPlayStatus(const int status);
    //    void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerID3TagChange(const int type,
                                   const int index,
                                   const QString &fileName,
                                   const int endTime);
private slots:
    void onMusicListViewItemRelease(const int index);
    void onToolButtonRelease();
    void onTimeOut();
private:
    friend class USBDiskMusicListViewWidgetPrivate;
    QScopedPointer<USBDiskMusicListViewWidgetPrivate> m_Private;
};

#endif // USBDISKMUSICLISTVIEWWIDGET_H
