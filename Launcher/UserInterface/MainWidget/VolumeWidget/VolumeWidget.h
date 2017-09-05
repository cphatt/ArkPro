#ifndef VOLUMEWIDGET_H
#define VOLUMEWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class VolumeWidgetPrivate;
class VolumeWidget : protected QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VolumeWidget)
public:
    explicit VolumeWidget(QWidget* parent = NULL);
    ~VolumeWidget();
protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);


private slots:
    void onTimeout();

private:
    friend class VolumeWidgetPrivate;
    QScopedPointer<VolumeWidgetPrivate> m_Private;
};

#endif // VOLUMEWIDGET_H
