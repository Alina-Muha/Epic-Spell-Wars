#include "server.h"

using namespace controller;

namespace server {

Server::Server(QObject *parent)
    : QObject(parent), m_server(new QTcpServer(this)),
      m_server_socket(new QTcpSocket(this)) {
  if (m_server->listen(QHostAddress::Any, 1234)) {
    connect(this, &Server::json_received, this, &Server::receive_json);
    connect(m_server, &QTcpServer::newConnection, this,
            &Server::new_connection);
  }

  auto logs_func = [&](QString from_, QList<QString> to_, int dice_,
                       QString type_of_spell_, int number_) {
    auto request = Request(types::logs);
    foreach (std::shared_ptr<player::Player> gamer,
             game_of_players.get_round().get_alive_players()) {
      if (gamer == nullptr)
        continue;
      request.add_player(controller::JsonPlayer(
          QString::fromStdString(gamer->get_name()), gamer->get_lives()));
    }
    auto card = std::make_shared<controller::CardPlayedResult>(
        from_, to_, dice_, type_of_spell_, number_);
    request.set_card_played_result(card);
    auto data = request.to_json_object();
    send_json_to_all_clients(data);
  };
  game_of_players.set_send_logs_func(logs_func);
}

Server::~Server() {
  foreach (QTcpSocket *socket, clients.keys()) {
    socket->close();
    socket->deleteLater();
  }

  m_server->close();
  m_server->deleteLater();
}

bool Server::set_socket_descriptor(qintptr socket_descriptor) {
  return m_server_socket->setSocketDescriptor(socket_descriptor);
}

void Server::new_connection() {
  while (m_server->hasPendingConnections()) {
    QTcpSocket *socket = m_server->nextPendingConnection();
    connect(socket, &QTcpSocket::readyRead, this, &Server::receive_data);
    connect(socket, &QTcpSocket::disconnected, this,
            &Server::disconnected_from_client);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Server::error);
    clients[socket] = "";
  }
}

void Server::disconnect_from_client() { m_server_socket->disconnectFromHost(); }

QString Server::user_name(QTcpSocket *client_socket) const {
  return clients[client_socket];
}

void Server::set_user_name(QTcpSocket *client_socket,
                           const QString &user_name) {
  clients[client_socket] = user_name;
}

void Server::receive_data() {
  QTcpSocket *socket = reinterpret_cast<QTcpSocket *>(sender());
  QByteArray json_data;
  QDataStream socket_stream(socket);
  socket_stream.setVersion(QDataStream::Qt_6_2);
  while (true) {
    socket_stream.startTransaction();
    socket_stream >> json_data;
    if (socket_stream.commitTransaction()) {
      QJsonParseError parseError;
      const QJsonDocument jsonDoc =
          QJsonDocument::fromJson(json_data, &parseError);
      if (parseError.error == QJsonParseError::NoError) {
        if (jsonDoc.isObject()) {
          json_received(socket, jsonDoc.object());
        } else
          emit log_message("Invalid message: " + QString::fromUtf8(json_data));
      } else {
        emit log_message("Invalid message: " + QString::fromUtf8(json_data));
      }
    } else {
      break;
    }
  }
}

void Server::receive_json(QTcpSocket *socket, const QJsonObject &json_obj) {
  controller::Request request(json_obj);
  if (request.get_type() == types::name) {
    set_user_name(socket, request.get_name()); // name will be in json
    std::string temp_name = request.get_name().toStdString();

    game_of_players.add_player(std::make_shared<player::Player>(temp_name));
  }
  if (request.get_type() == types::start) {
    auto gameStateRequest = Request(types::start);
    auto data = gameStateRequest.to_json_object();
    send_json_to_all_clients(data);

    game_of_players.play_game();
    send_players();
    send_cards();
  }
  if (request.get_type() == types::cards) {
    auto gamer = game_of_players.find_player(clients[socket].toStdString());
    if (!gamer)
      return;
    for (auto cardObj : *request.get_cards()) {
      if (gamer->get_spell().size() >= 4)
        break;
      card::Card a(cardObj.get_number(),
                   card::Card::convert_string_it_type(
                       cardObj.get_type_of_spell().toStdString()));

      auto b = std::make_shared<card::Card>(a);
      gamer->add_card_to_spell(b);
      gamer->deliting_card(b);
    }
    number_of_spelled_players++;
    if (game_of_players.get_round().get_alive_players().size() ==
        number_of_spelled_players) {
      auto player = game_of_players.get_round().play_round();
      if (player != nullptr) {
        auto winRequest = Request(types::game_over);
        winRequest.set_name(QString::fromStdString(player->get_name()));
        send_json_to_all_clients(winRequest.to_json_object());
      } else {
        send_players();
        send_cards();
        auto game_Request = Request(types::laying_out);
        send_json_to_all_clients(game_Request.to_json_object());
      }
      number_of_spelled_players = 0;
    }
  }
}

void Server::send_players() {
  auto playersRequest = Request(types::players);
  foreach (std::shared_ptr<player::Player> gamer,
           game_of_players.get_round().get_alive_players()) {

    if (gamer == nullptr)
      continue;

    playersRequest.add_player(controller::JsonPlayer(
        QString::fromStdString(gamer->get_name()), gamer->get_lives()));
  }
  auto data = playersRequest.to_json_object();
  send_json_to_all_clients(data);
}

void Server::send_cards() {
  foreach (QTcpSocket *socket, clients.keys()) {
    auto gamer = game_of_players.find_player(clients[socket].toStdString());
    if (gamer == nullptr)
      continue;
    auto cardsRequest = Request(types::cards);

    foreach (std::shared_ptr<card::Card> card_of_game, gamer->get_cards()) {

      cardsRequest.add_card(controller::JsonCard(
          QString::fromStdString(card_of_game->convert_type_in_string(
              card_of_game->get_card_component())),
          card_of_game->get_number()));
    }
    auto data = cardsRequest.to_json_object();
    send_json(socket, data);
  }
}

void Server::send_json(QTcpSocket *socket, QJsonObject data) {
  if (!socket)
    return;
  if (!socket->isOpen())
    return;
  QDataStream server_stream(socket);
  server_stream.setVersion(QDataStream::Qt_6_2);
  QJsonDocument doc(data);
  server_stream << doc.toJson();
}

void Server::send_json_to_all_clients(QJsonObject data) {
  foreach (QTcpSocket *socket, clients.keys()) { send_json(socket, data); }
}

void Server::give_cards_to_players(round_of_game::Round &round) {
  round.distribute_cards();
  for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */) {
    std::shared_ptr<player::Player> player =
        game_of_players.find_player(user_name(iter.key()).toStdString());
    iter++;
  }
}
void Server::fill_the_spell(round_of_game::Round &round) {
  for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */) {
    QTcpSocket *client_socket = iter.key();
    std::shared_ptr<player::Player> player =
        game_of_players.find_player(user_name(iter.key()).toStdString());
    iter++;
  }
}
void Server::complete_the_number_of_cards(round_of_game::Round &round) {
  for (auto iter = clients.begin(); iter != clients.end(); /* iter++ */) {
    QTcpSocket *client_socket = iter.key();
    std::shared_ptr<player::Player> player =
        game_of_players.find_player(user_name(iter.key()).toStdString());
    int num_to_add = round.number_of_cards_in_hand - player->get_cards().size();
  }
}
} // namespace server
