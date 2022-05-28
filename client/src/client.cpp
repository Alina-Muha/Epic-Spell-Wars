#include <QTcpSocket>

#include "client.h"
#include "start_window.h"
#include "board.h"

namespace client {
Client::Client(QObject *parent)
    : QObject(parent),
      socket(new QTcpSocket(this))
{
    QObject::connect(socket, &QTcpSocket::connected, this, &Client::connected);
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Client::on_ready_read);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

void Client::connect(const QHostAddress &ip, qint16 port) {
    socket->connectToHost(ip, port);
}

void Client::on_connected(){
    QDataStream out();
}

void Client::disconnect() {
    socket->disconnectFromHost();
}


void Client::send_json() {
    QDataStream client_stream(socket);
    client_stream.setVersion(QDataStream::Qt_6_2);
    client_stream << Data;
    Data.clear();
}

void Client::get_json(){

}

void Client::json_received(const QJsonObject &doc) {
    const QJsonValue type_val = doc.value(QString("type"));
}

void Client::on_ready_read() {
    QByteArray jsonData;
    QDataStream socket_stream(socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);
    if (socket_stream.status() == QDataStream::Ok) {
        for(;;) {
            socket_stream >> jsonData;
            // распарсить json;

        }
    }
}



}  // namespace client

