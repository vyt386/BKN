#include "PortControl.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QtTest/QTest>
#include <QBitArray>
#define RPPP_PACKET_SIMBOL			(0x7E)
// Символ замены
#define RPPP_REPLACE_SIMBOL			(0x7D)


// Максимальная длина служебных данных пакета (начало + crc16 (7E 7E) + конец)
#define RPPP_MAX_SERVICE_DATA_SIZE	(1 + 2 * 2 + 1)
// Максимальный размер данных в пакете
#define RPPP_MAX_DATA_SIZE			((0xFFFF - RPPP_MAX_SERVICE_DATA_SIZE) / 2)
// Возвращает максимальный размер пакета в байтах для передачи массива
// данных _array
//#define RPPP_max_packet_size(_array) \
//	(RPPP_MAX_SERVICE_DATA_SIZE + 2 * _countof(_array))

PortControl::PortControl(QObject *parent)
    : QObject(parent)
    , m_port(nullptr)
{

m_port=new QSerialPort(this);
connect(m_port,SIGNAL(readyRead()),this,SLOT(read()));

}

void PortControl::connectt(){
    ReadPortParameter();
}
void PortControl::ReadPortParameter(){
int i=0;
 foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {

 Portlist << info.portName();

 PortSpeed.portname[i]= info.portName();
 i++;
}
          QString response("123");
          t=Portlist.size();
          //////////////////
          Speedlist<<QStringLiteral("9600"),QSerialPort::Baud9600;
          Speedlist<<QStringLiteral("19200"), QSerialPort::Baud19200;
          Speedlist<<QStringLiteral("38400"), QSerialPort::Baud38400;
          Speedlist<< QStringLiteral("115200"), QSerialPort::Baud115200;
          Speedlist<< QStringLiteral("Custom");
          //////////////////
          StopBitlist<<QStringLiteral("1"), QSerialPort::OneStop;
          StopBitlist<<QStringLiteral("2"), QSerialPort::TwoStop;
          StopBitlist<<QStringLiteral("1.5"), QSerialPort::OneAndHalfStop;





}

void PortControl::SetPortParam(const QString &portName,QString speed,QString stopbits){
    if (!m_port) {
        m_port = new QSerialPort(portName);
       // connect(m_port, SIGNAL(readyRead()), SLOT(readData()));
    } else {
        m_port->close();
        m_port->setPortName(portName);
    }

  //  m_port->setPortName("COM2");
    m_port->setBaudRate(static_cast<QSerialPort::BaudRate>(speed.toInt()));
    m_port->setStopBits(static_cast<QSerialPort::StopBits>(stopbits.toInt()));
    //m_port->setDataBits("8");
}

void PortControl::ConnectPort(){
//quint8 mydata[] = {0xC8,0x16,0x7E};
//    quint8 packet;
//quint8 mydata1[100];
//quint8 packet1=make_raw_data(mydata,sizeof(mydata),mydata1);
   // QByteArray array;
   // QString str="C8167E";
//        array.resize(3);
//         array[0] = 0xC8;
//       array[1] = 0x16;
//       array[2] = 0x7E;

   // QByteArray array = QByteArray::fromHex("C8167E");
 //   int k=array.size();
//make_raw_data1(array,array.length(),array1);

   //QString str="x^16 + x^15 + x^2 + 1";
   // crc16_modbus(mydata,sizeof(mydata));
    QString error1=tr("Ошибка открытия порта");

    if (m_port->open(QIODevice::ReadWrite)) {
         connect(m_port,SIGNAL(readyRead()),this,SLOT(read()));
//            ui->actionConnect->setEnabled(false);
//            ui->actionDisconnect->setEnabled(true);
//ui->statusBar->showMessage(tr("Connect"));

    } else {
       emit error(error1);

    }


 // writePort(str);
  //readPort();
}
void PortControl::writePort(QString writedata){
   QByteArray array;
    array.resize(6);
           array[0] = 0x7E;
           array[1] = 0x01;
           array[2] = 0x7D;
           array[3] = 0x5E;
           array[4] = 0x80;
           array[5] = 0x7E;

// QByteArray writedat=writedata.toUtf8();
   //QByteArray array = QByteArray::fromHex(writedat);
  //  QByteArray array =writedata.toInt(&ok,16);
    QByteArray array1;
  //  make_raw_data1(array,array.length(),array1);
 //   m_port->write(packet_data1);
    m_port->write(array);
array1=m_port->readAll();
    //  receivedData();
   // QByteArray data=writedata.toLocal8Bit();


//m_port->write(writedat);

}

