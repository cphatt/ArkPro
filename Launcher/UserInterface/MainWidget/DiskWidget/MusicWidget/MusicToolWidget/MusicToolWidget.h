#ifndef MUSICTOOLWIDGET_H
#define MUSICTOOLWIDGET_H

#include "BusinessLogic/Multimedia/Multimedia.h"
#include "BusinessLogic/Widget/Widget.h"
#include <QWidget>
#include <QScopedPointer>

class MusicToolWidgetPrivate;
class MusicToolWidget
        : protected QWidget
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicToolWidget)
public:
    explicit MusicToolWidget(QWidget *parent = NULL);
    ~MusicToolWidget();
    QString StringLeftMove(const QString string);
protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void customEvent(QEvent *event);
protected slots:
    //MusicPlayer::Interface
    void onMusicPlayerPlayMode(const int mode);
    //        void onMusicPlayerPlayMode(const MusicPlayerPlayMode mode);
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
    void onMusicPlayerElapsedInformation(const int elapsedTime, const int elapsedMillesimal);
    void onMusicPlayerID3TagChange(const int index,
                                   const QString &fileName,
                                   const int endTime);
public slots:
    void onTickMarksMillesimalStart(const int millesimal);
    void onTickMarksMillesimalEnd(const int millesimal);
    void onToolButtonRelease();
private slots:
    void onTimeout();
private:
    friend class MusicToolWidgetPrivate;
    QScopedPointer<MusicToolWidgetPrivate> m_Private;
};

#endif // MUSICTOOLWIDGET_H
