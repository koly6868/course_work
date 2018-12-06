#include "server.h"
#include <QDebug>
#include <QCoreApplication>

FileTcpServer::FileTcpServer(QObject *parent, quint16 port) : QObject(parent)
{
  mTcpServer = new QTcpServer(this);

  connect(mTcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

  if (!mTcpServer->listen(QHostAddress::LocalHost, port))
  {
    qDebug() << "server is not started";
  }
  else
  {
    qDebug() << "server is started on port " << port;
  }
}

void FileTcpServer::slotNewConnection()
{
  QTcpSocket* sock = mTcpServer->nextPendingConnection();
  qDebug() << sock->state() <<  endl;
  Client new_client(this,sock);
  client = &new_client;
  qDebug() << "conected" << endl;
  client->sendMessage("hello");
  connect(client, SIGNAL(whenRecivedBytes(QString)), this, SLOT(slotServerRead(QString)));
  //connect(mTcpSocket, &QTcpSocket::disconnected, this, &FileTcpServer::slotClientDisconnected);
}

void FileTcpServer::slotServerRead(QString str)
{
    qDebug() << "reading" << endl;
    client->sendMessage(str.toUtf8());

}

void FileTcpServer::slotClientDisconnected()
{
    qDebug() << "disconected" << endl;
  //mTcpSocket->close();
}

