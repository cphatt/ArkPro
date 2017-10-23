#include "SettingService.h"
#include "ark_api.h"
#include "SettingPersistent.h"
#include "RunnableThread.h"
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>
#include <QThreadPool>

static const unsigned char brightnessStep(256 / 15);
static const unsigned char constrasStep(256 / 15);
static const unsigned char hueStep(256 / 15);

static void initializeRunnableCallback(void *paramater);

//OSD1_LAYER,//ui
//OSD2_LAYER,
//OSD3_LAYER,
//VIDEO_LAYER,
//VIDEO2_LAYER,

class SettingServicePrivate
{
    Q_DISABLE_COPY(SettingServicePrivate)
public:
    explicit SettingServicePrivate(SettingService* parent);
    ~SettingServicePrivate();
    void initialize();
    void connectAllSlots();
    LanguageType m_Language;
    unsigned char m_Brightness;
    unsigned char m_Contrast;
    unsigned char m_Hue;
    QTimer* m_Timer;
    QString m_Date;
    QString m_Time;
private:
    SettingService* m_Parent;
};

SettingService::SettingService(QObject *parent)
    : QObject(parent)
    , m_Private(new SettingServicePrivate(this))
{
}

SettingService::~SettingService()
{
}

void SettingService::synchronize()
{
    onTimeout();
    emit onLanguageChange(m_Private->m_Language);
//    emit onBrightnessChange(m_Private->m_Brightness / brightnessStep);
//    emit onContrastChange(m_Private->m_Contrast / constrasStep);
//    emit onHueChange(m_Private->m_Hue / hueStep);
}

void SettingService::setLanguage(const LanguageType language)
{
    if (language != m_Private->m_Language) {
        m_Private->m_Language = language;
        SettingPersistent::setLanguage(m_Private->m_Language);
    }
    qDebug() << "SettingService::setLanguage" << m_Private->m_Language;
    emit onLanguageChange(m_Private->m_Language);
}

void SettingService::setBrightness(const SettingType type, const int value)
{
    qDebug() << "SettingService::setBrightness" << type << value;
    switch (type) {
    case ST_Value: {
        m_Private->m_Brightness = value * brightnessStep;
        break;
    }
    case ST_Plus: {
        if (m_Private->m_Brightness <= (255 - brightnessStep)) {
            m_Private->m_Brightness += value * brightnessStep;
        } else {
            m_Private->m_Brightness = 255;
        }
        break;
    }
    case ST_Minus:
    default: {
        if (m_Private->m_Brightness >= brightnessStep) {
            m_Private->m_Brightness -= value * brightnessStep;
        } else {
            m_Private->m_Brightness = 0;
        }
        break;
    }
    }
#ifndef gcc
    int ret = arkapi_set_layer_brightness(OSD1_LAYER, m_Private->m_Brightness);
    qDebug() << "arkapi_set_layer_brightness" << ret << arkapi_get_layer_brightness(OSD1_LAYER);
#endif
    int tempValue = m_Private->m_Brightness / brightnessStep;
    if (value != tempValue) {
        SettingPersistent::setBrightness(tempValue);
    }
    emit onBrightnessChange(tempValue);
}

void SettingService::setContrast(const SettingType type, const int value)
{
    qDebug() << "SettingService::setContrast" << type << value;
    switch (type) {
    case ST_Value: {
        m_Private->m_Contrast = value * brightnessStep;
        break;
    }
    case ST_Plus: {
        if (m_Private->m_Contrast <= (255 - brightnessStep)) {
            m_Private->m_Contrast += value * brightnessStep;
        } else {
            m_Private->m_Contrast = 255;
        }
        break;
    }
    case ST_Minus:
    default: {
        if (m_Private->m_Contrast >= brightnessStep) {
            m_Private->m_Contrast -= value * brightnessStep;
        } else {
            m_Private->m_Contrast = 0;
        }
        break;
    }
    }
#ifndef gcc
    int ret = arkapi_set_layer_contrast(OSD1_LAYER, m_Private->m_Brightness);
    qDebug() << "arkapi_get_layer_contrast" << ret << arkapi_get_layer_contrast(OSD1_LAYER);
#endif
    int tempValue = m_Private->m_Contrast / constrasStep;
    if (value != tempValue) {
        SettingPersistent::setContrast(tempValue);
    }
    emit onContrastChange(tempValue);
}

