#include "server.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  server::Server play_server;
  return a.exec();
}
