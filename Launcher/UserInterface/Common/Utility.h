#ifndef UTILITY_H
#define UTILITY_H

#include <QObject>
#include <QBrush>

class Utility
{
public:
    static QBrush listViewItemBrush();
    static QColor customBlackColor();
    static QColor videoColor();
    static QColor mainWidgetBackgroundColor();
    static QColor multimediaAlphaColor();
    static void startTime();
    static void elapsed(const QString &str);
private:
    Utility();
    ~Utility();
    Utility(const Utility &utility);
    Utility& operator =(const Utility &utility);
    static QTime time;
};

#endif // UTILITY_H
