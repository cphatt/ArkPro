#ifndef AVENGINE_H
#define AVENGINE_H

#include <QObject>
#include <QSharedPointer>

class AVEnginePrivate;
class AVEngine : protected QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AVEngine)
#ifdef g_AVEngine
#undef g_AVEngine
#endif
#define g_AVEngine (AVEngine::instance())
public:
    enum AVType {
        AVT_Audio = 0,
        AVT_Video = 1,
    };
    enum AVStatus {
        AVS_Stop = 0,
        AVS_Play = 1,
        AVS_Pause = 2,
    };
    class Interface {
        Q_DISABLE_COPY(Interface)
    protected:
        Interface() {}
        virtual ~Interface() {}
        virtual void onAVEngineOutPut(const QString &output,  const AVEngine::AVType type) = 0;
    };
    inline static AVEngine* instance() {
        static AVEngine avEngine;
        return &avEngine;
    }
    void playAVFile(const QString &path);
    void playControl(const AVEngine::AVStatus status);
    void seekToMillesimal(const int millesimal);
signals:
    void onAVEngineOutPut(const QString &output, const AVEngine::AVType type);
private slots:
    void onMplayerOutput();
    void onTimeout();
private:
    explicit AVEngine(QObject *parent = NULL);
    ~AVEngine();
    friend class AVEnginePrivate;
    QSharedPointer<AVEnginePrivate> m_Private;
};

#endif // AVENGINE_H
