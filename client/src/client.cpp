#include <QTcpSocket>

#include "client.h"
#include "start_window.h"
#include "board.h"

namespace client {
Client::Client(QHostAddress ip_, qint16 port_, QString name_, QObject *parent)
    : QObject(parent),
      socket(new QTcpSocket(this)),
      ip(ip_),
      port(port_),
      name(name_)
{
    QObject::connect(socket, &QTcpSocket::connected, this, &Client::connected);
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Client::on_ready_read);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

void Client::set_name(QString name_) {
    name = name_;
}

void Client::connect() {
    socket->connectToHost(ip, port);
    // send name to server
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

