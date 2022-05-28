#include "server.h"
#include <QDebug>
#include <QCoreApplication>
#include <QAbstractSocket>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
namespace server{
Server::Server (QObject *parent)
 : QObject(parent)
, m_server_socket(new QTcpSocket(this))
{
    connect(m_server_socket, &QTcpSocket::readyRead, this, &Server::receive_json);
    connect (m_server_socket, &QTcpSocket::disconnected, this, &Server::disconnected_from_client);
    connect(m_server_socket, &QAbstractSocket:: errorOccurred, this, &Server::error);
}
bool Server::set_socket_descriptor (qintptr socket_descriptor){
    return m_server_socket->setSocketDescriptor(socket_descriptor);
}
void Server::disconnect_from_client(){
    m_server_socket->disconnectFromHost();
}

QString Server::user_name() const{
    return m_user_name;
}

void Server::set_user_name(const QString &user_name)
{
   m_user_name = user_name;
}
void Server::receive_json(){
    QByteArray json_data;
    QDataStream socket_stream(m_server_socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);
    while (true) {
        socket_stream.startTransaction();
        socket_stream >> json_data;
        if (socket_stream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(json_data, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject())
                    emit json_received(jsonDoc.object());
                else
                    emit log_message("Invalid message: " + QString::fromUtf8(json_data));
            } else {
                emit log_message("Invalid message: " + QString::fromUtf8(json_data));
            }
        } else {
            break;
        }
    }
}
void Server::send_json(const QJsonObject &json){
    const QByteArray json_data = QJsonDocument(json).toJson(QJsonDocument::Compact);
    emit log_message("Sending to " + user_name() + " - " + QString::fromUtf8(json_data));
    QDataStream socket_stream(m_server_socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);
    socket_stream << json_data;
}
}
