//#include "start_window.h"
#include "server.h"
#include "client.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //auto c = new client::Client();
    //Start_window w(c);
    server::Server play_server;
    ////w.show();
    return a.exec();
}
