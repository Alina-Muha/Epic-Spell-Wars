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
    client::Client* client;
    Ui::Board *ui;
    QVector<QPushButton*> cards_buttons;
    QVector<controller::JsonCard> cards_in_hand;
    QList<controller::JsonCard> selected_cards;
    void players_death(std::shared_ptr<controller::JsonPlayer> request);
    QString get_log(std::shared_ptr<controller::CardPlayedResult> card_played_res);
};

#endif // BOARD_H
