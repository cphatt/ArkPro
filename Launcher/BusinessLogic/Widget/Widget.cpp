#include "Widget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "EventEngine.h"
#include "ArkApplication.h"
#include <QDesktopWidget>
#include <QDebug>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <unistd.h>

class WidgetPrivate
{
    Q_DISABLE_COPY(WidgetPrivate)
public:
    explicit WidgetPrivate(Widget* parent);
    ~WidgetPrivate();
    void initialize();
    void receiveAllCustomEvent();
    Widget::Type M_Type;
    int m_BaseWindowWidth;
    float m_WidthScalabilityFactor;
    int m_BaseWindowHeight;
    float m_HeightScalabilityFactor;
    int m_BaseStatusBarHeight;
    int m_BaseTabBarHeight;
private:
    Widget* m_Parent;
};

QRect Widget::geometryFit(const int x, const int y, const int w, const int h, QWidget *widget)
{
    int ax = x * m_Private->m_WidthScalabilityFactor;
    int ay = y * m_Private->m_HeightScalabilityFactor;
    int aw = w * m_Private->m_WidthScalabilityFactor;
    int ah = h * m_Private->m_HeightScalabilityFactor;
    if (NULL != widget) {
        widget->setGeometry(ax, ay, aw, ah);
    }
    QRect rect(ax, ay, aw, ah);
    return rect;
}

int Widget::baseWindowWidth()
{
    return m_Private->m_BaseWindowWidth;
}

int Widget::baseWindowHeight()
{
    return m_Private->m_BaseWindowHeight;
}

int Widget::baseStatusBarHeight()
{
    return m_Private->m_BaseStatusBarHeight;
}

int Widget::baseTabBarHeight()
{
    return m_Private->m_BaseTabBarHeight;
}

float Widget::widthScalabilityFactor()
{
    return m_Private->m_WidthScalabilityFactor;
}

float Widget::heightScalabilityFactor()
{
    return m_Private->m_HeightScalabilityFactor;
}

void Widget::setWidgetType(const Widget::Type type, const QString &status)
{
    if (type != m_Private->M_Type) {
        m_Private->M_Type = type;
    }
    emit ontWidgetTypeChange(m_Private->M_Type, status);
}

void Widget::customEvent(QEvent* event)
{
    switch (event->type()) {
    case CustomEventType::MainWidgetConstructor: {
        g_EventEngine->detachCustomEvent(this);
        emit ontWidgetTypeChange(m_Private->M_Type, WidgetStatus::Show);
        break;
    }
    default: {
        break;
    }
    }
    QObject::customEvent(event);
}

Widget::Widget(QObject *parent)
    : QObject(parent)
    , m_Private(new WidgetPrivate(this))
{
}

Widget::~Widget()
{
    qDebug() << "Widget::~Widget";
}

WidgetPrivate::WidgetPrivate(Widget* parent)
    : m_Parent(parent)
{
    M_Type = Widget::T_Home;
    m_BaseWindowWidth = 800;
    m_BaseWindowHeight = 480;
//        m_BaseWindowWidth = 1280;
//        m_BaseWindowHeight = 720;
    m_WidthScalabilityFactor = 1.0f;
    m_HeightScalabilityFactor = 1.0f;
    m_BaseStatusBarHeight = 51;
    m_BaseTabBarHeight = 71;
    initialize();
    receiveAllCustomEvent();
}

WidgetPrivate::~WidgetPrivate()
{
}

void WidgetPrivate::initialize()
{
    QDesktopWidget* dekstopWidget = ArkApplication::desktop();
    int windowWidth(800);
    int windowHeight(480);
//    int windowWidth(1280);
//    int windowHeight(720);
    if (NULL != dekstopWidget) {
#ifndef gcc
        windowWidth = dekstopWidget->width();
        windowHeight = dekstopWidget->height();
#else
//        windowWidth = 800;
//        windowHeight = 480;
#endif
        qDebug() << "dekstopWidget" << windowWidth << windowHeight;
    } else {
#ifndef gcc
        int fd = open("/dev/fb0", O_RDONLY);
        if (fd) {
            struct fb_var_screeninfo fb_var;
            if (-1 != ioctl(fd, FBIOGET_VSCREENINFO, &fb_var)) {
                windowWidth = fb_var.xres;
                windowHeight = fb_var.yres;
                close(fd);
            }
        }
#endif
    }
    m_WidthScalabilityFactor = windowWidth / static_cast<float>(m_BaseWindowWidth);
    m_HeightScalabilityFactor = windowHeight / static_cast<float>(m_BaseWindowHeight);
    qDebug() << "m_WidthScalabilityFactor" << m_WidthScalabilityFactor;
    qDebug() << "m_HeightScalabilityFactor" << m_HeightScalabilityFactor;
}

void WidgetPrivate::receiveAllCustomEvent()
{
    g_EventEngine->attachCustomEvent(m_Parent);
}
