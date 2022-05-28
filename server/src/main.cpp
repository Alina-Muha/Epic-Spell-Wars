//#include "start_window.h"
#include "server.h"
#include "client.h"
#include <QApplication>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //auto c = new client::Client();
    //Start_window w(c);
    server::server play_server;
    ////w.show();
    return a.exec();
}
