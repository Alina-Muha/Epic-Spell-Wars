#include <QTcpSocket>

#include "client.h"
#include "start_window.h"
#include "board.h"
#include "controller.h"

namespace client {
Client::Client(QHostAddress ip_, qint16 port_, QString name_, QObject *parent)
    : QObject(parent),
      socket(new QTcpSocket(this)),
      ip(ip_),
      port(port_),
      name(name_)
{
    QObject::connect(socket, &QTcpSocket::connected, this, &Client::on_connected);
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Client::on_ready_read);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Client::disconnect);
}

void Client::set_name(QString name_) {
    name = name_;
}

void Client::send_name() {
    auto request = controller::Request(1);
    request.set_name(name);
    Data = request.to_json_object();
    send_json();
}

void Client::connect() {
    socket->connectToHost(ip, port);
    send_name();
}

void Client::send_start_signal() {
    auto request = controller::Request(2);
    Data = request.to_json_object();
    send_json();
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
    QJsonDocument doc(Data);
    client_stream << doc.toJson();
}

void Client::get_json(){

}

void Client::json_received(const QJsonObject &json_data) {
    const QJsonValue type =json_data.value(QString("type"));
    qDebug() << QString("New request, type: %1").arg(type.toString());
    if (type != 5) {
        auto request = controller::Request(json_data);
    } else /* type == 5 */ {
        auto request = controller::СardPlayedResult(json_data);
    }
}

void Client::on_ready_read() {
    QByteArray byte_data;
    QDataStream socket_stream(socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);
    if (socket_stream.status() == QDataStream::Ok) {
        for(;;) {
            socket_stream >> byte_data;
            QJsonObject json_data = QJsonDocument::fromJson(byte_data).object();
            json_received(json_data);
        }
    }
}



}  // namespace client

