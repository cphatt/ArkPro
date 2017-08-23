#ifndef CUSTOMEVENT_H
#define CUSTOMEVENT_H

#include <QEvent>
#include <QDebug>
#include <QCoreApplication>
#include <QScopedPointer>

class EventEnginePrivate;
class EventEngine
{
    Q_DISABLE_COPY(EventEngine)
#ifdef g_EventEngine
#undef g_EventEngine
#endif
#define g_EventEngine (EventEngine::instance())
public:
    inline static EventEngine* instance() {
        static EventEngine eventEngine;
        return &eventEngine;
    }
    template <class T>
    class CustomEvent : public QEvent {
    public:
        explicit CustomEvent(const QEvent::Type type, T* data = NULL)
            : QEvent(type)
            , m_Data(data) {
        }
        ~CustomEvent() {
            if (NULL != m_Data) {
                delete m_Data;
                m_Data = NULL;
            }
        }
        explicit CustomEvent(const CustomEvent& customEvent)
            : QEvent(customEvent.type())
            , m_Data(NULL) {
            if (NULL != customEvent.m_Data) {
                m_Data = new T(*customEvent.m_Data);
            }
        }
        CustomEvent& operator =(const CustomEvent& customEvent) {
            if (this == &customEvent) {
                return *this;
            } else {
                if (NULL != m_Data) {
                    delete m_Data;
                    m_Data = NULL;
                }
                if (NULL != customEvent.m_Data) {
                    m_Data = new T(*customEvent.m_Data);
                }
                return *this;
            }
        }
        T* m_Data;
    };
    void attachCustomEvent(QObject* receive);
    void detachCustomEvent(QObject* receive);
    void sendCustomEvent(QEvent& event);
    template <class T>
    void postCustomEvent(EventEngine::CustomEvent<T>& event, const Qt::EventPriority priority = Qt::NormalEventPriority) {
        for (int i = 0; i < attachObjectSize(); ++i) {
            if (NULL != objectAt(i)) {
                EventEngine::CustomEvent<T>* temp = new EventEngine::CustomEvent<T>(event);
                QCoreApplication::postEvent(objectAt(i), temp, priority);
            }
        }
    }
private:
    int attachObjectSize();
    QObject* objectAt(const int index);
    EventEngine();
    ~EventEngine();
    friend class EventEnginePrivate;
    QScopedPointer<EventEnginePrivate> m_Private;
};

#endif // CUSTOMEVENT_H
