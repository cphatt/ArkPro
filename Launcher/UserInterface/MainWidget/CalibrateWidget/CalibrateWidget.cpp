#include "CalibrateWidget.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QScreen>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDomDocument>
#include <QWSServer>
#include <QWSPointerCalibrationData>
#ifndef gcc
#endif

//export POINTERCAL_FILE=$TSLIB_CALIBFILE

class CalibrateWidgetPrivate
{
    Q_DISABLE_COPY(CalibrateWidgetPrivate)
public:
    explicit CalibrateWidgetPrivate(CalibrateWidget* parent);
    ~CalibrateWidgetPrivate();
    void initialize();
    void connectAllSlots();
    void calibrateStart();
    void calibrateFinish();
    QWSPointerCalibrationData m_PointerCalibrationData;
    int m_PressCount;
    int m_TimerId;
private:
    CalibrateWidget* m_Parent;
};

CalibrateWidget::CalibrateWidget(QWidget* parent)
    : QWidget(parent)
    , m_Private(new CalibrateWidgetPrivate(this))
{
    qDebug() << "CalibrateWidget::CalibrateWidget";
}

CalibrateWidget::~CalibrateWidget()
{
}

void CalibrateWidget::resizeEvent(QResizeEvent *event)
{
    g_Widget->geometryFit(0, 0, g_Widget->baseWindowWidth(), g_Widget->baseWindowHeight(), this);
    QWidget::resizeEvent(event);
}

void CalibrateWidget::hideEvent(QHideEvent *event)
{
    if (isVisible()) {
        releaseMouse();
    }
    QWidget::hideEvent(event);
}

void CalibrateWidget::paintEvent(QPaintEvent* event)
{
    QPainter p(this);
    p.fillRect(rect(), Qt::white);
#ifndef gcc
    QPoint point = m_Private->m_PointerCalibrationData.screenPoints[m_Private->m_PressCount];
    // Map to logical coordinates in case the screen is transformed
    QSize screenSize(qt_screen->deviceWidth(), qt_screen->deviceHeight());
    point = qt_screen->mapFromDevice(point, screenSize);
    p.fillRect(point.x() - 6, point.y() - 1, 13, 3, Qt::black);
    p.fillRect(point.x() - 1, point.y() - 6, 3, 13, Qt::black);
#endif
    QWidget::paintEvent(event);
}

void CalibrateWidget::mouseReleaseEvent(QMouseEvent *event)
{
    // Map from device coordinates in case the screen is transformed
#ifndef gcc
    QSize screenSize(qt_screen->width(), qt_screen->height());
    QPoint p = qt_screen->mapToDevice(event->pos(), screenSize);
#endif
#ifndef gcc
    m_Private->m_PointerCalibrationData.devPoints[m_Private->m_PressCount] = p;
#endif
    if (++(m_Private->m_PressCount) < 5) {
        repaint();
    } else {
        m_Private->calibrateFinish();
    }
    qDebug() << "m_Private->m_PressCount" << m_Private->m_PressCount;
    QWidget::mouseReleaseEvent(event);
}

void CalibrateWidget::timerEvent(QTimerEvent *event)
{
    grabMouse();
    QWidget::timerEvent(event);
}

CalibrateWidgetPrivate::CalibrateWidgetPrivate(CalibrateWidget *parent)
    : m_Parent(parent)
{
    m_PressCount = 0;
    m_TimerId = -1;
    initialize();
    connectAllSlots();
    m_Parent->setFocusPolicy(Qt::StrongFocus);
    m_Parent->setFocus();
    m_Parent->setVisible(true);
    m_TimerId = m_Parent->startTimer(0);
}

CalibrateWidgetPrivate::~CalibrateWidgetPrivate()
{
}

void CalibrateWidgetPrivate::initialize()
{
    calibrateStart();
    QDBusMessage message =QDBusMessage::createSignal(CALIBRATEPATH,
                                                     CALIBRATEINTERFACE,
                                                     CALIBRATESTARTMETHOD);
    qDebug() << "CalibrateWidgetPrivate::initialize" << QDBusConnection::sessionBus().send(message);
}

