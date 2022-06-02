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

QString Client::get_name() {
    return name;
}

void Client::send_name() {
    auto request = controller::Request(1);
    request.set_name(name);
    send_json(request.to_json_object());
}

void Client::connect() {
    socket->connectToHost(ip, port);
    send_name();
}

void Client::send_start_signal() {
    auto request = controller::Request(2);
    send_json(request.to_json_object());
}

void Client::on_connected(){
    QDataStream out();
}

void Client::disconnect() {
    socket->disconnectFromHost();
}


void Client::send_json(QJsonObject Data) {
    QDataStream client_stream(socket);
    client_stream.setVersion(QDataStream::Qt_6_2);
    QJsonDocument doc(Data);
    client_stream << doc.toJson();
}

void Client::json_received(const QJsonObject &json_data) {
    auto request = controller::Request(json_data);
    qDebug() << "in client type: " << request.get_type();
    requestsQueue.push_back(request);
    qDebug() << "in client size of queue " <<requestsQueue.size() << "\n";
}

void Client::on_ready_read() {
    QByteArray byte_data;
    QDataStream socket_stream(socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);

    socket_stream.setVersion(QDataStream::Qt_6_2);
    while (true) {
        socket_stream.startTransaction();
        socket_stream >> byte_data;
        if (socket_stream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(byte_data, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject()) {
                    json_received(jsonDoc.object());
                }
                else {
//                    emit log_message("Invalid message: " + QString::fromUtf8(byte_data));
                }
            } else {
//                emit log_message("Invalid message: " + QString::fromUtf8(byte_data));
            }
        } else {
            break;
        }
    }
}

}  // namespace client

