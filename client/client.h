#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QtCore>
#include <QHostAddress>


class Client : public QObject
{
  Q_OBJECT
public:
  Client(QObject *parent = nullptr, quint16 port = 6001);
  Client(QObject *parent, QTcpSocket* socket);
  ~Client();
  bool ConnectToHost(QHostAddress adr, quint16 port);
  void sendMessage(QByteArray str);
  QByteArray ReadMessage();

  public slots:
  void onConnectionError();
  void onReciveBytes();

signals:
  void whenRecivedBytes(QString str);

private:
  QTcpSocket * socket_{ nullptr };
  quint32 block_size_{ 0 };
};


#endif // CLIENT_H
