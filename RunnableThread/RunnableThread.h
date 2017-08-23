#ifndef RUNNABLETHREAD_H
#define RUNNABLETHREAD_H

#ifndef CUSTOMRUNNABLE_H
#define CUSTOMRUNNABLE_H

#include <QRunnable>
#include <QScopedPointer>

class CustomRunnablePrivate;
class CustomRunnable : public QRunnable
{
    Q_DISABLE_COPY(CustomRunnable)
public:
    CustomRunnable();
    ~CustomRunnable();
    void setCallbackFunction(void (*callback)(void *), void *parameter);
protected:
    void run();
private:
    friend class CustomRunnablePrivate;
    QScopedPointer<CustomRunnablePrivate> m_Private;
};

#endif // CUSTOMRUNNABLE_H

#ifndef CUSTOMTHREAD_H
#define CUSTOMTHREAD_H

#include <QThread>
#include <QScopedPointer>

class CustomThreadPrivate;
class CustomThread : public QThread
{
    Q_DISABLE_COPY(CustomThread)
public:
    explicit CustomThread(QObject *parent = NULL);
    ~CustomThread();
    void setCallbackFunction(void (*callback)(void *), void *parameter);
    void setEventLoop(const bool exec);
protected:
    void run();
private:
    friend class CustomThreadPrivate;
    QScopedPointer<CustomThreadPrivate> m_Private;
};

#endif // CUSTOMTHREAD_H

#endif // RUNNABLETHREAD_H
