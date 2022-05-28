#include "controller.h"
#include <QVariant>

#define F_SPELL "type_of_spell"
#define F_NUM "number"
#define F_TYPE "type"
#define F_NAME "name"
#define F_PLAYERS "players"
#define F_PLAYER "player"
#define F_LIFES "lifes"
#define F_CARDS "cards"
#define F_CARD "card"
#define F_FROM "from"
#define F_TO "to"
#define F_DICE "dice"

namespace controller {

JsonCard::JsonCard(QJsonObject jObj) {
    type_of_spell = jObj.value(F_SPELL).toString();
    number = jObj.value(F_NUM).toInt();
}

QJsonObject JsonCard::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_SPELL, QJsonValue::fromVariant(type_of_spell));
    jObj.insert(F_NUM, QJsonValue::fromVariant(number));
    return jObj;
}

JsonPlayer::JsonPlayer(QJsonObject jObj) {
    name = jObj.value(F_NAME).toString();
    lifes = jObj.value(F_LIFES).toInt();
}

QJsonObject JsonPlayer::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
    jObj.insert(F_LIFES, QJsonValue::fromVariant(lifes));
    return jObj;
}

Request_1::Request_1(QJsonObject jObj) {
    name = jObj.value(F_NAME).toString();
    type = jObj.value(F_TYPE).toInt();
}

QJsonObject  Request_1::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
    return jObj;
}

Request_2::Request_2(QJsonObject jObj) {
    type = jObj.value(F_TYPE).toInt();
}

QJsonObject  Request_2::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    return jObj;
}

Request_3::Request_3(QJsonObject jObj) {
    type = jObj.value(F_TYPE).toInt();
    QJsonArray json_players = jObj.value(F_PLAYERS).toArray();
    foreach (QJsonValue json_val, json_players) {
        QJsonObject json_player = json_val.toObject();
        players.append(JsonPlayer(json_player));
    }
}

QJsonObject  Request_3::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    QJsonArray json_players;
    foreach (JsonPlayer player, players) {
        json_players.append(player.to_json_object());
    }
    jObj.insert(F_PLAYERS, json_players);
    return jObj;
}

Request_4::Request_4(QJsonObject jObj) {
    type = jObj.value(F_TYPE).toInt();
    QJsonArray json_cards = jObj.value(F_CARDS).toArray();
    foreach (QJsonValue json_val, json_cards) {
        QJsonObject json_card = json_val.toObject();
        cards.append(JsonCard(json_card));
    }
}

QJsonObject  Request_4::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    QJsonArray json_cards;
    foreach (JsonCard card, cards) {
        json_cards.append(card.to_json_object());
    }
    jObj.insert(F_CARDS, json_cards);
    return jObj;
}

Request_5::Request_5(QJsonObject jObj) : card(jObj.value(F_CARD).toObject()) {
    type = jObj.value(F_TYPE).toInt();
    from = jObj.value(F_FROM).toString();
    from = jObj.value(F_TO).toString();
    dice = jObj.value(F_DICE).toInt();
    QJsonArray json_players = jObj.value(F_PLAYERS).toArray();
    foreach (QJsonValue json_val, json_players) {
        QJsonObject json_player = json_val.toObject();
        players.append(JsonPlayer(json_player));
    }
}

QJsonObject  Request_5::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    jObj.insert(F_FROM, QJsonValue::fromVariant(from));
    jObj.insert(F_TO, QJsonValue::fromVariant(to));
    jObj.insert(F_DICE, QJsonValue::fromVariant(dice));
    jObj.insert(F_CARD, card.to_json_object());
    QJsonArray json_players;
    foreach (JsonPlayer player, players) {
        json_players.append(player.to_json_object());
    }
    jObj.insert(F_PLAYERS, json_players);
    return jObj;
}

Request_6::Request_6(QJsonObject jObj) {
    name = jObj.value(F_NAME).toString();
    type = jObj.value(F_TYPE).toInt();
}

QJsonObject  Request_6::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
    return jObj;
}

Request_7::Request_7(QJsonObject jObj) {
    name = jObj.value(F_NAME).toString();
    type = jObj.value(F_TYPE).toInt();
}

QJsonObject  Request_7::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
    return jObj;
}

Request::Request(int type_) : type(type_), name("") {
}

Request::Request(QJsonObject jObj) {
    type = jObj.value(F_TYPE).toInt();
    if (type == 1 || type == 6 || type == 7) {
        name = jObj.value(F_NAME).toString();
    }
    if (type == 3) {
        QJsonArray json_players;
        foreach (JsonPlayer player, players) {
            json_players.append(player.to_json_object());
        }
        jObj.insert(F_PLAYERS, json_players);
    }
    if (type == 4) {
        QJsonArray json_cards = jObj.value(F_CARDS).toArray();
        foreach (QJsonValue json_val, json_cards) {
            QJsonObject json_card = json_val.toObject();
            cards.append(JsonCard(json_card));
        }
    }
}

int Request::get_type() {
    return type;
}

QString Request::get_name() {
    assert(type == 1 || type == 6 || type == 7);
    return name;
}

std::shared_ptr<QList<JsonCard>> Request::get_cards() {
    assert(type == 4);
    return std::make_shared<QList<JsonCard>>(cards);
}

std::shared_ptr<QList<JsonPlayer>> Request::get_players() {
    assert(type == 3);
    return std::make_shared<QList<JsonPlayer>>(players);
}

void Request::set_name(QString name_) {
    assert(type == 1 || type == 6 || type == 7);
    name = name_;
}

void Request::add_card(JsonCard card_) {
    assert(type == 4);
    cards.append(card_);
}

void Request::add_player(JsonPlayer player_) {
     assert(type == 3);
     players.append(player_);
}

void Request::clear() {
    cards.clear();
    players.clear();
}

QJsonObject  Request::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    if (type == 1 || type == 6 || type == 7) {
        jObj.insert(F_NAME, QJsonValue::fromVariant(name));
    }
    if (type == 3) {
        QJsonArray json_players;
        foreach (JsonPlayer player, players) {
            json_players.append(player.to_json_object());
        }
        jObj.insert(F_PLAYERS, json_players);
    }
    if (type == 4) {
        QJsonArray json_cards;
        foreach (JsonCard card, cards) {
            json_cards.append(card.to_json_object());
        }
        jObj.insert(F_CARDS, json_cards);
    }
    return jObj;
}





}  // namespace controller