void SettingService::setHue(const SettingType type, const int value)
{
    qDebug() << "SettingService::setHue" << type << value;
    switch (type) {
    case ST_Value: {
        m_Private->m_Hue = value * hueStep;
        break;
    }
    case ST_Plus: {
        if (m_Private->m_Hue <= (255 - hueStep)) {
            m_Private->m_Hue += value * hueStep;
        } else {
            m_Private->m_Hue = 255;
        }
        break;
    }
    case ST_Minus:
    default: {
        if (m_Private->m_Hue >= hueStep) {
            m_Private->m_Hue -= value * hueStep;
        } else {
            m_Private->m_Hue = 0;
        }
        break;
    }
    }
#ifndef gcc
    int ret = arkapi_set_layer_hue(OSD1_LAYER, m_Private->m_Brightness);
    qDebug() << "arkapi_get_layer_hue" << ret << arkapi_get_layer_hue(OSD1_LAYER);
#endif
    int tempValue = m_Private->m_Hue / constrasStep;
    if (value != tempValue) {
        SettingPersistent::setHue(tempValue);
    }
    emit onHueChange(tempValue);
}

void SettingService::test()
{
    emit onTest();
}
void SettingService::test1()
{
    emit onTest1();
    qDebug()<< "stupid";
}

void SettingService::onTimeout()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    emit onDateTimeChange(dateTime.toString(QString("yyyy-MM-dd")), dateTime.toString(QString("hh:mm")));
}

SettingServicePrivate::SettingServicePrivate(SettingService *parent)
    : m_Parent(parent)
{
    m_Timer = NULL;
    m_Language = SettingPersistent::getLanguage();
    m_Brightness = brightnessStep * SettingPersistent::getBrightness();
    m_Contrast = constrasStep * SettingPersistent::getContrast();
    m_Hue = hueStep * SettingPersistent::getHue();
    initialize();
    connectAllSlots();
    m_Timer->start(1000);
}

SettingServicePrivate::~SettingServicePrivate()
{
}

void SettingServicePrivate::initialize()
{
    m_Timer = new QTimer(m_Parent);
    qDebug() << "SettingServicePrivate::initialize" << qApp->arguments();
    if (ArkMicroSettingService == qApp->applicationName()) {
        bool ret = QDBusConnection::sessionBus().registerService(ArkMicroSettingService);
        ret = ret && QDBusConnection::sessionBus().registerObject(ArkMicroSettingPath,
                                                                  m_Parent,
                                                                  QDBusConnection::ExportNonScriptableSignals
                                                                  | QDBusConnection::ExportNonScriptableSlots);
        if (!ret) {
            qCritical() << "SettingService Register QDbus failed!";
            exit(EXIT_FAILURE);
        }
        qDebug() << "SettingService Register QDbus ok!";
    } else {
        qDebug() << "SettingService inner";
    }
    qDebug() << "maxThreadCount" << QThreadPool::globalInstance()->maxThreadCount();
    CustomRunnable* runnable = new CustomRunnable();
    runnable->setCallbackFunction(initializeRunnableCallback, this);
    QThreadPool::globalInstance()->start(runnable);
}

void SettingServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
    QObject::connect(m_Timer,  SIGNAL(timeout()),
                     m_Parent, SLOT(onTimeout()),
                     type);
}

static void initializeRunnableCallback(void *paramater)
{
    qDebug() << "initializeRunnableCallback" << paramater;
    SettingServicePrivate *ptr = static_cast<SettingServicePrivate *>(paramater);
    if (NULL != ptr) {
#ifndef gcc
        int ret = arkapi_set_layer_brightness(OSD1_LAYER, ptr->m_Brightness);
        qDebug() << "arkapi_set_layer_brightness" << ret << arkapi_get_layer_brightness(OSD1_LAYER);
#else
        qDebug() << "ptr->m_Brightness" << ptr->m_Brightness;
#endif
    }
}
