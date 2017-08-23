#include "MainWidget.h"
#include "UserInterface/Common/Utility.h"
#include "StatusBarWidget/StatusBarWidget.h"
#include "UserInterface/Common/MessageBox.h"
#include "UserInterface/MainWidget/HomeWidget/HomeWidget.h"
#include "UserInterface/MainWidget/DiskWidget/DiskWidget.h"
#include "UserInterface/MainWidget/MediaWidget/MediaWidget.h"
#include "BusinessLogic/Common/BusinessLogicUtility.h"
#include "LinkWidget/LinkWidget.h"
#include "SettingWidget/SettingWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include "TabBarWidget/TabBarWidget.h"
#include "IdleWidget/IdleWidget.h"
#include "MessageBoxWidget/MessageBoxWidget.h"
#include "AVWidget/AVWidget.h"
#include "EventEngine.h"
#include "ArkApplication.h"
#include "AudioService.h"
#include "FMWidget/FMWidget.h"
#include "VolumeWidget/VolumeWidget.h"
//#include "CalibrateWidget/CalibrateWidget.h"
#include <QDBusConnection>
#include <QEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QWSServer>
#include <QWSCalibratedMouseHandler>
#include <QDomDocument>
#include <QSettings>

class MainWidgetPrivate
{
    Q_DISABLE_COPY(MainWidgetPrivate)
public:
    explicit MainWidgetPrivate(MainWidget *parent);
    ~MainWidgetPrivate();
    void initialize();
    void connectAllSlots();
    //    CalibrateWidget* m_CalibrateWidget;
    HomeWidget* m_HomeWidget;
    DiskWidget* m_DiskWidget;
    LinkWidget* m_LinkWidget;
    SettingWidget* m_SettingWidget;
    MediaWidget* m_MediaWidget;
   // AVWidget* m_AVWidget;
    StatusBarWidget* m_StatusBarWidget;
    TabBarWidget* m_TabBarWidget;
    FMWidget* m_FMWidget;
    VolumeWidget* m_VolumeWidget;
    MessageBoxWidget* m_MessageBoxWidget;
    IdleWidget* m_IdleWidget;
private:
    MainWidget* m_Parent;
};

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , Widget::Interface()
    , m_Private(new MainWidgetPrivate(this))
{
}

MainWidget::~MainWidget()
{
    qDebug() << "MainWidget::~MainWidget";
}

bool MainWidget::event(QEvent* event)
{
    //    qDebug() << "MainWidget::event" << event->type();
    if (!qApp->arguments().contains(QString("-calibrate"))) {
        switch (event->type()) {
        case QEvent::ShowToParent: {
            static bool flag(false);
            if (!flag) {
                flag = true;
                EventEngine::CustomEvent<void*> event(static_cast<QEvent::Type>(CustomEventType::MainWidgetConstructor), NULL);
                g_EventEngine->postCustomEvent(event);
            }
            break;
        }
        case QEvent::WindowActivate: {
            static bool flag(false);
            if (!flag) {
                flag = true;
#ifndef gcc
                if (0 == system(QString("echo 23 > /proc/display").toLocal8Bit().constData())) {
                    qDebug() << "Hide startup logo!";
                }
                QSettings setting(QString("/data/Launcher.ini"), QSettings::IniFormat, qApp);
#else
                QSettings setting(QString("/tmp/Launcher.ini"), QSettings::IniFormat, qApp);
#endif
                if (QString(qgetenv("QWS_ARK_MT_DEVICE").data()).isEmpty()) {
                    if (!setting.contains(QString("Launcher"))) {
                        qDebug() << "";
                        setting.setValue(QString("Launcher"), QVariant(bool(true)));
                        setting.sync();
#ifndef gcc
                        system("ts_calibrate");
                        //system("reboot");
#endif
                        exit(EXIT_SUCCESS);
                    }
                }
                bool ret = QDBusConnection::sessionBus().registerService(qApp->applicationName());
                if (!ret) {
                    qCritical() << "LauncherService Register QDbus failed!";
                    exit(EXIT_FAILURE);
                }
                qDebug() << "LauncherService Register QDbus ok!";
                m_Private->m_FMWidget = new FMWidget(this);
                m_Private->m_VolumeWidget = new VolumeWidget(this);
                m_Private->m_MessageBoxWidget = new MessageBoxWidget(this);
                //    m_CalibrateWidget = new CalibrateWidget(m_Parent);
                m_Private->m_IdleWidget = new IdleWidget(this);
                EventEngine::CustomEvent<int> event(static_cast<QEvent::Type>(CustomEventType::MainWidgetShow), NULL);
                g_EventEngine->postCustomEvent(event, Qt::HighEventPriority);
                Utility::elapsed(__func__);
            }
        }
            break;
        default: {
            break;
        }
        }
    }
    return QWidget::event(event);
}

