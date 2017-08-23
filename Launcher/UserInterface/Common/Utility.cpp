#include "Utility.h"
#include <QColor>
#include <QTime>
#include <QDebug>

QTime Utility::time;

QBrush Utility::listViewItemBrush()
{
    return QBrush(QColor(0, 94, 187));
}

QColor Utility::customBlackColor()
{
    return QColor(0, 0, 1);
}

QColor Utility::videoColor()
{
    return QColor(0, 0, 0);
}

QColor Utility::mainWidgetBackgroundColor()
{
    return QColor(16, 6, 119);
}

QColor Utility::multimediaAlphaColor()
{
    return QColor(210, 210, 210, 180);
}

void Utility::startTime()
{
    time.restart();
}

void Utility::elapsed(const QString &str)
{
    qDebug() << "Utility::elapsed" << time.elapsed() << str;
}
