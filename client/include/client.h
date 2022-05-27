#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QString>
#include <QDialog>
#include <QUdpSocket>
#include "../../common/controller.h"

namespace client {

    class Client : public QObject {

    private:
        QTcpSocket *socket;
        QByteArray Data;
        QString name;
        void json_received(const QJsonObject &doc);

    public:
        explicit Client(QObject *parent=nullptr);
    public slots:
        void connect(const QHostAddress &ip, qint16 port);
        void send_json();
        void get_json();
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
