#ifndef CALIBRATEWIDGET_H
#define CALIBRATEWIDGET_H

#include <QWidget>
#include <QScopedPointer>

#define CALIBRATESERVICE       QString("com.arkmicro.calibrate")
#define CALIBRATEPATH          QString("/com/arkmicro/calibrate")
#define CALIBRATEINTERFACE     QString("Local.DbusServer.Calibrate")
#define CALIBRATESTARTMETHOD   QString("startCalibrate")
#define CALIBRATEFINISHMETHOD  QString("finishCalibrate")
//dbus-send --session --type=signal /com/arkmicro/calibrate Local.DbusServ
//er.Calibrate.finishCalibrate
class CalibrateWidgetPrivate;
class CalibrateWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CalibrateWidget)
public:
    explicit CalibrateWidget(QWidget* parent = NULL);
    ~CalibrateWidget();
signals:
    void startCalibrate();
    void finishCalibrate(const QString& str);
protected:
    void resizeEvent(QResizeEvent* event);
    void hideEvent(QHideEvent* event);
    void paintEvent(QPaintEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void timerEvent(QTimerEvent* event);
private:
    friend class CalibrateWidgetPrivate;
    QScopedPointer<CalibrateWidgetPrivate> m_Private;
};

#endif //CALIBRATEWIDGET_H
