#include "controller.h"
#include <QVariant>

#define F_TYPE "type_of_spell"
#define F_NUM "number"
#define F_NEED_TO_ROLL_THE_DICE "need_to_roll_the_dice"

JsonCard::JsonCard(QJsonObject jObj) {
    type_of_spell = jObj.value(F_TYPE).toString();
    number = jObj.value(F_NUM).toInt();

}

QJsonObject JsonCard::toJsonObject() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type_of_spell));
    jObj.insert(F_NUM, QJsonValue::fromVariant(number));
    jObj.insert(F_NEED_TO_ROLL_THE_DICE, QJsonValue::fromVariant(need_to_roll_the_dice));
}

CardsJsonController::CardsJsonController(){

}
QByteArray CardsJsonController::list(){
    QJsonArray jCards;
    foreach (JsonCard card, items){
        jCards.append(card.toJsonObject());
    }
    return QJsonDocument(jCards).toJson();
}
void CardsJsonController::append(QByteArray json){
    QJsonObject jCard = QJsonDocument::fromJson(json).object();
    items.append(JsonCard(jCard));
}
void CardsJsonController::clear(){
    items.clear();
}

==================================================

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

JsonCard::JsonCard(QString type_of_spell_, int number_) : type_of_spell(type_of_spell_), number(number_) {
}

JsonCard::JsonCard(QJsonObject jObj) {
    type_of_spell = jObj.value(F_SPELL).toString();
    number = jObj.value(F_NUM).toInt();
}

QString JsonCard::get_type_of_spell() {
    return type_of_spell;
}
int JsonCard::get_number(){
    return number;
}

QJsonObject JsonCard::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_SPELL, QJsonValue::fromVariant(type_of_spell));
    jObj.insert(F_NUM, QJsonValue::fromVariant(number));
    return jObj;
}

JsonPlayer::JsonPlayer(QString name_, int lifes_) : name(name_), lifes(lifes_){
}

JsonPlayer::JsonPlayer(QJsonObject jObj) {
    name = jObj.value(F_NAME).toString();
    lifes = jObj.value(F_LIFES).toInt();
}

QString JsonPlayer::get_name() {
    return name;
}
int JsonPlayer::get_lifes(){
    return lifes;
}

QJsonObject JsonPlayer::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
    jObj.insert(F_LIFES, QJsonValue::fromVariant(lifes));
    return jObj;
}

СardPlayedResult::СardPlayedResult (QString from_, QList<QString> to_, int dice_,
                                    QString type_of_spell_, int number_) : from(from_),
                                    to(to_), dice(dice_), card(JsonCard(type_of_spell_, number_)) {
}

СardPlayedResult::СardPlayedResult (QJsonObject jObj) : card(jObj.value(F_CARD).toObject()) {
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

QString СardPlayedResult::get_from() {
    return from;
}
QList<QString> СardPlayedResult::get_to(){
    return to;
}
int СardPlayedResult::get_dice() {
    return dice;
}
JsonCard СardPlayedResult::get_card(){
    return card;
}
std::shared_ptr<QList<JsonPlayer>> СardPlayedResult::get_players(){
     return std::make_shared<QList<JsonPlayer>> (players);
}

void СardPlayedResult::add_player(JsonPlayer player_) {
    players.append(player_);
}
void СardPlayedResult::players_clear() {
    players.clear();
}

QJsonObject  СardPlayedResult ::to_json_object() {
    QJsonObject jObj;
    jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
    jObj.insert(F_FROM, QJsonValue::fromVariant(from));
    QJsonArray to_arr;
    foreach (QString name, to) {
        to_arr.append(QJsonValue(name).toObject());
    }
    jObj.insert(F_TO, to_arr);
    jObj.insert(F_DICE, QJsonValue::fromVariant(dice));
    jObj.insert(F_CARD, card.to_json_object());
    QJsonArray json_players;
    foreach (JsonPlayer player, players) {
        json_players.append(player.to_json_object());
    }
    jObj.insert(F_PLAYERS, json_players);
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










