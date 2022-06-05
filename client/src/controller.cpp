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

types int_to_types(int n) {
  if (n == 1) {
    return types::name;
  } else if (n == 2) {
    return types::start;
  } else if (n == 3) {
    return types::players;
  } else if (n == 4) {
    return types::cards;
  } else if (n == 5) {
    return types::logs;
  } else if (n == 6) {
    return types::game_over;
  } else if (n == 7) {
    return types::laying_out;
  } else if (n == 8) {
    return types::registered;
  } else if (n == 9) {
    return types::duplicate;
  } else /* if (n == 10) */ {
    return types::connected;
  }
}

int types_to_int(types t) {
  if (t == types::name) {
    return 1;
  } else if (t == types::start) {
    return 2;
  } else if (t == types::players) {
    return 3;
  } else if (t == types::cards) {
    return 4;
  } else if (t == types::logs) {
    return 5;
  } else if (t == types::game_over) {
    return 6;
  } else if (t == types::laying_out) {
    return 7;
  } else if (t == types::registered) {
    return 8;
  } else if (t == types::duplicate) {
    return 9;
  } else /* if (t == types::connected) */ {
    return 10;
  }
}

JsonCard::JsonCard() {}
JsonCard::JsonCard(QString type_of_spell_, int number_)
    : type_of_spell(type_of_spell_), number(number_) {}

JsonCard::JsonCard(QJsonObject jObj) {
  type_of_spell = jObj.value(F_SPELL).toString();
  number = jObj.value(F_NUM).toInt();
}

QString JsonCard::get_type_of_spell() { return type_of_spell; }
int JsonCard::get_number() { return number; }

QString JsonCard::get_card_name() {
  QString card_name;
  if (type_of_spell == "Delivery") {
    if (number == 1) {
      card_name = "Nuke-u-lur Get Meltdown";
    } else if (number == 2) {
      card_name = "Mercy-Killing";
    } else if (number == 3) {
      card_name = "Meatier Swarm";
    } else if (number == 4) {
      card_name = "Lightning Bolt";
    } else if (number == 5) {
      card_name = "Gore-Nado";
    } else if (number == 6) {
      card_name = "Fountain Of Youth";
    } else if (number == 7) {
      card_name = "Fist O'nature";
    } else if (number == 8) {
      card_name = "Exorcism";
    } else if (number == 9) {
      card_name = "Death Wish";
    } else if (number == 10) {
      card_name = "Chicken";
    } else if (number == 11) {
      card_name = "Cone Of Acid";
    } else if (number == 12) {
      card_name = "Snakedance";
    } else if (number == 13) {
      card_name = "Phantasmagoons";
    } else if (number == 14) {
      card_name = "Pact With The Devil";
    }
  } else if (type_of_spell == "Quality") {
    if (number == 1) {
      card_name = "Boulder-Iffic";
    } else if (number == 2) {
      card_name = "Delicious";
    } else if (number == 3) {
      card_name = "Devlicious";
    } else if (number == 4) {
      card_name = "Dicey";
    } else if (number == 5) {
      card_name = "Disco-Mirrored";
    } else if (number == 6) {
      card_name = "Festering";
    } else if (number == 7) {
      card_name = "Impatient";
    } else if (number == 8) {
      card_name = "Iferno-Tastic";
    } else if (number == 9) {
      card_name = "Maggoty";
    } else if (number == 10) {
      card_name = "Mighty-gro";
    } else if (number == 11) {
      card_name = "Prickly";
    } else if (number == 12) {
      card_name = "Explodifying";
    } else if (number == 13) {
      card_name = "Thundering";
    }
  } else if (type_of_spell == "Source") {
    if (number == 1) {
      card_name = "Beard'o blasty's";
    } else if (number == 2) {
      card_name = "Professor Presto's";
    } else if (number == 3) {
      card_name = "Dr. Rooty Bark's";
    } else if (number == 4) {
      card_name = "King Oberon's";
    } else if (number == 5) {
      card_name = "Magma Gogs";
    } else if (number == 6) {
      card_name = "Midnight Merlin's";
    } else if (number == 7) {
      card_name = "Muzzlesnap's";
    } else if (number == 8) {
      card_name = "Old Scratch's";
    } else if (number == 9) {
      card_name = "Pam And Hecuba's";
    } else if (number == 10) {
      card_name = "The death fairy's";
    } else if (number == 11) {
      card_name = "Rose Bottom's";
    } else if (number == 12) {
      card_name = "Scorchia's";
    } else if (number == 13) {
      card_name = "Thaifoon's";
    } else if (number == 14) {
      card_name = "Walker Time Ranger's";
    } else if (number == 15) {
      card_name = "Wyrmtor's";
    }
  }
  return card_name;
}

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
  foreach (QString name, to) { to_arr.append(QJsonValue(name).toObject()); }
  jObj.insert(F_TO, to_arr);
  jObj.insert(F_DICE, QJsonValue::fromVariant(dice));
  jObj.insert(F_CARD, card.to_json_object());
  return jObj;
}

Request::Request(types type_) : type(type_), name("") {}

Request::Request(QJsonObject jObj) {
  type = int_to_types(jObj.value(F_TYPE).toInt());
  if (type == types::name || type == types::game_over) {
    name = jObj.value(F_NAME).toString();
  }
  if (type == types::players || type == types::logs) {
    QJsonArray json_players = jObj.value(F_PLAYERS).toArray();
    for (auto player : json_players) {
      players.append(JsonPlayer(player.toObject()));
    }
  }
  if (type == types::cards) {
    QJsonArray json_cards = jObj.value(F_CARDS).toArray();
    for (auto json_val : json_cards) {
      QJsonObject json_card = json_val.toObject();
      cards.append(JsonCard(json_card));
    }
  }
  if (type == types::logs) {
    card_played_result = CardPlayedResult(jObj.value(F_CARD_PLAYED).toObject());
  }
}

types Request::get_type() { return type; }

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

void Request::add_player(JsonPlayer player_) { players.append(player_); }

void Request::clear() {
  cards.clear();
  players.clear();
}

QJsonObject Request::to_json_object() {
  QJsonObject jObj;
  jObj.insert(F_TYPE, QJsonValue::fromVariant(types_to_int(type)));
  if (type == types::name || type == types::game_over) {
    jObj.insert(F_NAME, QJsonValue::fromVariant(name));
  }
  if (type == types::players || type == types::logs) {
    QJsonArray json_players;
    foreach (JsonPlayer player, players) {
      json_players.append(player.to_json_object());
    }
    jObj.insert(F_PLAYERS, json_players);
  }
  if (type == types::cards) {
    QJsonArray json_cards;
    foreach (JsonCard card, cards) { json_cards.append(card.to_json_object()); }
    jObj.insert(F_CARDS, json_cards);
  }
  if (type == types::logs) {
    jObj.insert(F_CARD_PLAYED, card_played_result.to_json_object());
  }

  return jObj;
}

} // namespace controller