void PortControl::readPort(){

//    QByteArray data=m_port->readAll();

}
void PortControl::read(){
    QByteArray data=m_port->read(6);

    emit readdata(data);

}
PortControl::~PortControl()
{
    delete m_port;
}

quint16 PortControl::crc16_modbus1(QByteArray data,quint32 len){

    static const quint16 wCRCTable[] = {
    0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
    0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
    0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
    0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
    0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
    0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
    0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
    0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
    0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
    0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
    0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
    0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
    0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
    0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
    0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
    0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
    0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
    0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
    0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
    0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
    0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
    0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
    0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
    0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
    0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
    0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
    0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
    0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
    0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
    0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
    0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
    0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };
    quint8 nTemp;
    quint16 wCRCWord = 0xFFFF;
//wCRCWord=qChecksum(array,array.length());

   for (int i=0; i < len;++i)
      {
          nTemp = (quint8)data.at(i) ^ wCRCWord;
          wCRCWord >>= 8;
          wCRCWord ^= wCRCTable[nTemp];
       }
       return wCRCWord;
}
quint16 PortControl::crc16_byte( quint16 crc,quint8 byte)
{static const quint16 wCRCTable[] = {
        0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241,
        0XC601, 0X06C0, 0X0780, 0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440,
        0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1, 0XCE81, 0X0E40,
        0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841,
        0XD801, 0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40,
        0X1E00, 0XDEC1, 0XDF81, 0X1F40, 0XDD01, 0X1DC0, 0X1C80, 0XDC41,
        0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680, 0XD641,
        0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040,
        0XF001, 0X30C0, 0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240,
        0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501, 0X35C0, 0X3480, 0XF441,
        0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
        0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840,
        0X2800, 0XE8C1, 0XE981, 0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41,
        0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1, 0XEC81, 0X2C40,
        0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640,
        0X2200, 0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041,
        0XA001, 0X60C0, 0X6180, 0XA141, 0X6300, 0XA3C1, 0XA281, 0X6240,
        0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480, 0XA441,
        0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41,
        0XAA01, 0X6AC0, 0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840,
        0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01, 0X7BC0, 0X7A80, 0XBA41,
        0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
        0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640,
        0X7200, 0XB2C1, 0XB381, 0X7340, 0XB101, 0X71C0, 0X7080, 0XB041,
        0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0, 0X5280, 0X9241,
        0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440,
        0X9C01, 0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40,
        0X5A00, 0X9AC1, 0X9B81, 0X5B40, 0X9901, 0X59C0, 0X5880, 0X9841,
        0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81, 0X4A40,
        0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41,
        0X4400, 0X84C1, 0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641,
        0X8201, 0X42C0, 0X4380, 0X8341, 0X4100, 0X81C1, 0X8081, 0X4040 };
     //QByteArray array = QByteArray::fromRawData(data, sizeof(data));
   //QByteArray array[0xC8];
//    //QByteArray array=str.toUtf8();
//   QByteArray array;
//     array.resize(3);
//      array[0] = 0xC8;
//    array[1] = 0x16;
//   array[2] = 0x7E;
   //  ba[3] = 0x18;
    // ba[4] = 0xca;



      return (crc >> 8) ^ wCRCTable[(crc & 0xFF) ^ byte];
}

//qint16 PortControl::make_raw_data(const quint8 *data, quint16 len, quint8 *packet_data){
//    // Проверяем аргументы
//quint8 mydata[] = {0xC8,0x16,0x7E};
//        //if(len && !data) return 0;
//      //  if(!packet_data) return 0;
//       // if(len > RPPP_MAX_DATA_SIZE) return 0;

//        // Ещё один указатель на данные пакета
//        quint8* pd = packet_data;

