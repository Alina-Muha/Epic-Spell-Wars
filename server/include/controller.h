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
        JsonCard();
        JsonCard(QString type_of_spell_, int number_);
        JsonCard(QJsonObject jObj);
        QJsonObject to_json_object();
        QString get_type_of_spell();
        int get_number();
        QString get_card_name();
    private:
        QString type_of_spell;
        int number;
    };

    class JsonPlayer {
    public:
        JsonPlayer(QString name_, int lives_);
        JsonPlayer(QJsonObject jObj);
        QJsonObject to_json_object();
        QString get_name();
        int get_lives();
    private:
        QString name;
        int lives;
    };

    class CardPlayedResult {
    public:
        CardPlayedResult (QString from_ = "", QList<QString> to = {}, int dice_ = 0, QString type_of_spell_ = "", int number_ = 0);
        CardPlayedResult (QJsonObject jObj);
        QJsonObject to_json_object();
        QString get_from();
        QList<QString> get_to();
        int get_dice();
        JsonCard get_card();
        void add_player(JsonPlayer player_);

    private:
        QString from;
        QList<QString> to;
        int dice;
        JsonCard card;
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
        std::shared_ptr<CardPlayedResult> get_card_played_result();
        void set_name(QString name_);
        void set_cards(QList<JsonCard> cards_);
        void add_card(JsonCard card_);
        void add_player(JsonPlayer player_);
        void set_card_played_result(std::shared_ptr<CardPlayedResult> card_played_result_);
        void clear();

    private:
        int type;
        QString name;
        QList<JsonCard> cards;
        QList<JsonPlayer> players;
        CardPlayedResult card_played_result;
    };

}  // namespace controller
#endif // CONTROLLER_H
