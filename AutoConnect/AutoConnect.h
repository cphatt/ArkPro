#ifndef AUTOCONNECT_H
#define AUTOCONNECT_H

#include <QList>
#include <QString>
class QObject;

void connectSignalAndSlotByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list = QList<QString>());
void connectSignalAndSignalByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list = QList<QString>());

#endif // AUTOCONNECT_H
