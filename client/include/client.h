#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QDialog>
#include <QQueue>
#include <QUdpSocket>
#include "controller.h"

namespace client {

    class Client : public QObject {

    private:
        QTcpSocket *socket;
        QHostAddress ip;
        qint16 port;
        QString name;
        bool is_game_started_flag;


        void json_received(const QJsonObject &doc);

    public:
        explicit Client(QHostAddress ip_, qint16 port_, QString name_ = "", QObject *parent=nullptr);
        void set_name(QString name_);
        QQueue<controller::Request> requestsQueue;
    public slots:
        void connect();
        void send_name();
        void set_game_started_flag();
        bool is_game_started();
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
}  // namespace client

#endif  // CLIENT_H
