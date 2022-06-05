#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QVariant>

namespace controller {

enum class types {
    name, start, players, cards, logs, game_over, laying_out, registered, duplicate, connected
};

types int_to_types(int n);
int types_to_int(types t);

class JsonCard {
public:
  JsonCard();
  JsonCard(QString type_of_spell_, int number_);
  JsonCard(QJsonObject jObj);
  QJsonObject to_json_object();
  [[nodiscard]] QString get_type_of_spell();
  [[nodiscard]] int get_number();

private:
  QString type_of_spell;
  int number;
};

class JsonPlayer {
public:
  JsonPlayer(QString name_, int lives_);
  JsonPlayer(QJsonObject jObj);
  QJsonObject to_json_object();
  [[nodiscard]] QString get_name();
  [[nodiscard]] int get_lives();

private:
  QString name;
  int lives;
};

class CardPlayedResult {
public:
  CardPlayedResult(QString from_ = "", QList<QString> to = {}, int dice_ = 0,
                   QString type_of_spell_ = "", int number_ = 0);
  CardPlayedResult(QJsonObject jObj);
  QJsonObject to_json_object();
  [[nodiscard]] QString get_from();
  [[nodiscard]] QList<QString> get_to();
  [[nodiscard]] int get_dice();
  [[nodiscard]] JsonCard get_card();
  void add_player(JsonPlayer player_);

private:
  QString from;
  QList<QString> to;
  int dice;
  JsonCard card;
};

class Request {
public:
  Request(types type_);
  Request(QJsonObject jObj);
  QJsonObject to_json_object();
  [[nodiscard]] types get_type();
  [[nodiscard]] QString get_name();
  [[nodiscard]] std::shared_ptr<QList<JsonCard>> get_cards();
  [[nodiscard]] std::shared_ptr<QList<JsonPlayer>> get_players();
  [[nodiscard]] std::shared_ptr<CardPlayedResult> get_card_played_result();
  void set_name(QString name_);
  void set_cards(QList<JsonCard> cards_);
  void add_card(JsonCard card_);
  void add_player(JsonPlayer player_);
  void
  set_card_played_result(std::shared_ptr<CardPlayedResult> card_played_result_);
  void clear();

private:
  types type;
  QString name;
  QList<JsonCard> cards;
  QList<JsonPlayer> players;
  CardPlayedResult card_played_result;
};

} // namespace controller
#endif // CONTROLLER_H
