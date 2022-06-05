#include "client.h"
#include "board.h"
#include "start_window.h"

using namespace controller;

namespace client {
Client::Client(QString name_, QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this)), name(name_),
      is_game_started_flag(false) {
  QObject::connect(socket, &QTcpSocket::connected, this, &Client::on_connected);
  QObject::connect(socket, &QTcpSocket::readyRead, this,
                   &Client::on_ready_read);
  QObject::connect(socket, &QTcpSocket::disconnected, this,
                   &Client::disconnect);
}

void Client::set_game_started_flag() { is_game_started_flag = true; }

bool Client::is_game_started() { return is_game_started_flag; }

void Client::set_name(QString name_) { name = name_; }

QString Client::get_name() { return name; }

void Client::send_name() {
  auto request = Request(types::name);
  request.set_name(name);
  send_json(request.to_json_object());
}

void Client::connect(QString ip, qint16 port) {
  socket->connectToHost(QHostAddress(ip), port);
}

void Client::send_start_signal() {
  auto request = Request(types::start);
  send_json(request.to_json_object());
}

void Client::on_connected() { QDataStream out(); }

void Client::disconnect() { socket->disconnectFromHost(); }

void Client::send_json(QJsonObject Data) {
  QDataStream client_stream(socket);
  client_stream.setVersion(QDataStream::Qt_6_2);
  QJsonDocument doc(Data);
  client_stream << doc.toJson();
}

void Client::json_received(const QJsonObject &json_data) {
  auto request = controller::Request(json_data);
  requestsQueue.push_back(request);
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
      const QJsonDocument jsonDoc =
          QJsonDocument::fromJson(byte_data, &parseError);
      if (parseError.error == QJsonParseError::NoError) {
        if (jsonDoc.isObject()) {
          json_received(jsonDoc.object());
        }
      }
    } else {
      break;
    }
  }
}

} // namespace client
