#include "start_window.h"
#include "server.h"
#include <QApplication>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Start_window w;
    server::server play_server;
    w.show();
    return a.exec();
}
