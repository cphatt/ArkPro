#include "EventEngine.h"
#include <QList>

//namespace CustomEventType {
//static const QEvent::Type demoEvent = static_cast<QEvent::Type>(QEvent::registerEventType(QEvent::User));
//}
//if (CustomEventType::demoEvent == event->type()) {
//    QWidget* temp  = reinterpret_cast<EventEngine::CustomEvent<QVariant>*>(event)->m_Data->value<QWidget*>();
//    if (NULL != temp) {
//        temp->hide();
//    }
//}
//g_EventEngine->attachCustomEvent(this);
//QVariant* variant = new QVariant;
//variant->setValue((QWidget*)this);
////    EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::demoEvent), variant);
////    g_EventEngine->sendCustomEvent(event);
////    EventEngine::CustomEvent<QVariant> event(static_cast<QEvent::Type>(CustomEventType::demoEvent), variant);
//g_EventEngine->postCustomEvent(EventEngine::CustomEvent<QVariant>(CustomEventType::demoEvent, variant));

class EventEnginePrivate
{
    Q_DISABLE_COPY(EventEnginePrivate)
public:
    explicit EventEnginePrivate(EventEngine* parent);
    ~EventEnginePrivate();
    EventEngine* m_Parent;
    QList<QObject*> m_AttachList;
};

void EventEngine::attachCustomEvent(QObject *receive)
{
    if (NULL != receive) {
        if (!m_Private->m_AttachList.contains(receive)) {
            m_Private->m_AttachList.append(receive);
        }
    }
}

void EventEngine::detachCustomEvent(QObject *receive)
{
    if (NULL != receive) {
        if (m_Private->m_AttachList.contains(receive)) {
            m_Private->m_AttachList.removeOne(receive);
        }
    }
}

int EventEngine::attachObjectSize()
{
    m_Private->m_AttachList.size();
}

QObject *EventEngine::objectAt(const int index)
{
    if (index < attachObjectSize()) {
        return m_Private->m_AttachList.at(index);
    } else {
        qDebug() << "out of EventEngine::objectAt() index!";
        return NULL;
    }
}

void EventEngine::sendCustomEvent(QEvent& event)
{
    for (int i = 0; i < m_Private->m_AttachList.size(); ++i) {
        if (NULL != m_Private->m_AttachList.at(i)) {
            QCoreApplication::sendEvent(m_Private->m_AttachList.at(i), &event);
        }
    }
}

EventEngine::EventEngine()
    : m_Private(new EventEnginePrivate(this))
{
}

EventEngine::~EventEngine()
{
}

EventEnginePrivate::EventEnginePrivate(EventEngine *parent)
    : m_Parent(parent)
{
    m_AttachList.clear();
}

EventEnginePrivate::~EventEnginePrivate()
{
    m_AttachList.clear();
}
