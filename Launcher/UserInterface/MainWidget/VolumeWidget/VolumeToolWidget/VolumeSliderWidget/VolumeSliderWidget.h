#ifndef VOLUMESLIDERWIDGET_H
#define VOLUMESLIDERWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class VolumeSliderWidgetPrivate;
class VolumeSliderWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VolumeSliderWidget)
public:
    explicit VolumeSliderWidget(QWidget* parent = NULL);
    ~VolumeSliderWidget();
    void setTickMarksMillesimal(const int millesimal);
protected:
    void resizeEvent(QResizeEvent* event);
signals:
    void minusBtnRelease();
    void plusBtnRelease();
    void tickMarksMillesimalEnd(const int millesimal);
private:
    friend class VolumeSliderWidgetPrivate;
    QScopedPointer<VolumeSliderWidgetPrivate> m_Private;
};

#endif // VOLUMESLIDERWIDGET_H
