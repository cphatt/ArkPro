#include "AV.h"
#include "AutoConnect.h"
#include <QDebug>

class AVPrivate
{
public:
    explicit AVPrivate(AV* parent);
    ~AVPrivate();
    void initialize();
    void connectAllSlots();
    AVService* m_AVService;
private:
    AV* m_Parent;
};

void AV::startAV(const AVType type, const int width, const int height)
{
    m_Private->m_AVService->startAV(type, width, height);
}

void AV::stopAV(const AVType type)
{
    m_Private->m_AVService->stopAV(type);
}

AV::AV(QObject *parent)
    : QObject(parent)
    , AVService::Interface()
    , m_Private(new AVPrivate(this))
{
    qDebug() << "AV::AV";
}

AV::~AV()
{
    qDebug() << "AV::~AV";
}

AVPrivate::AVPrivate(AV *parent)
    : m_Parent(parent)
{
    m_AVService = NULL;
    initialize();
    connectAllSlots();
}

AVPrivate::~AVPrivate()
{
}

void AVPrivate::initialize()
{
    m_AVService = new AVService(m_Parent);
}

void AVPrivate::connectAllSlots()
{
    connectSignalAndSignalByNamesake(m_AVService, m_Parent);
}
