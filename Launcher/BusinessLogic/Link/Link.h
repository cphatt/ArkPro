#ifndef LINK_H
#define LINK_H

#include "DbusService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

typedef enum
{
    CARPLAY = 0X00,
    CARLIFE,
    ANDROID_MIRROR
}Link_Type;

#define Link_Type int

enum TouchType {
    TouchBegin = 0x01,
    TouchUpdate = 0x02,
    TouchEnd = 0x03,
};
#define TouchType int

struct TouchEvent
{
    enum TouchPointState {
        TouchPointPressed    = 0x01,
        TouchPointMoved      = 0x02,
        TouchPointStationary = 0x04,
        TouchPointReleased   = 0x08,
    };
    TouchEvent(){}
    explicit TouchEvent(TouchEvent::TouchPointState state, int x, int y)
        : state(state)
        , y(y)
        , x(x) {}
    ~TouchEvent() {}
    int x;
    int y;
    TouchEvent::TouchPointState state;
};

typedef enum
{
   HOME_KEY = 0x01,
   MENU_KEY,
   BACK_KEY,
}LinkKeyValue;
#define LinkKeyValue int

typedef enum
{
    LINK_UNSUPPORTED=0XFF,
    LINK_CONNECTED = 0x01,
    LINK_DISCONNECTED,
    LINK_STARTING,
    LINK_SUCCESS,
    LINK_FAIL,
    LINK_EXITING,
    LINK_EXITED,
    LINK_START_PROCESS,
}Link_STATUS;
#define Link_STATUS int

class LinkPrivate;
class Link
        : public QObject
        , protected DbusService::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(Link)
#ifdef g_Link
#undef g_Link
#endif
#define g_Link (Link::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onLinkStatusChange(const int type, const int status);
        //  virtual void onLinkStatusChange(const Link_Type type, const Link_STATUS status);
    };
    inline static Link* instance() {
        static Link* link(new Link(qApp));
        return link;
    }
    void requestLinkStatus(const int type, const int status);
    //  void requestLinkStatus(const Link_Type type, const Link_STATUS status);

    void requestTouchStatus(const int deviceType, const int touchType, const QString &touchPointXml);
//    void requestTouchStatus(const Link_Type , cdeviceTypeonst TouchType touchType, const QString &touchPointXml);
    void requestKeyValue(const int type);
//    void requestKeyValue(const KeyValue type);

signals:
    void onLinkStatusChange(const int type, const int status);
    //  void onLinkStatusChange(const Link_Type type, const Link_STATUS status);
private slots:
    void onServiceRegistered(const QString& service);
    void onServiceUnregistered(const QString& service);
    void linkStatusChange(const int type, const int status);
private:
    explicit Link(QObject *parent = NULL);
    ~Link();
    void initializePrivate();
    friend class LinkPrivate;
    QScopedPointer<LinkPrivate> m_Private;
};

#endif // LINK_H
