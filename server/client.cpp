#include "client.h"



Client::Client(QObject *parent, quint16 port)
  : QObject(parent)
  , block_size_(0)
{
  socket_ = new QTcpSocket(this);
  socket_->bind(QHostAddress::LocalHost, port);
  connect(socket_, SIGNAL(onConnectionError()), this, SLOT(onConnectionError()));
  connect(socket_, SIGNAL(readyRead()), this, SLOT(onReciveBytes()));
  qDebug() << block_size_;
};



Client::Client(QObject* parent, QTcpSocket* socket)
    : QObject (parent)
    , block_size_(0)
{
    socket_ = socket;
    qDebug() << socket_->state();
    connect(socket_, SIGNAL(onConnectionError()), this, SLOT(onConnectionError()));
    connect(socket_, SIGNAL(readyRead()), this, SLOT(onReciveBytes()));
}



Client::~Client()
{
  qDebug() << "Client deleted" << endl;
  socket_->close();
};



void Client::sendMessage(QByteArray message)
{
  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out << static_cast<quint32>(0); //резерв на размер блока
  out << message;
  out.device()->seek(0); // возврат в начало
  out << static_cast<quint32>(block.size() - sizeof(quint32));

  socket_->write(block);
  if(socket_->waitForBytesWritten(1000)) qDebug() << "Message is sended" << endl;
};


bool Client::ConnectToHost(QHostAddress adr, quint16 port)
{
  socket_->open(QIODevice::ReadWrite);
  socket_->connectToHost(adr, port);
  if (socket_->waitForConnected(3000))
  {
    qDebug() << "Ready to work";
  }
  else
  {
    qDebug() << "Not open";
  }
  return true;
};



void Client::onConnectionError()
{
  qDebug() << "not conected" << endl;
}



void Client::onReciveBytes()
{
  qDebug() << "Client: reading message" << endl;
  QDataStream in(socket_);
  if (block_size_ == 0)
  {
    if (socket_->bytesAvailable() < sizeof(quint32))
    {
      return;
    }
    in >> block_size_;
    qDebug() << "block size: " << block_size_  << endl;
  }
  if (socket_->bytesAvailable() >= block_size_)
  {
    char* mes = new char[block_size_];
    in.readBytes(mes, block_size_);
    QString res(mes);
    qDebug() << res << endl;
    emit whenRecivedBytes(res);
    block_size_ = 0;
  }
}



