#include "server.h"
#include "controller.h"
#include "card.h"
#include "player.h"
#include <QDebug>
#include <QCoreApplication>
#include <QAbstractSocket>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
namespace server{
Server::Server (QObject *parent)
 : QObject(parent),
   m_server(new QTcpServer(this)),
   m_server_socket(new QTcpSocket(this))
{
    if (m_server->listen(QHostAddress::Any, 1234)) {
        //connect(this, &Server::json_received, this, &Server::receive_json);
        connect(m_server, &QTcpServer::newConnection, this, &Server::new_connection);
        qDebug() << "Server starts...";
    } else {
        // TODO: Server start fail
    }
}

Server::~Server() {
    foreach (QTcpSocket* socket, clients.keys())
    {
        socket->close();
        socket->deleteLater();
    }

    m_server->close();
    m_server->deleteLater();
}

bool Server::set_socket_descriptor (qintptr socket_descriptor){
    return m_server_socket->setSocketDescriptor(socket_descriptor);
}

void Server::new_connection() {
    while (m_server->hasPendingConnections()) {
        QTcpSocket* socket = m_server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &Server::receive_data);
        connect (socket, &QTcpSocket::disconnected, this, &Server::disconnected_from_client);
        connect(socket, &QAbstractSocket:: errorOccurred, this, &Server::error);
        clients[socket] = "";
        // TODO: add player to game
        qDebug() << QString("Client %1 has entered the game").arg(socket->socketDescriptor());
    }
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

void Server::receive_data(){
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());
    QByteArray json_data;
    QDataStream socket_stream(socket);
    socket_stream.setVersion(QDataStream::Qt_6_2);
    while (true) {
        socket_stream.startTransaction();
        socket_stream >> json_data;
        if (socket_stream.commitTransaction()) {
            QJsonParseError parseError;
            const QJsonDocument jsonDoc = QJsonDocument::fromJson(json_data, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                if (jsonDoc.isObject()) {
                    receive_json(socket, jsonDoc.object());
                }
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

void Server::receive_json(QTcpSocket* socket, const QJsonObject &json_obj) {
    controller::Request request(json_obj);
    qDebug() << "REQUEST " << QString("New request, type: %1").arg(request.get_type()) << "\n";
    if (request.get_type() == 4) {
        qDebug() << request.to_json_object();
    }
    if (request.get_type() == 1) {
        set_user_name(socket, request.get_name()); // name will be in json
        std::string temp_name = request.get_name().toStdString();
        //player::Player gamer(temp_name);
        // players[request.get_name()] = gamer; // in map players add new player with name

        game_of_players.add_player(std::make_shared<player::Player>(temp_name));
        qDebug() << QString("Client registered, name: %1").arg(request.get_name());
    }
    if (request.get_type() == 2) {
        auto gameStateRequest = controller::Request(2);
        auto data = gameStateRequest.to_json_object();
        qDebug() << data;
        send_json_to_all_clients(data);

        game_of_players.play_game();
        send_players();
        send_cards();
    }
    if (request.get_type() == 4) {
        auto gamer = game_of_players.find_player(clients[socket].toStdString());
        if (!gamer) return;
        qDebug() << request.get_cards()->size();
        for (auto cardObj : *request.get_cards()) {
            if (gamer->get_spell().size() >= 4) break;
            card::Card a(cardObj.get_number(), card::Card::convert_string_it_type(cardObj.get_type_of_spell().toStdString()));

            auto b = std::make_shared<card::Card>(a);
            gamer->add_card_to_spell(b);
            gamer->deliting_card(b);

            qDebug() << QString::fromStdString(gamer->get_name()) << " "<< gamer->get_spell().size()<<"\n";


        }
        number_of_spelled_players++;
        qDebug() << "Spelled players: " << number_of_spelled_players;
        qDebug() << "Round players: " <<  game_of_players.get_round().get_alive_players().size();
        if (game_of_players.get_round().get_alive_players().size() == number_of_spelled_players) {
            qDebug() << "play round";
            auto player = game_of_players.get_round().play_round();
            qDebug() << "round played";
            if (player != nullptr) {
                auto winRequest = controller::Request(6);
                winRequest.set_name(QString::fromStdString(player->get_name()));
                send_json_to_all_clients(winRequest.to_json_object());
            } else {
                send_players();
                send_cards();
                auto game_Request = controller::Request(7);
                send_json_to_all_clients(game_Request.to_json_object());
            }
            number_of_spelled_players = 0;
        }
    }
}

void Server::send_players() {
    auto playersRequest = controller::Request(3);
    qDebug() << QString("players_size: ") << game_of_players.get_round().get_alive_players().size();
    foreach (std::shared_ptr<player::Player> gamer, game_of_players.get_round().get_alive_players()) {
        qDebug() << (gamer->get_name()).c_str()<<"\n";
        playersRequest.add_player(controller::JsonPlayer(QString::fromStdString(gamer->get_name()), gamer->get_lives()));
    }
    auto data = playersRequest.to_json_object();
    qDebug() << data;
    send_json_to_all_clients(data);
}

void Server::send_cards() {
    foreach (QTcpSocket* socket, clients.keys()) {
        auto gamer = game_of_players.find_player(clients[socket].toStdString());
        if (gamer == nullptr) continue;
        auto cardsRequest = controller::Request(4);
        qDebug() << "abpba";


        qDebug() << gamer->get_cards().size();
        foreach (std::shared_ptr<card::Card> card_of_game, gamer->get_cards()) {

            cardsRequest.add_card(controller::JsonCard(QString::fromStdString(card_of_game->convert_type_in_string(card_of_game->get_card_component())), card_of_game->get_number()));
            qDebug() << cardsRequest.to_json_object();

        }
        auto data = cardsRequest.to_json_object();
        send_json(socket, data);
    }
}

//void Server::send_json(const QJsonObject &json){
//    const QByteArray json_data = QJsonDocument(json).toJson(QJsonDocument::Compact);
//    emit log_message("Sending to - " + QString::fromUtf8(json_data));
//    QDataStream socket_stream(m_server_socket);
//    socket_stream.setVersion(QDataStream::Qt_6_2);
//    socket_stream << json_data;
//}

void Server::send_json(QTcpSocket* socket, QJsonObject data) {
    if (!socket) return;
    if (!socket->isOpen()) return;
    QDataStream server_stream(socket);
    server_stream.setVersion(QDataStream::Qt_6_2);
    QJsonDocument doc(data);
    server_stream << doc.toJson();
}

void Server::send_json_to_all_clients(QJsonObject data) {
    foreach (QTcpSocket* socket, clients.keys()) {
        qDebug() << QString("Sending json to %1").arg(socket->socketDescriptor());
        send_json(socket, data);
    }
}


//void Server::accept_all_connections(){
//    while (true){
//        qDebug() << QString::fromUtf8("New Connection");
//        QTcpSocket* client_socket = m_server->nextPendingConnection();
//        clients[client_socket] = "";
//        QJsonDocument doc = QJsonDocument::fromJson(client_socket->readAll());
//        QJsonObject obj = doc.object();
//        set_user_name(*client_socket, name); // name will be in json
//        player = player::Player(name);
//        players[name] = player; // in map players add new player with name
//        round.set_players.emplace_back(player)
//        if in json sent "game started":
//            for (auto client : clients){
//                send json "game started"
//            }
//            break;
//    }
//}

void Server::give_cards_to_players(round_of_game::Round &round){
    round.distribute_cards();
    for (auto iter = clients.begin(); iter != clients.end();/* iter++ */){
        std::shared_ptr<player::Player> player = game_of_players.find_player(user_name(iter.key()).toStdString());
        /*player->get_cards();
        // write json: cards, lives = 20
        // send_json()*/
        iter++;
    }
}
void Server::fill_the_spell(round_of_game::Round &round){
    for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */){
        QTcpSocket *client_socket = iter.key();
        std::shared_ptr<player::Player> player = game_of_players.find_player(user_name(iter.key()).toStdString());
        /*recieve json with spell
        player->add_card_to_spell(); */
        iter++;
    }
}
void Server::complete_the_number_of_cards(round_of_game::Round &round){
    for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */){
        QTcpSocket *client_socket = iter.key();
        std::shared_ptr<player::Player> player = game_of_players.find_player(user_name(iter.key()).toStdString());
        int num_to_add = round.number_of_cards_in_hand - player->get_cards().size();
        // distribute_card(num_to_add)
        // send json
    }
}
//void Server::applying_of_card_functions(round_of_game::Round &round, card_functions::CardFunctions &card_functions){
//    for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */){
//        QTcpSocket *client_socket = iter.key();
//        std::shared_ptr<player::Player> player = game_of_players.find_player(user_name(iter.key()).toStdString());
//        // recieve json with count of cards
//        std::vector<std::shared_ptr<card::Card>> players_spell = player->get_spell();
//        int num = players_spell.size();
//        // there may be other jsons
//        for (int i = 0; i < num; i++){
//            //card_functions.do_card_effects(players_spell[i].first, player);
//            // write to json
//        }
//        iter++;
//    }
//    for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */){
//        QTcpSocket *client_socket = iter.key();
//        //client_socket->... : send_json;
//    }
//}
bool Server::check_game_state(){
    // checking if there is a live player
    int alive = 0;
    while (true){
        // play game
        /*for (auto iter = clients.begin(); iter != clients.end();iter++){
            std::shared_ptr<player::Player> player = iter.value().first;
            if (player->get_lives() > 0){
                alive++;
            }
        }*/
        if (alive == 1){
            for (auto iter = clients.begin(); iter != clients.end();/* iter++ */){
                // send json : game_finished, name of the winner : player with != 0 count of lives
            }
            break;
        }
    }
}
}
