#ifndef MUSICSHORTCUTWIDGET_H
#define MUSICSHORTCUTWIDGET_H

#include "BusinessLogic/Widget/Widget.h"
#include "BusinessLogic/Multimedia/Multimedia.h"
#include "UserInterface/Common/BmpButton.h"
#include <QScopedPointer>

class MusicShortCutWidgetPrivate;
class MusicShortCutWidget
        : protected QWidget
        , protected Multimedia::Interface
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicShortCutWidget)
public:
    explicit MusicShortCutWidget(QWidget *parent = NULL);
    ~MusicShortCutWidget();
protected:
    void resizeEvent(QResizeEvent* event);
    void customEvent(QEvent* event);
protected slots:
    //Multimedia::Interface
    void onMusicPlayerPlayStatus(const int status);
    //        void onMusicPlayerPlayStatus(const MusicPlayerPlayStatus status);
private slots:
    void onBmpButtonRelease();
private:
    friend class MusicShortCutWidgetPrivate;
    QScopedPointer<MusicShortCutWidgetPrivate> m_Private;
};

#endif // MUSICSHORTCUTWIDGET_H
