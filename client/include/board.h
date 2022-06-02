#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include "client.h"

namespace Ui {
    class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(client::Client* client_ = nullptr, QWidget *parent = nullptr);
    ~Board();

private slots:
            void update_from_server();

            void on_card_1_clicked();

            void on_card_2_clicked();

            void on_card_3_clicked();

            void on_card_4_clicked();

            void on_card_5_clicked();

            void on_card_6_clicked();

            void on_do_move_button_clicked();

private:
            enum class status {
                laying_out_cards, spells_applying, dead_player
            };
    client::Client* client;
    Ui::Board *ui;
    status game_status;
    std::map<status, QString> game_status_info = {{status::laying_out_cards, "Select 1 - 3 cards of different types for the move and press DO MOVE"},
                                               {status::spells_applying, "There is a showdown of cards and the use of spells of wizards"},
                                               {status::dead_player, "You're dead. Now you can only watch the battle of the living wizards"}};;
    QVector<QPushButton*> cards_buttons;
    QVector<controller::JsonCard> cards_in_hand;
    QList<controller::JsonCard> selected_cards;
    void players_death(std::shared_ptr<controller::JsonPlayer> request);
    void card_clicked(int i);
    QString get_log(std::shared_ptr<controller::CardPlayedResult> card_played_res);

};

#endif // BOARD_H
