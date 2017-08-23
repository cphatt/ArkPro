#ifndef AV_H
#define AV_H

#include "AVService.h"
#include <QObject>
#include <QScopedPointer>
#include <QCoreApplication>

class AVPrivate;
class AV
        : public QObject
        , protected AVService::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(AV)
#ifdef g_AV
#undef g_AV
#endif
#define g_AV (AV::instance())
public:
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onAVStatus(const int type, const int status) = 0;
        //    void onStartAV(const AVType type, const AVStatus status);
    };
    inline static AV* instance() {
        static AV* av(new AV(qApp));
        return av;
    }
public slots:
    void startAV(const int type, const int width, const int height);
    //    void startAV(const AVType type, const int width, const int height);
    void stopAV(const int type);
    //    void stopAV(const AVType type);
signals:
    void onAVStatus(const int type, const int status);
    //    void onStartAV(const AVType type, const AVStatus status);
private:
    explicit AV(QObject *parent = NULL);
    ~AV();
    friend class AVPrivate;
    QScopedPointer<AVPrivate> m_Private;
};

#endif // AV_H
