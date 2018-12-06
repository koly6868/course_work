#ifndef SERVER_2018
#define SERVER_2018

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "client.h"

class FileTcpServer : public QObject
{
  Q_OBJECT
public:
  explicit FileTcpServer(QObject *parent = nullptr, quint16 port = 6000);

  public slots:
  void slotNewConnection();
  void slotServerRead(QString str);
  void slotClientDisconnected();

private:
  QTcpServer * mTcpServer;
  Client * client;
};

#endif // !SERVER_2018