void MainWidget::resizeEvent(QResizeEvent* event)
{
    move(0 * g_Widget->widthScalabilityFactor(), 0 * g_Widget->baseWindowHeight());
    setFixedSize(g_Widget->baseWindowWidth() * g_Widget->widthScalabilityFactor(), g_Widget->baseWindowHeight() * g_Widget->heightScalabilityFactor());
    QWidget::resizeEvent(event);
}

void MainWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QBrush(Utility::mainWidgetBackgroundColor()));
    QWidget::paintEvent(event);
}

void MainWidget::timerEvent(QTimerEvent *event)
{
    //    qDebug() << "MainWidget::timerEvent" << isVisible();
    //    for (int i = 0; i < qApp->children().size(); ++i) {
    //        qDebug() <<qApp->children().at(i);
    //    }
    QWidget::timerEvent(event);
}

void MainWidget::ontWidgetTypeChange(const Widget::Type type, const QString &status)
{
    //    switch (type) {
    //    default: {
    //        //        if (WidgetStatus::Show == status) {
    //        //            EventEngine::CustomEvent<QString> event(CustomEventType::MessageBoxWidgetStatus, new QString(WidgetStatus::RequestHide));
    //        //            g_EventEngine->sendCustomEvent(event);
    //        //        }
    //        break;
    //    }
    //    }
    if (WidgetStatus::Show == status) {
        setVisible(true);
    }
}

void MainWidget::onStartCalibrate()
{
    qDebug() << "MainWidget::onStartCalibrate";
    setVisible(false);
}

void MainWidget::onFinishCalibrate(const QString& xml)
{
    qDebug() << "MainWidget::onFinishCalibrate" << xml;
    //    QWSPointerCalibrationData data;
    //    QPoint *screenPoints = data.screenPoints;
    //    QPoint *devicePoints = data.devPoints;
    //    QDomDocument document;
    //    document.setContent(xml);
    //    QDomElement root = document.documentElement();
    //    if ((!root.isNull())
    //            && (root.isElement())
    //            && (QString("Calibrate") == root.toElement().tagName())
    //            && (root.hasChildNodes())) {
    //        QDomNode node = root.firstChild();
    //        while (!node.isNull()) {
    //            if (node.isElement()) {
    //                QDomElement element = node.toElement();
    //                if (!element.isNull()) {
    //                    if ((QString("ScreenPoints") == element.tagName())
    //                            || (QString("DevicePoints") == element.tagName())) {
    //                        QDomNodeList nodeList = element.childNodes();
    //                        for (int i = 0, j = 0, k = 0; i < nodeList.size(); ++i) {
    //                            QDomNode node = nodeList.at(i);
    //                            if (node.isElement()) {
    //                                if (!node.toElement().isNull()) {
    //                                    if (QString("ScreenPoints") == element.tagName()) {
    //                                        if (node.toElement().tagName().contains(QString("ScreenPointsX:"))) {
    //                                            screenPoints[j].setX(node.toElement().text().toInt());
    //                                        } else if (node.toElement().tagName().contains(QString("ScreenPointsY:"))) {
    //                                            screenPoints[j].setY(node.toElement().text().toInt());
    //                                            ++j;
    //                                        }
    //                                    } else if (QString("DevicePoints") == element.tagName()) {
    //                                        if (node.toElement().tagName().contains(QString("DevicePointsX:"))) {
    //                                            devicePoints[k].setX(node.toElement().text().toInt());
    //                                        } else if (node.toElement().tagName().contains(QString("DevicePointsY:"))) {
    //                                            devicePoints[k].setY(node.toElement().text().toInt());
    //                                            ++k;
    //                                        }
    //                                    }
    //                                    qDebug() << root.toElement().tagName();
    //                                    qDebug() << "Index:" << node.toElement().tagName();
    //                                    qDebug() << "value:" << node.toElement().text();
    //                                }
    //                            }
    //                        }
    //                    }
    //                }
    //            }
    //            node = node.nextSibling();
    //        }
    //    }
    //    qDebug() << "calibrate";
    //    for (int i = 0; i < 5; ++i) {
    //        qDebug() << screenPoints[i].x() << screenPoints[i].y();
    //        qDebug() << devicePoints[i].x() << devicePoints[i].y();
    //    }
    //#ifndef gcc
    //    QWSServer::mouseHandler()->calibrate(&(data));
    //#endif
    setVisible(true);
}