void CalibrateWidgetPrivate::connectAllSlots()
{
}

void CalibrateWidgetPrivate::calibrateStart()
{
#ifndef gcc
    int width = qt_screen->deviceWidth();
    int height = qt_screen->deviceHeight();
    m_Parent->setGeometry(0, 0, width, height);
    int dx = width / 10;
    int dy = height / 10;
#endif
#ifndef gcc
    QPoint *points = m_PointerCalibrationData.screenPoints;
    points[QWSPointerCalibrationData::TopLeft] = QPoint(dx, dy);
    points[QWSPointerCalibrationData::BottomLeft] = QPoint(dx, height - dy);
    points[QWSPointerCalibrationData::BottomRight] = QPoint(width - dx, height - dy);
    points[QWSPointerCalibrationData::TopRight] = QPoint(width - dx, dy);
    points[QWSPointerCalibrationData::Center] = QPoint(width / 2, height / 2);
#endif
    m_PressCount = 0;
#ifndef gcc
    if (width < g_Widget->baseWindowWidth()) {
        QWSServer::mouseHandler()->clearCalibration();
    }
#endif
    m_Parent->grabMouse();
}

void CalibrateWidgetPrivate::calibrateFinish()
{
    m_PressCount = 0;
#ifndef gcc
    QWSServer::mouseHandler()->calibrate(&(m_PointerCalibrationData));
#endif
    QPoint *screenPoints = m_PointerCalibrationData.screenPoints;
    QPoint *devicePoints = m_PointerCalibrationData.devPoints;
    qDebug() << "calibrate";
    for (int i = 0; i < 5; ++i) {
        qDebug() << screenPoints[i].x() << screenPoints[i].y();
        qDebug() << devicePoints[i].x() << devicePoints[i].y();
    }
    QString xml;
    xml.clear();
    //    QDomDocument domDocument;
    //    domDocument.clear();
    //    domDocument.appendChild(domDocument.createElement(QString("Calibrate")));
    //    QDomElement root = domDocument.firstChildElement(QString("Calibrate"));
    //    QDomElement fileNames;
    //    QDomElement info;
    //    fileNames = domDocument.createElement(QString("ScreenPoints"));
    //    root.appendChild(fileNames);
    //    for (int i = QWSPointerCalibrationData::TopLeft;
    //         i <= QWSPointerCalibrationData::Center;
    //         ++i) {
    //        info = domDocument.createElement(QString("ScreenPointsX:" + QString::number(i)));
    //        fileNames.appendChild(info);
    //        info.appendChild(domDocument.createTextNode(QString::number(screenPoints[i].x())));
    //        info = domDocument.createElement(QString("ScreenPointsY:" + QString::number(i)));
    //        fileNames.appendChild(info);
    //        info.appendChild(domDocument.createTextNode(QString::number(screenPoints[i].y())));
    //    }
    //    fileNames = domDocument.createElement(QString("DevicePoints"));
    //    root.appendChild(fileNames);
    //    for (int i = QWSPointerCalibrationData::TopLeft;
    //         i <= QWSPointerCalibrationData::Center;
    //         ++i) {
    //        info = domDocument.createElement(QString("DevicePointsX:" + QString::number(i)));
    //        fileNames.appendChild(info);
    //        info.appendChild(domDocument.createTextNode(QString::number(devicePoints[i].x())));
    //        info = domDocument.createElement(QString("DevicePointsY:" + QString::number(i)));
    //        fileNames.appendChild(info);
    //        info.appendChild(domDocument.createTextNode(QString::number(devicePoints[i].y())));
    //    }
    //    xml = domDocument.toString();
    //    qDebug() << xml;
    qDebug() << "CalibrateWidget::CalibrateWidget";
    QDBusMessage message = QDBusMessage::createSignal(CALIBRATEPATH,
                                                      CALIBRATEINTERFACE,
                                                      CALIBRATEFINISHMETHOD);
    message << xml;
    qDebug() << QDBusConnection::sessionBus().send(message);
    if (-1 != m_TimerId) {
        m_Parent->killTimer(m_TimerId);
    }
    m_Parent->releaseMouse();
    m_Parent->setVisible(false);
}
