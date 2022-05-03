#include "server.h"
#include <QDebug>
#include <QCoreApplication>
namespace server{
server::server(QObject *parent) : QObject(parent){
    tcp_server = new QTcpServer(this);
    connect(tcp_server, &QTcpServer::newConnection, this, &server::new_connection);
    if (!tcp_server->listen(QHostAddress::Any, 3300)){
        qDebug() << "connection not started\n";
    }
    else{
        qDebug() << "connection started\n";
    }
}
void server::new_connection(){
    tcp_socket = tcp_server->nextPendingConnection();
    tcp_socket->write("OK\n");
    connect(tcp_socket, &QTcpSocket::readyRead, this, &server::read_connection);
    connect(tcp_socket, &QTcpSocket::disconnected, this, &server::disconnection);
}
void server::read_connection(){
    while(tcp_socket->bytesAvailable() > 0){
        QByteArray array = tcp_socket -> readAll();
        tcp_socket->write(array);
    }
}
void server::disconnection(){
    tcp_socket -> close();
}
}


