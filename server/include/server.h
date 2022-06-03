#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMap>
#include <QJsonObject>
#include "round.h"
#include "player.h"
#include "game.h"
namespace server{
class Server : public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(Server)

public:

    game::Game game_of_players;
    explicit Server(QObject *parent = nullptr);
    ~Server();
    virtual bool set_socket_descriptor(qintptr socket_descriptor);
    QString user_name(QTcpSocket *client_socket) const;
    void set_user_name(QTcpSocket *client_socket, const QString &user_name);
//    void send_json(const QJsonObject &json_data);
    void send_json(QTcpSocket* socket, QJsonObject data);
    void send_json_to_all_clients(QJsonObject data);
    void accept_all_connections();
    void give_cards_to_players(round_of_game::Round &round);
    void fill_the_spell(round_of_game::Round &round);
    void complete_the_number_of_cards(round_of_game::Round &round);
    //void applying_of_card_functions(round_of_game::Round &round, card_functions::CardFunctions &card_functions);
    void play_the_game();
    bool check_game_state();
    void send_players();
    void send_cards();
signals:
    void json_received(QTcpSocket* socket, const QJsonObject &json_doc);
    void disconnected_from_client();
    void error();
    void log_message (const QString &msg);
public slots:
    void disconnect_from_client();
private slots:
    void receive_data();
    void new_connection();
    void receive_json(QTcpSocket* socket, const QJsonObject &json_obj);
private:
    QTcpServer *m_server;
    QTcpSocket *m_server_socket;
    QMap<QTcpSocket *, QString> clients;
    int number_of_spelled_players = 0;

};
} // namespace server

#endif // SERVER_H
