#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QDialog>
#include <QUdpSocket>
#include "controller.h"

namespace client {

    class Client : public QObject {

    private:
        QTcpSocket *socket;
        QByteArray Data;
        QString name;

    public:
        explicit Client(QObject *parent);
        void connect(char* ip, int port);
        void send_json();
        void get_json();

    private slots:
        void on_connected();
        void on_disconnected();
        void slot_ready_read();



    };
}  // namespace client

#endif  // CLIENT_H
