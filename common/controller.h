#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonValue>

namespace controller {

class JsonCard
{
public:
    JsonCard(QJsonObject jObj);
    QJsonObject to_json_object();
private:
    QString type_of_spell;
    int number;
};

class JsonPlayer {
public:
    JsonPlayer(QJsonObject jObj);
    QJsonObject to_json_object();
private:
    QString name;
    int lifes;
};

class Request_1 {
public:
    Request_1(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 1;
    QString name;
};

class Request_2 {
public:
    Request_2(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 2;
};

class Request_3 {
public:
    Request_3(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 3;
    QList<JsonPlayer> players;
};

class Request_4 {
public:
    Request_4(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 4;
    QList<JsonCard> cards;
};

class Request_5 {
public:
    Request_5(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 5;
    QString from;
    QString to;
    int dice;
    JsonCard card;
    QList<JsonPlayer> players;
};

class Request_6 {
public:
    Request_6(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 6;
    QString name;
};

class Request_7 {
public:
    Request_7(QJsonObject jObj);
    QJsonObject to_json_object();

private:
    int type = 7;
    QString name;
};

class Request {
public:
    Request(int type_);
    Request(QJsonObject jObj);
    QJsonObject to_json_object();
    int get_type();
    QString get_name();
    std::shared_ptr<QList<JsonCard>> get_cards();
    std::shared_ptr<QList<JsonPlayer>> get_players();
    void set_name(QString name_);
    void add_card(JsonCard card_);
    void add_player(JsonPlayer player_);
    void clear();

private:
    int type;
    QString name;
    QList<JsonCard> cards;
    QList<JsonPlayer> players;
};

}  // namespace controller
#endif // CONTROLLER_H