//        // Формируем заголовок пакета
//        *pd++ = RPPP_PACKET_SIMBOL;
//        // Данные пакета
//        for(quint16 i = 0; i < len; i++)
//        {
//            if((data[i] != RPPP_PACKET_SIMBOL) && (data[i] != RPPP_REPLACE_SIMBOL))
//            {
//                *pd++ = data[i];
//            }
//            else
//            {
//                *pd++ = RPPP_REPLACE_SIMBOL;
//                *pd++ = data[i] ^ 0x20;
//            }
//        }
//        // Контрольная сумма
//       quint16 crc = crc16_modbus(mydata,sizeof(mydata));
//       quint8 crc_lo = (crc & 0x00FF) >> 0;
//        quint8 crc_hi = (crc & 0xFF00) >> 8;
//        if((crc_lo != RPPP_PACKET_SIMBOL) && (crc_lo != RPPP_REPLACE_SIMBOL))
//        {
//            *pd++ = crc_lo;
//        }
//        else
//        {
//            *pd++ = RPPP_REPLACE_SIMBOL;
//            *pd++ = crc_lo ^ 0x20;
//        }
//        if((crc_hi != RPPP_PACKET_SIMBOL) && (crc_hi != RPPP_REPLACE_SIMBOL))
//        {
//            *pd++ = crc_hi;
//        }
//        else
//        {
//            *pd++ = RPPP_REPLACE_SIMBOL;
//            *pd++ = crc_hi ^ 0x20;
//        }
//        // Окончание пакета
//        *pd++ = RPPP_PACKET_SIMBOL;

//        // Возвращаем общую длину пакета
//        return (pd - packet_data);

//}
qint16 PortControl::make_raw_data1(QByteArray data, quint16 lenhth,QByteArray packet_data){
    quint8 PacketSimbol = 0x7E;

    quint8 ReplaceSimbol = 0x7D;
    // Пока возвращаемого массива нет
    //packet_data = null;
    // Проверяем аргументы
//    if (data == null) return 0;
//    if (data.Length < length) return 0;
//    if (length > MaxDataSize) return 0;

    // Контрольная сумма данных
    quint16 crc = crc16_modbus1(data,data.length());
    quint8 crc_lo = (crc & 0x00FF) >> 0;
     quint8 crc_hi = (crc & 0xFF00) >> 8;
     //int len;
    // Сначала считаем размер формирующегося пакета, для этого
    // складываем байт начала, байт конца, данные пакета и 2 байта
    // контрольной суммы, при этом саем по 2 байта каждый раз,
    // когда встречается символ PacketSimbol или ReplaceSimbol
    quint16 len;
            len= 1 + 2 + 1;
    if ((crc_lo == PacketSimbol) || (crc_lo == ReplaceSimbol)) len++;
    if ((crc_hi ==PacketSimbol) || (crc_hi == ReplaceSimbol)) len++;

    len +=lenhth;
    for (quint16 i = 0; i < lenhth; i++)
    {
        if ((data[i] == (char)PacketSimbol) || (data[i] == (char)ReplaceSimbol)) len++;
    }

    // Создаём данные пакета
    //QByteArray packet_data1;

    // Индекс байта данных в пакете
    quint16 pd = 0;

    // Формируем заголовок пакета
    packet_data1[pd++] = (char)PacketSimbol;
    // Данные пакета
    for (quint16 i = 0; i < lenhth; i++)
    {
        if ((data[i] !=(char) PacketSimbol) && (data[i] !=(char) ReplaceSimbol))
        {
            packet_data1[pd++] = data[i];
        }
        else
        {
            packet_data1[pd++] = (char)ReplaceSimbol;
            packet_data1[pd++] = (char)(data[i] ^ 0x20);
        }
    }
    // Контрольная сумма
    if ((crc_lo != PacketSimbol) && (crc_lo != ReplaceSimbol))
    {
        packet_data1[pd++] = (char)crc_lo;
    }
    else
    {
        packet_data1[pd++] = (char)ReplaceSimbol;
        packet_data1[pd++] = (char)(crc_lo ^ 0x20);
    }
    if ((crc_hi != PacketSimbol) && (crc_hi != ReplaceSimbol))
    {
        packet_data1[pd++] = (char)crc_hi;
    }
    else
    {
        packet_data1[pd++] = (char)ReplaceSimbol;
        packet_data1[pd++] = (char)(crc_hi ^ 0x20);
    }
    // Окончание пакета
    packet_data1[pd++] = (char)PacketSimbol;

    // Возвращаем общую длину пакета
    return len;

}

