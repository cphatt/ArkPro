#include "Port.h"
#include <QDebug>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "RunnableThread.h"
#include "AutoConnect.h"
#include <QThreadPool>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

static int input_fd;
bool isUSBAlive;
bool isSDAlive;
class PortPrivate
{
    Q_DISABLE_COPY(PortPrivate)
public:
    explicit PortPrivate(Port* parent);
    ~PortPrivate();
    void initialize();
    void connectAllSlots();
    bool isOpen();
    void setPortName(const QString &name);
    QString portName() ;
    void setBaudRate(int baudRate);
    int baudRate();
    virtual bool open();
    virtual void close();
    virtual bool clear();
    QByteArray readData();
    int writeData(char *buf, int size);
    int write(char ch);
    static void SerialPortReadThread(void *);
    QString m_portName;
    int m_BaudRate;
    QSerialPort *m_serialPort;
    QByteArray requestData;

public:
    Port* m_Parent;

};

void Port::handlerMCUData(const Port::Type type, const char *buffer, const int size)
{
    qDebug() <<"Port::handlerMCUData";
    emit onMCUDataRecv(type,buffer,size);
}

void Port::handlerData(QByteArray data)
{
    //qDebug() <<"Port::handlerData" << m_Private->requestData;
    //qDebug() <<"Port::handlerData" <<data.data();
     //   qDebug() <<"Port::handlerData" <<data.toHex().data();
}

Port::Port(QObject *parent)
    : QObject(parent)
    , m_Private(new PortPrivate(this))
{
     qDebug() <<"Port::Port";
}

Port::~Port()
{

}


void Port::onDeviceWatcherStatus(const DeviceWatcherType type, const DeviceWatcherStatus status)
{
    qDebug() << "HomeWidget::onDeviceWatcherStatus" << type << status;
    if (DWT_SDDisk == type) {
        switch (status) {
            case DWS_Empty: {
                isSDAlive= false;
                break;
            }
            case DWS_Busy: {
                isSDAlive = true;
                break;
            }
            case DWS_Ready: {
                isSDAlive= true;
                break;
            }
            case DWS_Remove: {
                isSDAlive = false;
                break;
            }
            default: {
                break;
            }
        }
    }
    if (DWT_USBDisk == type) {
        switch (status) {
            case DWS_Empty: {
                isUSBAlive = false;
                break;
            }
            case DWS_Busy: {
                isUSBAlive = true;
                break;
            }
            case DWS_Ready: {
                isUSBAlive = true;
                break;
            }
            case DWS_Remove: {
                isUSBAlive = false;
                break;
            }
            default: {
                break;
            }
        }
    }
}
PortPrivate::~PortPrivate()
{

}

