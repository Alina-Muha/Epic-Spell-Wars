#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QMap>
#include "round.h"
#include "player.h"
#include "cards_functions.h"
namespace server{
class Server : public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(Server)

public:
    explicit Server(QObject *parent = nullptr);
    virtual bool set_socket_descriptor(qintptr socket_descriptor);
    QString user_name(QTcpSocket *client_socket) const;
    void set_user_name(QTcpSocket *client_socket, const QString &user_name);
    void send_json(const QJsonObject &json_data);
    void accept_all_connections();
    void give_cards_to_players(round_of_game::Round &round);
    void fill_the_spell(round_of_game::Round &round);
    void complete_the_number_of_cards(round_of_game::Round &round);
    void applying_of_card_functions(round_of_game::Round &round, card_functions::CardFunctions &card_functions);
    void play_the_game();
signals:
    void json_received(const QJsonObject &json_doc);
    void disconnected_from_client();
    void error();
    void log_message (const QString &msg);
public slots:
    void disconnect_from_client();
private slots:
    void receive_json();
private:
    QTcpServer *m_server;
    QTcpSocket *m_server_socket;
    QMap<QTcpSocket *, std::pair<std::shared_ptr<player::Player>, QString>> clients;
};
} // namespace server

#endif // SERVER_H