void PortControl::receivedData(){
    QString writedata="7EC8167D5E7D5E7D5E7E";
 quint8 maxlen=writedata.length();
 quint16 MaxDataSize = ((0xFFFF - 6) / 2);
    buf.resize(52);
     //QByteArray array=writedata.toUtf8();
    QByteArray array=m_port->readAll();

    QByteArray data = QByteArray::fromHex(array);


quint8 new_byte;
        for (int i=0;i<=data.length();i++){
           new_byte= data[i];
        receivedByteData(new_byte);
        }
}
   bool PortControl::receivedByteData(quint8 new_byte){


       quint8 PacketSimbol = 0x7E;
quint8 maxLen=11;
       quint8 ReplaceSimbol = 0x7D;

        // Пакет пока не считан
                    //data = null;
                    // Пишем пришедший байт
                    buf[writePointer] =new_byte ;
                    // Перемещаем указатель записи
                    writePointer++;
                    if(writePointer == buf.length()) writePointer = 0;

                    // Если начало предполагаемого пакета ещё не найдено
                    if(!startFound)
                    {
                        // Если нашли байт начала пакета, то
                        if(new_byte == PacketSimbol)
                        {
                            // Считаем, что нашли начало пакета
                            startFound = true;
                            // Запоминаем место начала пакета (уже после символа
                            // начала пакета)
                            startPointer = writePointer;
                            // Сбрасываем флаг замены
                            replaceFlag = false;
                            // Реальное количество байт данных
                            realBytesCount = 0;
                        }
                    }
                    // Если начало предполагаемого пакета уже найдено
                    else
                    {
                        // Если новый символ - символ замены, то
                        if(new_byte == ReplaceSimbol)
                        {
                            // Если не установлен флаг замены, то
                            if(replaceFlag == false)
                            {
                                // Устанавливаем
                                replaceFlag = true;
                            }
                            // Если уже установлен, то
                            else
                            {
                                // Значит ошибка, поэтому считаем, что начало пакета не
                                // найдено, потому что этот пакет уже неверный
                                startFound = false;
                                // Выходим
                                return false;
                            }
                        }

                        // Если какой-то другой символ, кроме байта конца пакета, то
                        else if(new_byte != PacketSimbol)
                        {
                            // Снимаем флаг инверсии
                            replaceFlag = false;
                            // Увеличиваем счётчик реального количества байт данных
                            realBytesCount++;
                        }
                        // Если новый символ является байтом конца пакета, то
                        else if(new_byte == PacketSimbol)
                        {
                            // Если установлен флаг замены или количество данных
                            // менее 2-х байт, то
                            if((replaceFlag == true) || (realBytesCount < 2)
                                || ((realBytesCount - 2) > maxLen))
                            {
                                // Считаем, что пакет неверный, но, возможно только что
                                // найденный символ - это начало верного пакета, поэтому
                                // переносим указатель начала на это место (будет считаться
                                // началом этого пакета)
                                startPointer = writePointer;
                                // Сбрасываем флаг замены
                                replaceFlag = false;
                                // Реальное количество байт данных
                                realBytesCount = 0;
                                // Выходим
                                return false;
                            }

                            // Считываем все байты данных пакета от самого начала
                            // и расчитываем контрольную сумму:
                            // Позиция чтения
                            quint16 tmp_pointer = startPointer;
                            // Флаг замены
                            replaceFlag = false;
                            // Расчётная контрольная сумма
                            quint16 calc_crc = crc16_modbus1(NULL, 0);
                            // Счётчик считанных байт данных
                            quint16 data_bytes_count = 0;
                            // Пока не считано (realBytesCount - 2) байт данных
                            while(data_bytes_count < (realBytesCount - 2))
                            {
                                // Читаем байт
                               quint8 tmp_byte = buf[tmp_pointer];
                                // Увеличиваем позицию чтения
                                tmp_pointer++;
                                if(tmp_pointer == buf.length()) tmp_pointer = 0;
                                // Если байт - символ замены, то
                                if(tmp_byte == ReplaceSimbol)
                                {
                                    // Ставим флаг замены следующего символа
                                    replaceFlag = true;
                                }
                                // Если не байт замены символа, то
                                else
                                {
                                    // Инверсируем его 6-й бит если надо
                                    if(replaceFlag)
                                    {
                                        tmp_byte ^= 0x20;
                                        replaceFlag = false;
                                    }
                                    // Пересчитываем CRC
                                    calc_crc = crc16_byte(calc_crc, tmp_byte);
                                    // Увеличиваем счётчик байт данных
                                    data_bytes_count++;
                                }
                            }

                            // Читаем значение контрольной суммы:
                            // Флаг замены
                            replaceFlag = false;
                            // Счётчик считанных байт CRC
                            quint16 crc_bytes_count = 0;
                            // Байты контрольной суммы
                           // QByteArray crc_bytes[2] = {0x00, 0x00};
                            quint8 crc_bytes[2]={0x00, 0x00};

                            // Пока не считано 2 байта контрольной суммы
                            while(crc_bytes_count < 2)
                            {
                                // Читаем байт
                               quint8 tmp_byte = buf[tmp_pointer];
                                // Увеличиваем позицию чтения
                                tmp_pointer++;
                                if(tmp_pointer == buf.length()) tmp_pointer = 0;
                                // Если байт - символ замены, то
                                if(tmp_byte == ReplaceSimbol)
                                {
                                    // Ставим флаг замены следующего символа
                                    replaceFlag = true;
                                }
                                // Если не байт замены символа, то
                                else
                                {
                                    // Инверсируем его 6-й бит если надо
                                    if(replaceFlag)
                                    {
                                        tmp_byte ^= 0x20;
                                        replaceFlag = false;
                                    }
                                    // Запоминаем байт CRC
                                    crc_bytes[crc_bytes_count] = tmp_byte;
                                    // Увеличиваем счётчик байт CRC
                                    crc_bytes_count++;
                                }
                            }
                            // Определяем значение контрольной суммы по считанным байтам
                            quint16 pa=crc_bytes[0] << 0;
                            quint16 pa1=crc_bytes[1] << 8;
                            quint16 packet_crc = quint16((crc_bytes[0] << 0) |
                                                (crc_bytes[1] << 8));

                            // Сравниваем расчитанную и принятую контрольные суммы:
                            // если они не равны, то
                            if(packet_crc != calc_crc)
                            {
                                // Считаем, что пакет неверный, но, возможно только что
                                // найденный символ - это начало верного пакета, поэтому
                                // переносим указатель начала на это место (будет считаться
                                // началом этого пакета)
                                startPointer = writePointer;
                                // Сбрасываем флаг замены
                                replaceFlag = false;
                                // Реальное количество байт данных
                                realBytesCount = 0;
                                // Выходим
                                return false;
                            }

                            // Теперь считываем все байты пакета от самого начала
                            // и копируем их в массив для возврата считанного пакета
                            // Позиция чтения
                            tmp_pointer = startPointer;
                            // Флаг замены
                            replaceFlag = false;
                            // Счётчик считанных байт данных
                            data_bytes_count = 0;
                            // Создаём массив с данными
                          // QByteArray data[realBytesCount - 2];
                           QByteArray data;
                            // Пока не считано (realBytesCount - 2) байт данных
                            while(data_bytes_count < (realBytesCount - 2))
                            {
                                // Читаем байт
                                quint8 tmp_byte = buf[tmp_pointer];
                                // Увеличиваем позицию чтения
                                tmp_pointer++;
                                if(tmp_pointer == buf.length()) tmp_pointer = 0;
                                // Если байт - символ замены, то
                                if(tmp_byte == ReplaceSimbol)
                                {
                                    // Ставим флаг замены следующего символа
                                    replaceFlag = true;
                                }
                                // Если не байт замены символа, то
                                else
                                {
                                    // Инверсируем его 6-й бит если надо
                                    if(replaceFlag)
                                    {
                                        tmp_byte ^= 0x20;
                                        replaceFlag = false;
                                    }
                                    // Запоминаем этот байт
                                    data[data_bytes_count] = tmp_byte;
                                    // Увеличиваем счётчик байт данных
                                    data_bytes_count++;
                                }
                            }

                            // Было ли найдено начало пакета
                            startFound = false;
                            // Начало пакета
                            startPointer = 0;
                            // Реальное количество байт данных
                            realBytesCount = 0;
                            // Выходим
                            return true;
                        }
                    }

                    // Выходим
                    return false;




}
