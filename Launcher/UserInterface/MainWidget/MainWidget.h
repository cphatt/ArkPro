#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

#define ArkMicroLauncherService       QString("com.arkmicro.launcher")

class MainWidgetPrivate;
class MainWidget
        : protected QWidget
        , protected Widget::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(MainWidget)
#ifdef g_MainWindow
#undef g_MainWindow
#endif
#define g_MainWindow (MainWindow::instance())
public:
    explicit MainWidget(QWidget* parent = NULL);
    ~MainWidget();
protected:
    bool event(QEvent* event);
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
protected slots:
    //Widget::Interface
    void ontWidgetTypeChange(const Widget::Type type, const QString &status);
private slots:
    void onStartCalibrate();
    void onFinishCalibrate(const QString& xml);
private:
    friend class MainWidgetPrivate;
    QScopedPointer<MainWidgetPrivate> m_Private;
};

#endif // MAINWINDOW_H
