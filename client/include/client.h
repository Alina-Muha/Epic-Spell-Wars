#ifndef CLIENT_H
#define CLIENT_H

#include "board.h"
#include "controller.h"
#include "start_window.h"
#include <QDialog>
#include <QObject>
#include <QQueue>
#include <QString>
#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>

namespace client {

class Client : public QObject {

private:
  QTcpSocket *socket;
  QString name;
  bool is_game_started_flag;

  void json_received(const QJsonObject &doc);

public:
  explicit Client(QString name_ = "", QObject *parent = nullptr);
  void set_name(QString name_);
  QQueue<controller::Request> requestsQueue;
  void set_game_started_flag();
  bool is_game_started();
public slots:
  void connect(QString ip, qint16 port);
  void send_name();
  QString get_name();
  void send_start_signal();
  void send_json(QJsonObject Data);
  void disconnect();

private slots:
  void on_connected();
  void on_disconnected();
  void on_ready_read();

signals:
  void connected();
  void disconnected();
};
} // namespace client

#endif // CLIENT_H
