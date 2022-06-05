#include "server.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  server::Server play_server(1234); //(std::stoi(std::string(argv[1])));
  return a.exec();
}
