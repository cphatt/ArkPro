#ifndef DBUSSERVER_H
#define DBUSSERVER_H

#include <QObject>
#include <QTimer>
#include "icarplayer.h"
#include "protocolmanager.h"
#include "carplay.h"
#define ArkMicroLinkService     "com.arkmicro.mirror"
#define ArkMicroLinkPath        "/com/arkmicro/mirror"
#define ArkMicroLinkInterface   "Local.DbusServer.Mirror"

//Signals
//#define ArkMicroLinkSignals     "arkLinkProtocolSignal"

typedef enum
{
    EV_UNSUPPORTED=0XFF,
    EV_DOWN = 0x01,
    EV_UP,
    EV_MOVE ,
    EV_MULTIMOVE,
}TouchStatus;
#define TouchStatus int


typedef enum
{
   HOME_KEY = 0x01,
   MENU_KEY,
   BACK_KEY,
}KeyValue;
#define KeyValue int

typedef enum
{
    CARPLAY = 0X00,
    APPLE_CARLIFE,
    ANDROID_CARLIFE,
    ANDROID_MIRROR
}Link_Type;
#define Link_Type int

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


enum AudioSource {
    AS_Idle = 0,
    AS_Music = 1,
    AS_Video = 2,
    AS_Mirror = 3,
    AS_Carplay = 4,
    AS_AV1 = 5,
    AS_AV2 = 6,
};
#define AudioSource int

class DbusServer : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DbusServer)
    Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Mirror")
#define g_Link (DbusServer::instance())
public:
    explicit DbusServer(QObject *parent = NULL);
    ~DbusServer();
    inline static DbusServer& instance() {
        static DbusServer dbusServer;
        return dbusServer;
    }
    void initialize();
    void set_player(ICarPlayer *player);

    void sendLinkStatus(const Link_Type type, const Link_STATUS status);

    void sendTouchEvent(TouchStatus type, int x_src, int y_src, int x_dst, int y_dst);

    bool requestAudioSource(const AudioSource source);

    ICarPlayer *m_player;
    QTimer* m_Timer;
    int m_src_x;
    int m_src_y;

    bool m_bInit;

public slots:
    void onExitSignal();
private slots:
     void onTimeout();
signals:
    void onLinkStatusChange(const int type, const int status);
//  void onTouchStatusChange(int type, int x_src, int y_src, int x_dst, int y_dst);
//  void onTouchStatusChange(TouchStatus type, int x_src, int y_src, int x_dst, int y_dst);

public slots:
    void releaseAudioSource(const int source);
//  void releaseAudioSource(const AudioSource source);

    void requestLinkStatus(const int type, const int status);

    void requestTouchStatus(int type, int x_src, int y_src, int x_dst, int y_dst);

    void requestKeyValue(int type);

};

#endif // DBUSSERVER_H
