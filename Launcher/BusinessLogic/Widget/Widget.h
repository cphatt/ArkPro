#ifndef WIDGET_H
#define WIDGET_H

#include <QObject>
#include <QEvent>
#include <QRect>
#include <QScopedPointer>
#include <QCoreApplication>

namespace WidgetStatus {
static const QString RequestShow("RequestShow");
static const QString RequestHide("RequestHide");
static const QString Show("Show");
}

class WidgetPrivate;
class Widget : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Widget)
#ifdef g_Widget
#undef g_Widget
#endif
#define g_Widget (Widget::instance())
public:
    enum Type {
        T_Back = 0,
        T_Home = 1,
        T_SDDisk = 2,
        T_SDDiskMusic = 3,
        T_SDDiskImage = 4,
        T_SDDiskVideo = 5,
        T_USBDisk = 6,
        T_USBDiskMusic = 7,
        T_USBDiskImage = 8,
        T_USBDiskVideo = 9,
        T_Music = 10,
        T_Image = 11,
        T_ImageFullScreen = 12,
        T_Video = 13,
        T_VideoFullScreen = 14,
        T_Link = 15,
        T_Mirror = 16,
        T_Carplay = 17,
        T_AV1 = 18,
        T_AV1FullScreen = 19,
        T_AV2 = 20,
        T_AV2FullScreen = 21,
        T_Setting = 22,
        T_SettingGeneral = 23,
        T_SettingLanguage = 24,
        T_SettingEffect = 25,
        T_SettingField = 26,
        T_Media = 27,
        T_Carlife = 28,
        T_test
    };
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void ontWidgetTypeChange(const Widget::Type type, const QString &status) = 0;
    };
    QRect geometryFit(const int x, const int y, const int w, const int h, QWidget* widget = NULL);
    int baseWindowWidth();
    int baseWindowHeight();
    int baseStatusBarHeight();
    int baseTabBarHeight();
    float widthScalabilityFactor();
    float heightScalabilityFactor();
    void setWidgetType(const Widget::Type type, const QString &status);
    inline static Widget* instance() {
        static Widget* widget(new Widget(qApp));
        return widget;
    }
signals:
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
protected:
    void customEvent(QEvent* event);
private:
    explicit Widget(QObject *parent = NULL);
    ~Widget();
    friend class WidgetPrivate;
    QScopedPointer<WidgetPrivate> m_Private;
};

#endif // WIDGET_H