MainWidgetPrivate::MainWidgetPrivate(MainWidget *parent)
    : m_Parent(parent)
{
    //    m_CalibrateWidget = NULL;
    m_DiskWidget = NULL;
    m_HomeWidget = NULL;
    m_LinkWidget = NULL;
    m_SettingWidget = NULL;
    m_MediaWidget = NULL;
//    m_AVWidget = NULL;
    m_StatusBarWidget = NULL;
    m_TabBarWidget = NULL;
    m_FMWidget = NULL;
    m_MessageBoxWidget = NULL;
    m_IdleWidget = NULL;
    //    if (qApp->arguments().contains(QString("-calibrate"))) {
    //        m_Parent->setVisible(true);
    //        m_CalibrateWidget = new CalibrateWidget(m_Parent);
    //        m_Parent->startTimer(500);
    //    } else {
    initialize();
    connectAllSlots();
    m_Parent->setVisible(true);
    //    }
}

MainWidgetPrivate::~MainWidgetPrivate()
{
}

void MainWidgetPrivate::initialize()
{

    m_DiskWidget = new DiskWidget(m_Parent);
    m_LinkWidget = new LinkWidget(m_Parent);
   // m_AVWidget = new AVWidget(m_Parent);
    m_SettingWidget = new SettingWidget(m_Parent);
    m_MediaWidget = new MediaWidget(m_Parent);

    m_HomeWidget = new HomeWidget(m_Parent);    //中间这块
    Utility::elapsed("HomeWidget");
    m_StatusBarWidget = new StatusBarWidget(m_Parent);//最上边的
    Utility::elapsed("StatusBarWidget");
    m_TabBarWidget = new TabBarWidget(m_Parent);//最下面的状态
    Utility::elapsed("TabBarWidget");
    //    Utility::elapsed(__func__);
#ifndef gcc
    //    m_Parent->setCursor(Qt::BlankCursor);
    m_Parent->setWindowFlags(Qt::FramelessWindowHint);
#endif
    //    QStringList cmd;
    //    cmd << QString("-t") << QString("-qws") << QString("-calibrate");
    //    QDBusConnection::sessionBus().connect(QString(),
    //                                          CALIBRATEPATH,
    //                                          CALIBRATEINTERFACE,
    //                                          CALIBRATESTARTMETHOD,
    //                                          m_Parent,
    //                                          SLOT(onStartCalibrate()));
    //    QDBusConnection::sessionBus().connect(QString(),
    //                                          CALIBRATEPATH,
    //                                          CALIBRATEINTERFACE,
    //                                          CALIBRATEFINISHMETHOD,
    //                                          m_Parent,
    //                                          SLOT(onFinishCalibrate(const QString&)));
    //    bool ret = QProcess::startDetached(qApp->applicationFilePath(), cmd);
    //    qDebug() << "start" << QString("-calibrate") << ret;
}

void MainWidgetPrivate::connectAllSlots()
{
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
}
