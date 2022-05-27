#include <QTcpSocket>

#include "client.h"
#include "start_window.h"
#include "board.h"

namespace client {
Client::Client(QObject *parent)
    : QObject(parent) {
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(slot_ready_read()));
    connect(socket, SIGNAL(connected()), this, SLOT(on_connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(on_disconnected()));
}

void Client::connect(char* ip, int port) {
    socket->connectToHost(ip, port);
}

void Client::on_connected(){
    QDataStream out()
}


void Client::send_json() {

}

void Client::get_json(){

}

void Client::slot_ready_read() {
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok) {


    }
}



}  // namespace client

