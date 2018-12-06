#include <QObject>
#include <QtCore>
#include <QtNetwork>
#include <iostream>
#include <QApplication>
#include "data_pont.h"
#include "client.h"

int main(int argc, char** argv)
{
  QCoreApplication a(argc, argv);


  Client client(nullptr, 6009);
  client.ConnectToHost(QHostAddress::LocalHost, 6000);
  std::string inp;
  while (inp != "exit")
  {
  std::cin >> inp;
  std::cout << inp << " sended" << endl;
  
  client.sendMessage(QString(inp.c_str()).toUtf8());
  }
  

  return a.exec();
}