PortPrivate::PortPrivate(Port* parent)
    : m_Parent(parent)
{
    m_serialPort = NULL;
    m_BaudRate = 9600;
    m_portName = "";
    requestData = "";
    input_fd = -1;
#ifndef gcc
    initialize();
#endif
    connectAllSlots();

}
bool isCommand(const char *read_buf){
    struct input_event ev; //input

    char checksum;
    int x_val,y_val,i;
    bool ret = false;

        checksum = 0;
        for(i=0; i<5; i++)
            checksum += read_buf[i];
        checksum = ~checksum;
        //qDebug() << checksum << read_buf[i];

        if(checksum == read_buf[i])
        {
            if(read_buf[0] == 0x61 || read_buf[0] == 0xa1 || read_buf[0] == 0xe1)//header -- touch event
            {
                x_val = (read_buf[2] << 8) | (read_buf[1] << 0);
                y_val = (read_buf[4] << 8) | (read_buf[3] << 0);

                if(read_buf[0] == 0xe1) //release
                {
                    //presure
                    ev.type = EV_ABS;
                    ev.code = ABS_PRESSURE;
                    ev.value = 0x0;
                    ::write(input_fd, &ev, sizeof(struct input_event));

                    //sync
                    ev.type = EV_SYN;
                    ev.code = SYN_REPORT;
                    ev.value = 0x0;
                    ret = ::write(input_fd, &ev, sizeof(struct input_event));
                   // qDebug() << "UP";
                }
                else	//push
                {
                    //x axis
                    ev.type = EV_ABS;
                    ev.code = ABS_X;
                    ev.value = x_val;
                    ret = ::write(input_fd, &ev, sizeof(struct input_event));
                    if(ret < 0)
                    {
                        qDebug() << "write X axis failed";
                    }
                    //y axis
                    ev.type = EV_ABS;
                    ev.code = ABS_Y;
                    ev.value = y_val;
                    ::write(input_fd, &ev, sizeof(struct input_event));
                    //presure
                    ev.type = EV_ABS;
                    ev.code = ABS_PRESSURE;
                    ev.value = 0xFFF;
                   ::write(input_fd, &ev, sizeof(struct input_event));

                    //sync
                    ev.type = EV_SYN;
                    ev.code = SYN_REPORT;
                    ev.value = 0x0;
                    ::write(input_fd, &ev, sizeof(struct input_event));
                    //qDebug() << "MOVE";
                }
                ret = true;
            }
            else  if(read_buf[0] == 0x51 || read_buf[0] == 0x91 || read_buf[0] == 0xd1)//header -- touch event
            {
                //printf("#Key data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",read_buf[0], read_buf[1], read_buf[2], read_buf[3], read_buf[4], read_buf[5]);
                switch (read_buf[2]) {
                case Port::K_Control :

                    break;
                case Port::K_Escape :
                    g_Widget->setWidgetType(Widget::T_Back, WidgetStatus::RequestShow);
                    break;
                case Port::K_VolumeMore :

                    break;
                case Port::K_VolumeLess :

                    break;
                case Port::K_Down :

                    break;
                case Port::K_Up :

                    break;
                case Port::K_Right :

                    break;
                case Port::K_Enter :

                    break;
                case Port::K_Left :

                    break;
                case Port::K_Menu :

                    break;
                case Port::K_BT :

                    break;
                case Port::K_CMMB :

                    break;
                case Port::K_GPS :

                    break;
                case Port::K_Music :
                    if (isUSBAlive)
                        g_Widget->setWidgetType(Widget::T_USBDiskMusic, WidgetStatus::RequestShow);
                    else if(isSDAlive)
                        g_Widget->setWidgetType(Widget::T_SDDiskMusic, WidgetStatus::RequestShow);
                    break;
                case Port::K_Picture :
                    if (isUSBAlive)
                        g_Widget->setWidgetType(Widget::T_USBDiskImage, WidgetStatus::RequestShow);
                    else if(isSDAlive)
                        g_Widget->setWidgetType(Widget::T_SDDiskImage, WidgetStatus::RequestShow);
                    break;
                case Port::K_Video :
                    if (isUSBAlive)
                        g_Widget->setWidgetType(Widget::T_USBDiskVideo, WidgetStatus::RequestShow);
                    else if(isSDAlive)
                        g_Widget->setWidgetType(Widget::T_SDDiskVideo, WidgetStatus::RequestShow);
                    break;
                case Port::K_Home :
                    g_Widget->setWidgetType(Widget::T_Home, WidgetStatus::RequestShow);
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            printf("###### data: 0x%x 0x%x 0x%x 0x%x 0x%x 0x%x \n",read_buf[0], read_buf[1], read_buf[2], read_buf[3], read_buf[4], read_buf[5]);
        //	printf("###### x:%d y:%d\n",(read_buf[2] << 8) | (read_buf[1] << 0),(read_buf[4] << 8) | (read_buf[3] << 0));
        }
        return ret;
}
void PortPrivate::SerialPortReadThread(void *paramater)
{
    qDebug() << "SerialPortReadThread" << paramater;
    PortPrivate* m_Private = (PortPrivate*)paramater;
    int len = 0;

    forever{
        m_Private->requestData += m_Private->readData(); //m_Private->m_serialPort->readAll();
        len = m_Private->requestData.size();
        while(len >= 6)
        {
            //将qbytearray分割成两个变量
           //qDebug() <<"SerialPortReadThread"<<QString(m_Private->requestData);
               //     qDebug() <<"Port::handlerData" <<m_Private->requestData.toHex().data();
            //         m_Private->requestData = "";
           // emit m_Private->m_Parent->read_port_data(m_Private->requestData);
            if(isCommand(m_Private->requestData.mid(0,6).data())){
                len -= 6;
                m_Private->requestData = m_Private->requestData.mid(6,len);
            }
            else{
                len -= 1;
                m_Private->requestData = m_Private->requestData.mid(1,len);
            }

        }

    }
}

void PortPrivate::initialize()
{
    system("pkill app_touchscreen");
    m_serialPort = new QSerialPort();
#ifdef gcc
        m_BaudRate = 115200;
    m_portName = "/dev/ttyUSB0";
#else
        m_BaudRate = 38400;
    m_portName = "/dev/ttyHS0";
#endif
    if(open()){
        qDebug() <<"66666666666666";
    }else{
        qDebug() <<"77777777777777" << m_serialPort->errorString();
        return;
    }

    input_fd = ::open("/dev/input/event0", O_RDWR);
    if(input_fd < 0)
    {
        perror("Can not open input node\n");
        exit(1);
    }else{
        qDebug()<< "open input success!";
    }
    CustomRunnable* runnable = new CustomRunnable();
    runnable->setCallbackFunction(SerialPortReadThread, this);
    QThreadPool::globalInstance()->start(runnable);
}

void PortPrivate::connectAllSlots(){
    connectSignalAndSlotByNamesake(g_Widget, m_Parent);
    connectSignalAndSlotByNamesake(g_Multimedia, m_Parent);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);


    QObject::connect(m_Parent, SIGNAL(read_port_data(QByteArray )),
                     m_Parent,  SLOT(handlerData(QByteArray)),
                     type);
}


static QSerialPort::BaudRate getBaudRate(int baudRate){
    switch(baudRate){
        case 1200:
            return QSerialPort::Baud1200;
        case 2400:
            return QSerialPort::Baud2400;
        case 4800:
            return QSerialPort::Baud4800;
        case 9600:
            return QSerialPort::Baud9600;
        case 19200:
            return QSerialPort::Baud1200;
        case 38400:
            return QSerialPort::Baud38400;
        case 57600:
            return QSerialPort::Baud57600;
        case 115200:
            return QSerialPort::Baud115200;

    }

}

void PortPrivate::setPortName(const QString &name){
    m_portName = name;
}

QString PortPrivate::portName(){
    return m_portName;
}
void PortPrivate::setBaudRate(int baudRate){
    m_BaudRate = baudRate;
}
int PortPrivate::baudRate(){
    return m_BaudRate;
}
bool PortPrivate::isOpen(){
    return m_serialPort->isOpen();
}
bool PortPrivate::open(){
    if(m_serialPort->isOpen())
        return true;
    m_serialPort->setPortName(m_portName);
    m_serialPort->setBaudRate(m_BaudRate);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);
    m_serialPort->setReadBufferSize(1024);
    return m_serialPort->open(QSerialPort::ReadWrite);
}

bool PortPrivate::clear(){
    if(m_serialPort->isOpen()){
        m_serialPort->clear();
        this->close();
        return this->open();
    }
    return false;

}

void PortPrivate::close(){
    if(m_serialPort->isOpen())
        m_serialPort->close();
}

QByteArray PortPrivate::readData(){
    QByteArray Data = "";
    while(m_serialPort->waitForReadyRead(20))
    {
        Data += m_serialPort->readAll();
    }
    Data += m_serialPort->readAll();
    return Data;
}

int PortPrivate::writeData(char *buf, int size){
    int len = 0;
    forever{
        int n = m_serialPort->write(&buf[len], size - len);
        if(n == -1){
            return -1;
        }else{
            len += n;
            if(size == len)
                break;
        }

    }
    return len;
}
