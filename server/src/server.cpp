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
 : QObject(parent),
   m_server(new QTcpServer(this)),
   m_server_socket(new QTcpSocket(this))
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

QString Server::user_name(QTcpSocket *client_socket) const{
    return clients[client_socket];
}

void Server::set_user_name(QTcpSocket *client_socket, const QString &user_name)
{
   clients[client_socket] = user_name;
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
    emit log_message("Sending to - " + QString::fromUtf8(json_data));
    QDataStream socket_stream(m_server_socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);
    socket_stream << json_data;
}
void Server::accept_all_connections(){
    while (true){
        qDebug() << QString::fromUtf8("New Connection");
        QTcpSocket* client_socket = m_server->nextPendingConnection();
        clients[client_socket] = "";
        QJsonDocument doc = QJsonDocument::fromJson(client_socket->readAll());
        QJsonObject obj = doc.object();
        /*set_user_name(*client_socket, name); // name will be in json
        player = player::Player(name);
        players[name] = player; // in map players add new player with name
        round.set_players.emplace_back(player)
        if in json sent "game started":
            for (auto client : clients){
                send json "game started"
            }
            break; */
    }
}
void Server::give_cards_to_players(round_of_game::Round &round){
    round.distribute_cards();
    for (auto iter = clients.begin(); iter != clients.end();){
        std::shared_ptr<player::Player> player = players[user_name(iter.key())];
        /*player->get_cards();
        // write json: cards, lives = 20
        // send_json()*/
        iter++;
    }
}
void Server::fill_the_spell(round_of_game::Round &round){
    for (auto iter = clients.begin(); iter != clients.end();){
        QTcpSocket *client_socket = iter.key();
        std::shared_ptr<player::Player> player = players[user_name(iter.key())];
        /*recieve json with spell
        player->add_card_to_spell(); */
        iter++;
    }
}
void Server::complete_the_number_of_cards(round_of_game::Round &round){
    for (auto iter = clients.begin(); iter != clients.end();){
        QTcpSocket *client_socket = iter.key();
        std::shared_ptr<player::Player> player = players[user_name(iter.key())];
        int num_to_add = round.number_of_cards_in_hand - player->get_cards().size();
        // distribute_card(num_to_add)
        // send json
    }
}
void Server::applying_of_card_functions(round_of_game::Round &round, card_functions::CardFunctions &card_functions){
    for (auto iter = clients.begin(); iter != clients.end();){
        QTcpSocket *client_socket = iter.key();
        std::shared_ptr<player::Player> player = players[user_name(iter.key())];
        // recieve json with count of cards
        std::vector<std::pair<std::shared_ptr<card::Card>, int>> players_spell = player->get_spell();
        int num = players_spell.size();
        // there may be other jsons
        for (int i = 0; i < num; i++){
            card_functions.do_card_effects(players_spell[i].first, player);
            // write to json
        }
        iter++;
    }
    for (auto iter = clients.begin(); iter != clients.end();){
        QTcpSocket *client_socket = iter.key();
        //client_socket->... : send_json;
    }
}
void Server::play_the_game(){
    // checking if there is a live player
    int alive = 0;
    while (true){
        // play game
        /*for (auto iter = clients.begin(); iter != clients.end();){
            std::shared_ptr<player::Player> player = iter.value().first;
            if (player->get_lives() > 0){
                alive++;
            }
        }*/
        if (alive == 1){
            for (auto iter = clients.begin(); iter != clients.end();){
                // send json : game_finished, name of the winner : player with != 0 count of lives
            }
            break;
        }
    }
}
}
