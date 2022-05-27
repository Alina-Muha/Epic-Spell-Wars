#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QUdpSocket>
#include "controller.h"

namespace client {

    class Client {

    private:
        QTcpSocket *socket;
        QByteArray Data;

    public:
        Client();
        void connect(char* ip, int port);
        void send_json();
        void get_json();

    public slots:
        void slotReadyRead();


    };
}  // namespace client

#endif  // CLIENT_H
