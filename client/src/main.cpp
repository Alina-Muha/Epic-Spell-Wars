#include <QApplication>
#include <QQmlContext>
#include<iostream>
#include "start_window.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QStringList paths(QApplication::libraryPaths());
    paths.append(".");
    QApplication::setLibraryPaths(paths);
    QApplication a(argc, argv);
    std::shared_ptr<client::Client> ptr = std::make_shared<client::Client>();
    Start_window w(ptr, nullptr);
    w.show();
    return a.exec();
}
