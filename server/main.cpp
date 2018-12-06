#include <QCoreApplication>
#include "server.h"
#include <QTcpSocket>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileTcpServer server(&a, 6000);


    return a.exec();
}

