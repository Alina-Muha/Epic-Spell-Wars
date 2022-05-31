#include "board.h"
#include "controller.h"
#include "ui_board.h"
#include <QTimer>

Board::Board(client::Client *client_, QWidget *parent) :
        QWidget(parent),
        client(client_),
        ui(new Ui::Board),
        cards_buttons({ui->card_1, ui->card_2, ui->card_3, ui->card_4, ui->card_5, ui->card_6})
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Board::update_from_server);
    timer->start(1000);
    ui->setupUi(this);
}

void Board::players_death(std::shared_ptr<controller::JsonPlayer> player) {
    if (player->get_name() == client->get_name()) {
        ui->logs->setText(ui->logs->text() + "You died. Now you can only watch other wizards play");
        for (auto card : cards_buttons)
        {
            card->setEnabled(false);
        }
    } else {
        ui->logs->setText(ui->logs->text() + "\nWizard " + player->get_name() + " died");
    }
}

void Board::update_from_server() {
    while (!client->requestsQueue.empty()) {
        auto request = client->requestsQueue.front();
        client->requestsQueue.pop_front();

        if (request.get_type() == 3) {
            auto players = request.get_players();
            ui->lives_of_players->clear();
            for(auto player : *players) {
                if (player.get_name() == client->get_name()) {
                    ui->life->setText(QString::number(player.get_lives()));
                }
                ui->lives_of_players->setText(ui->lives_of_players->text() + "\n" + player.get_name() + ": " + QString::number(player.get_lives()));
                if (player.get_lives() == 0) {
                    players_death(std::make_shared<controller::JsonPlayer>(player));
                }
            }
        }
        if (request.get_type() == 4) {
            qDebug() << QString("Got cards, size: %1").arg(request.get_cards()->size());
            auto json_cards_ptr = request.get_cards();
            assert(json_cards_ptr->size() == 6);
            for (int i = 0; i < 6; i++) {
                cards_in_hand[i] = (*json_cards_ptr)[i];
                QPixmap pixmap((*json_cards_ptr)[i].get_type_of_spell() + "_" + QString::number((*json_cards_ptr)[i].get_number()) + ".png");
                QIcon card_icon(pixmap);
                cards_buttons[i]->setIcon(card_icon);
                cards_buttons[i]->setIconSize(pixmap.rect().size());
            }
        }
        if (request.get_type() == 6) {
            if (request.get_name() == client->get_name()) {
                ui->logs->setText(ui->logs->text() + "You have won. Congratulations to you!");
            }
            else {
                ui->logs->setText(ui->logs->text() + "\nWizard " + request.get_name() + " wins. The game is over");
            }
        }
    }
}

Board::~Board()
{
    delete ui;
}

void Board::on_card_1_clicked()
{
   selected_cards.append(cards_in_hand[0]);
}


void Board::on_card_2_clicked()
{
    selected_cards.append(cards_in_hand[1]);
}


void Board::on_card_3_clicked()
{
    selected_cards.append(cards_in_hand[2]);
}


void Board::on_card_4_clicked()
{
    selected_cards.append(cards_in_hand[3]);
}


void Board::on_card_5_clicked()
{
    selected_cards.append(cards_in_hand[4]);
}


void Board::on_card_6_clicked()
{
    selected_cards.append(cards_in_hand[5]);
}


void Board::on_do_move_button_clicked()
{
    auto request = controller::Request(4);
    request.set_cards(selected_cards);
    selected_cards.clear();
    client->send_json(request.to_json_object());
}

