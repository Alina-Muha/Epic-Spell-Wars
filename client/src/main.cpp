#include "start_window.h"
#include "client.h"
#include <QApplication>
#include <QQmlContext>
#include<iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug() << "ip " << QHostAddress::LocalHost << "port " << 1234;
    std::shared_ptr<client::Client> ptr = std::make_shared<client::Client>();
    Start_window w(ptr, nullptr);
    w.show();
    return a.exec();
}
