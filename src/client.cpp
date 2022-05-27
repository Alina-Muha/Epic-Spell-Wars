#include <QTcpSocket>

#include "client.h"
#include "start_window.h"
#include "board.h"

namespace client {
Client::Client() {
    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

void Client::connect(char* ip, int port) {
    socket->connectToHost(ip, port);
}





}  // namespace client

