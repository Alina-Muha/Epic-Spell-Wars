#include "start_window.h"
#include "client.h"
#include <QApplication>
#include <QQmlContext>
#include<iostream>

QHostAddress read_ip(){
    std::string ip_string;
    std::cout << "Please, enter host address:\n";
    std::cin >> ip_string;
    QHostAddress ip_to_return = QHostAddress(QString::fromStdString(ip_string));
    return ip_to_return;
}

qint16 read_port(){
    qint16 port_to_return;
    std::cout << "Please, enter port number:\n";
    std::cin >> port_to_return;
    return port_to_return;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QHostAddress ip = read_ip();
    qint16 port = read_port();
    client::Client c(ip, port, "", nullptr);
    Start_window w(c);
    w.show();
    return a.exec();
}
