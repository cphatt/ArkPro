#ifndef MusicLoadingWidget_H
#define MusicLoadingWidget_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include <QWidget>
#include <QScopedPointer>

class MusicLoadingWidgetPrivate;
class MusicLoadingWidget
        : protected QWidget
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicLoadingWidget)
public:
    explicit MusicLoadingWidget(QWidget *parent = NULL);
    ~MusicLoadingWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent* event);
    bool event(QEvent* event);
protected slots:
    //Multimedia::Interface
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
private:
    friend class MusicLoadingWidgetPrivate;
    QScopedPointer<MusicLoadingWidgetPrivate> m_Private;
};

#endif // MusicLoadingWidget_H
