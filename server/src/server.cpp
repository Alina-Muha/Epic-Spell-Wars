#include "server.h"
#include <QDebug>
#include <QCoreApplication>
namespace server{
Server::Server(QObject *parent) : QObject(parent){
    tcp_server = new QTcpServer(this);
    connect(tcp_server, &QTcpServer::newConnection, this, &Server::new_connection);
    if (!tcp_server->listen(QHostAddress::Any, 5040)){
        qDebug() << "Not listening\n";
    }
    else{
        qDebug() << "Listening\n";
    }
}
void Server::new_connection(){
    const auto client = tcp_server -> nextPendingConnection();
    if (client == nullptr){
        return;
    }
    client->write("Hello!\n");
    clients.insert(this->get_client(client), client);
    connect(client, &QTcpSocket::readyRead, this, &Server::read_connection);
    connect(client, &QTcpSocket::disconnected, this, &Server::disconnection);
}
void Server::read_connection(){
    const auto client = qobject_cast<QTcpSocket*>(sender());
    if (client == nullptr){
        return;
    }
    const auto name = client->readAll();
}
void Server::disconnection(){
    const auto client = qobject_cast<QTcpSocket*>(sender());

    client->close();
    clients.remove(this->get_client(client));
}
int Server::get_cube_value(){
    const auto client = qobject_cast<QTcpSocket*>(sender());
    return client->readAll().toInt();
}
QString Server::get_client(const QTcpSocket *client) const{
    return client->peerName();
}
}