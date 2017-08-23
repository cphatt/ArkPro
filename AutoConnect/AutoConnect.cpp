#include "AutoConnect.h"
#include <QMetaMethod>
#include <QDebug>
#include <QObject>

#ifndef QLOCATION
#define QLOCATION "\0"__FILE__":"QTOSTRING(__LINE__)
#endif

enum ConnectType {
    CT_Signal = 0,
    CT_Slot,
};

void autoConnect(QObject *sender, QObject *receiver, const ConnectType type, const QList<QString>& list)
{
#define METASIGNAL 2
#define METASLOT   1
    Q_ASSERT(sender);
    Q_ASSERT(receiver);
    const QMetaObject *instanceMeta = sender->metaObject();
    Q_ASSERT(instanceMeta);
    for (int i = 0; i < instanceMeta->methodCount(); ++i) {
        if (QMetaMethod::Signal == instanceMeta->method(i).methodType()) {
#if QT_VERSION >= 0x050000
            const QByteArray signalSignature = instanceMeta->method(i).methodSignature();
            const char *signal = signalSignature.constData();
#else
            const char *signal = instanceMeta->method(i).signature();
#endif
            Q_ASSERT(signal);
            if (-1 != instanceMeta->indexOfSignal(signal)) {
                const QMetaObject *dispatcherMeta = receiver->metaObject();
                Q_ASSERT(dispatcherMeta);
                for (int j = 0; j < dispatcherMeta->methodCount(); ++j) {
                    QMetaMethod::MethodType methodType;
                    if (type == CT_Slot) {
                        methodType = QMetaMethod::Slot;
                    } else {
                        methodType = QMetaMethod::Signal;
                    }
                    if (methodType == dispatcherMeta->method(j).methodType()) {
#if QT_VERSION >= 0x050000
                        const QByteArray slotSignature = dispatcherMeta->method(j).methodSignature();
                        const char *slot = slotSignature.constData();
#else
                        const char *slot = dispatcherMeta->method(j).signature();
#endif
                        Q_ASSERT(slot);
                        int ret = -1;
                        if (type == CT_Slot) {
                            ret = dispatcherMeta->indexOfSlot(slot);
                        } else {
                            ret = dispatcherMeta->indexOfSignal(slot);
                        }
                        if (-1 != ret) {
                            if (QString(signal) ==  QString(slot)) {
                                QString signalStr = QString(METASIGNAL) + QString(signal) + QString(QLOCATION);
                                QString slotStr;
                                if (type == CT_Slot) {
                                    slotStr = qPrintable(QString(METASLOT) + QString(slot) + QString(QLOCATION));
                                } else {
                                    slotStr = qPrintable(QString(METASIGNAL) + QString(slot) + QString(QLOCATION));
                                }
                                Qt::ConnectionType connectType = static_cast<Qt::ConnectionType>(Qt::AutoConnection | Qt::UniqueConnection);
                                if (0 ==  list.size()) {
                                    QObject::connect(sender,
                                                     qFlagLocation(qPrintable(signalStr)),
                                                     receiver,
                                                     qFlagLocation(qPrintable(slotStr)),
                                                     connectType);
                                } else {
                                    if (list.contains(slotStr)) {
                                        QObject::connect(sender,
                                                         qFlagLocation(qPrintable(signalStr)),
                                                         receiver,
                                                         qFlagLocation(qPrintable(slotStr)),
                                                         connectType);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void connectSignalAndSlotByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list)
{
    autoConnect(sender, receiver, CT_Slot, list);
}

void connectSignalAndSignalByNamesake(QObject *sender, QObject *receiver, const QList<QString>& list)
{
    autoConnect(sender, receiver, CT_Signal, list);
}
