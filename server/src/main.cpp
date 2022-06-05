#include "server.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  server::Server play_server(1234);
  return a.exec();
}
