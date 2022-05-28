#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QJsonDocument>
#include<QJsonArray>
#include<QJsonObject>
#include<QJsonValue>

class JsonCard
{
public:
    JsonCard(QJsonObject jObj);
    QJsonObject toJsonObject();
private:
    QString type_of_spell;
    int number;
    bool need_to_roll_the_dice;
};

class CardsJsonController
{
public:
    CardsJsonController();
    QByteArray list();
    void append(QByteArray json);
    void clear();
private:
    QList<JsonCard> items;
};

class JsonMessage{
public:
private:

};

#endif // CONTROLLER_H

======================================================

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
    JsonCard(QString type_of_spell_, int number_);
    JsonCard(QJsonObject jObj);
    QJsonObject to_json_object();
    QString get_type_of_spell();
    int get_number();
private:
    QString type_of_spell;
    int number;
};

class JsonPlayer {
public:
    JsonPlayer(QString name_, int lifes_);
    JsonPlayer(QJsonObject jObj);
    QJsonObject to_json_object();
    QString get_name();
    int get_lifes();
private:
    QString name;
    int lifes;
};

class СardPlayedResult {
public:
    СardPlayedResult (QString from_, QList<QString> to, int dice_, QString type_of_spell_, int number_);
    СardPlayedResult (QJsonObject jObj);
    QJsonObject to_json_object();
    QString get_from();
    QList<QString> get_to();
    int get_dice();
    JsonCard get_card();
    std::shared_ptr<QList<JsonPlayer>> get_players();
    void add_player(JsonPlayer player_);
    void players_clear();

private:
    int type = 5;
    QString from;
    QList<QString> to;
    int dice;
    JsonCard card;
    QList<JsonPlayer> players;
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
