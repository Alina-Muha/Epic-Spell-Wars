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

void send_json() {

}

void get_json(){

}

void Client::slotReadyRead() {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {
        //Qstring name;
        //in >> name; // ????

    }
}



}  // namespace client

