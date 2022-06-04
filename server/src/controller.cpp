#include "controller.h"

#define F_SPELL "type_of_spell"
#define F_NUM "number"
#define F_TYPE "type"
#define F_NAME "name"
#define F_PLAYERS "players"
#define F_PLAYER "player"
#define F_LIVES "lives"
#define F_CARDS "cards"
#define F_CARD "card"
#define F_FROM "from"
#define F_TO "to"
#define F_DICE "dice"
#define F_CARD_PLAYED "card_played_result"

namespace controller {
JsonCard::JsonCard() {}
JsonCard::JsonCard(QString type_of_spell_, int number_)
    : type_of_spell(type_of_spell_), number(number_) {}

JsonCard::JsonCard(QJsonObject jObj) {
  type_of_spell = jObj.value(F_SPELL).toString();
  number = jObj.value(F_NUM).toInt();
}

QString JsonCard::get_type_of_spell() { return type_of_spell; }
int JsonCard::get_number() { return number; }

QJsonObject JsonCard::to_json_object() {
  QJsonObject jObj;
  jObj.insert(F_SPELL, QJsonValue::fromVariant(type_of_spell));
  jObj.insert(F_NUM, QJsonValue::fromVariant(number));
  return jObj;
}

JsonPlayer::JsonPlayer(QString name_, int lives_)
    : name(name_), lives(lives_) {}

JsonPlayer::JsonPlayer(QJsonObject jObj) {
  name = jObj.value(F_NAME).toString();
  lives = jObj.value(F_LIVES).toInt();
}

QString JsonPlayer::get_name() { return name; }
int JsonPlayer::get_lives() { return lives; }

QJsonObject JsonPlayer::to_json_object() {
  QJsonObject jObj;
  jObj.insert(F_NAME, QJsonValue::fromVariant(name));
  jObj.insert(F_LIVES, QJsonValue::fromVariant(lives));
  return jObj;
}

CardPlayedResult::CardPlayedResult(QString from_, QList<QString> to_, int dice_,
                                   QString type_of_spell_, int number_)
    : from(from_), to(to_), dice(dice_),
      card(JsonCard(type_of_spell_, number_)) {}

CardPlayedResult::CardPlayedResult(QJsonObject jObj)
    : card(jObj.value(F_CARD).toObject()) {
  from = jObj.value(F_FROM).toString();
  QJsonArray to_arr = jObj.value(F_TO).toArray();
  for (auto name : to_arr) {
    to.append(name.toString());
  }
  dice = jObj.value(F_DICE).toInt();
}

QString CardPlayedResult::get_from() { return from; }
QList<QString> CardPlayedResult::get_to() { return to; }
int CardPlayedResult::get_dice() { return dice; }
JsonCard CardPlayedResult::get_card() { return card; }

QJsonObject CardPlayedResult::to_json_object() {
  QJsonObject jObj;

  jObj.insert(F_FROM, QJsonValue::fromVariant(from));
  QJsonArray to_arr;
  foreach (QString name, to) { to_arr.append(QJsonValue(name)); }
  jObj.insert(F_TO, to_arr);
  jObj.insert(F_DICE, QJsonValue::fromVariant(dice));
  jObj.insert(F_CARD, card.to_json_object());
  return jObj;
}

Request::Request(int type_) : type(type_), name("") {}

Request::Request(QJsonObject jObj) {
  type = jObj.value(F_TYPE).toInt();
  if (type == 1 || type == 6) {
    name = jObj.value(F_NAME).toString();
  }
  if (type == 3 || type == 5) {
    QJsonArray json_players = jObj.value(F_PLAYERS).toArray();
    for (auto player : json_players) {
      players.append(JsonPlayer(player.toObject()));
    }
  }
  if (type == 4) {
    QJsonArray json_cards = jObj.value(F_CARDS).toArray();
    for (auto json_val : json_cards) {
      QJsonObject json_card = json_val.toObject();
      cards.append(JsonCard(json_card));
    }
  }
  if (type == 5) {
    card_played_result = CardPlayedResult(jObj.value(F_CARD_PLAYED).toObject());
  }
}

int Request::get_type() { return type; }

QString Request::get_name() { return name; }

std::shared_ptr<QList<JsonCard>> Request::get_cards() {
  return std::make_shared<QList<JsonCard>>(cards);
}

std::shared_ptr<QList<JsonPlayer>> Request::get_players() {
  return std::make_shared<QList<JsonPlayer>>(players);
}

std::shared_ptr<CardPlayedResult> Request::get_card_played_result() {
  return std::make_shared<CardPlayedResult>(card_played_result);
}

void Request::set_name(QString name_) { name = name_; }

void Request::add_card(JsonCard card_) { cards.append(card_); }

void Request::set_cards(QList<JsonCard> cards_) { cards = std::move(cards_); }

void Request::set_card_played_result(
    std::shared_ptr<CardPlayedResult> card_played_result_) {
  card_played_result = *card_played_result_;
}

void Request::add_player(JsonPlayer player_) {
  assert(type == 3 || type == 5);
  players.append(player_);
}

void Request::clear() {
  cards.clear();
  players.clear();
}

QJsonObject Request::to_json_object() {
  QJsonObject jObj;
  jObj.insert(F_TYPE, QJsonValue::fromVariant(type));
  if (type == 1 || type == 6) {
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
  }
  if (type == 3 || type == 5) {
    QJsonArray json_players;
    foreach (JsonPlayer player, players) {
      json_players.append(player.to_json_object());
    }
    jObj.insert(F_PLAYERS, json_players);
  }
  if (type == 4) {
    QJsonArray json_cards;
    foreach (JsonCard card, cards) { json_cards.append(card.to_json_object()); }
    jObj.insert(F_CARDS, json_cards);
  }
  if (type == 5) {
    jObj.insert(F_CARD_PLAYED, card_played_result.to_json_object());
  }
  return jObj;
}

} // namespace controller
