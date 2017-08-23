#include "ArkApplication.h"
#include <QDebug>
#ifdef QT_GUI_LIB
#include <QFont>
#include <QFontDatabase>
#include <QStringList>
#ifndef gcc
#include <QBrush>
#include <QColor>
#include <QWSServer>
#endif
#endif

class ArkApplicationPrivate
{
    Q_DISABLE_COPY(ArkApplicationPrivate)
public:
    explicit ArkApplicationPrivate(int &argc, char **argv, ArkApplication* parent);
    ~ArkApplicationPrivate();
#ifdef QT_GUI_LIB
    QStringList m_Arguments;
#endif
private:
    ArkApplication* m_Parent;
};

ArkApplication::ArkApplication(int &argc, char **argv)
#ifdef QT_GUI_LIB
    : QApplication(argc, argv, QApplication::GuiServer)
    #else
    : QCoreApplication(argc, argv)
    #endif
    , m_Private(new ArkApplicationPrivate(argc, argv, this))
{
#ifdef QT_GUI_LIB
#ifndef gcc
    QFontDatabase database;
    QStringList type = database.families();
    for (int i = 0; i < type.size(); ++i) {
        qDebug() << "Qt support font type:" << type.at(i);
    }
#endif
    QFont font(QString("WenQuanYi Micro Hei"));
    font.setPixelSize(18);
    setFont(font);
    qDebug() << "Application font" << QApplication::font();
#ifndef gcc
//    QWSServer::setCursorVisible(false);
//    setOverrideCursor(Qt::BlankCursor);
//    QWSServer::setBackground(QBrush(Qt::transparent));
//    QWSServer::sendMouseEvent(QPoint(0, 0), 0);
#endif
#endif
}

ArkApplication::~ArkApplication()
{
}

int ArkApplication::size() const
{
    return m_Private->m_Arguments.size();
}

QStringList ArkApplication::arguments() const
{
    return m_Private->m_Arguments;
}

bool ArkApplication::notify(QObject *object, QEvent *event)
{
//    qDebug() << "Application::notify" << object << event << event->type();
    return QApplication::notify(object, event);
}

ArkApplicationPrivate::ArkApplicationPrivate(int &argc, char **argv, ArkApplication* parent)
    : m_Parent(parent)
{
    m_Arguments.clear();
    if ((1 == argc) || (2 == argc)) {
        int tempArgc(3);
        char* tempArgv[3] = {argv[0], "-t", "-qws"};
        argc = tempArgc;
        argv = tempArgv;
    }
    qDebug() << "main argc=" << argc;
    for (int i = 0; i < argc; ++i) {
        qDebug() << "argv[" << i << "]=" << argv[i];
    }
    for (int i = 0; i < argc; ++i) {
        m_Arguments << QString(argv[i]);
    }
    qDebug() << "ArkApplicationPrivate" << argc << m_Arguments;
}

ArkApplicationPrivate::~ArkApplicationPrivate()
{
}

