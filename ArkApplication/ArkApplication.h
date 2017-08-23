#ifndef ARKAPPLICATION_H
#define ARKAPPLICATION_H

#include <QCoreApplication>
#ifdef QT_GUI_LIB
#include <QApplication>
#endif
#include <QScopedPointer>
#if defined(ArkApp)
#undef ArkApp
#endif
#define ArkApp (static_cast<ArkApplication *>(QCoreApplication::instance()))

class ArkApplicationPrivate;
class ArkApplication
        #ifdef QT_GUI_LIB
        : public QApplication
        #else
        : public QCoreApplication
        #endif
{
    Q_DISABLE_COPY(ArkApplication)
public:
    explicit ArkApplication(int &argc, char **argv);
    ~ArkApplication();
    int size() const;
    QStringList arguments() const;
protected:
    bool notify(QObject *object, QEvent *event);
private:
    friend class ArkApplicationPrivate;
    QScopedPointer<ArkApplicationPrivate> m_Private;
};

#endif // ARKAPPLICATION_H
