#ifndef MULTIMEDIALOADINGWIDGET_H
#define MULTIMEDIALOADINGWIDGET_H

#include <QWidget>
#include <QScopedPointer>

class MultimediaLoadingWidgetPrivate;
class MultimediaLoadingWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MultimediaLoadingWidget)
public:
    explicit MultimediaLoadingWidget(QWidget *parent = NULL);
    ~MultimediaLoadingWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
private:
    friend class MultimediaLoadingWidgetPrivate;
    QScopedPointer<MultimediaLoadingWidgetPrivate> m_Private;
};

#endif // MULTIMEDIALOADINGWIDGET_H
