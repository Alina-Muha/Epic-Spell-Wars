#include "server.h"
#include <QDebug>
#include <QCoreApplication>
namespace server{
server::server(QObject *parent) : QObject(parent){
    tcp_server = new QTcpServer(this);
    connect(tcp_server, &QTcpServer::newConnection, this, &server::new_connection);
    if (!tcp_server->listen(QHostAddress::Any, 5040)){
        qDebug() << "Not listening\n";
    }
    else{
        qDebug() << "Listening\n";
    }
}
void server::new_connection(){
    const auto client = tcp_server -> nextPendingConnection();
    if (client == nullptr){
        return;
    }
    client->write("Hello!\n");
    clients.insert(this->get_client(client), client);
    connect(client, &QTcpSocket::readyRead, this, &server::read_connection);
    connect(client, &QTcpSocket::disconnected, this, &server::disconnection);
}
void server::read_connection(){
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if (client == nullptr){
        return;
    }
    const auto name = client->readAll();
}
void server::disconnection(){
    const auto client = qobject_cast<QTcpSocket*>(sender());

    client->close();
    clients.remove(this->get_client(client));
}
int server::get_cube_value(){
    const auto client = qobject_cast<QTcpSocket*>(sender());
    return client->readAll().toInt();
}
QString server::get_client(const QTcpSocket *client) const{
    return client->peerName();
}
}