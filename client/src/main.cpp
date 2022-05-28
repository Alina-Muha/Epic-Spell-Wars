#include "start_window.h"
#include "client.h"
#include <QApplication>
#include <QQmlContext>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto c = new client::Client(nullptr);
    Start_window w(c);
    w.show();
    return a.exec();
}
