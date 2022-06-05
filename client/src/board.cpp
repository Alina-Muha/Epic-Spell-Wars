#include "board.h"
using namespace controller;

Board::Board(std::shared_ptr<client::Client> client_, QWidget *parent)
    : QWidget(parent), ui(new Ui::Board),
      game_status(status::laying_out_cards) {
  client = client_;
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &Board::update_from_server);
  timer->start(500);
  ui->setupUi(this);
  cards_in_hand.resize(6, {"", 0});
  ui->info->setText(
      "Select 1 - 3 cards of different types for the move and press DO MOVE");
  ui->name->setText(client->get_name());
  ui->logs->addScrollBarWidget(ui->verticalScrollBar, Qt::AlignRight);
}

void Board::players_death(std::shared_ptr<controller::JsonPlayer> player) {
  if (player->get_name() == client->get_name()) {
    ui->info->setText(game_status_info[status::dead_player]);
    cards_buttons = {ui->card_1, ui->card_2, ui->card_3,
                     ui->card_4, ui->card_5, ui->card_6};
    for (auto card : cards_buttons) {
      card->setEnabled(false);
    }
  } else {
    ui->logs->append("\nWizard " + player->get_name() + " died");
  }
}

QString
Board::get_log(std::shared_ptr<controller::CardPlayedResult> card_played_res) {
  QString log = "Wizard " + card_played_res->get_from() + " played card " +
                card_played_res->get_card().get_card_name();
  if (!(card_played_res->get_to().empty())) {
    log += " against ";
    bool not_first = false;
    for (auto &player_name : card_played_res->get_to()) {
      if (not_first) {
        log += ", ";
      }
      log += player_name;
      not_first = true;
    }
  }
  log += ". ";
  if (card_played_res->get_dice() != 0) {
    log += "The result of the dice roll is ";
    log += QString::number(card_played_res->get_dice());
  }
  return log;
}

void Board::update_from_server() {
  while (!client->requestsQueue.empty()) {
    auto request = client->requestsQueue.front();
    client->requestsQueue.pop_front();
    if (request.get_type() == types::logs) {
      std::shared_ptr<controller::CardPlayedResult> card_played_res =
          request.get_card_played_result();
      QString log = get_log(card_played_res);
      ui->logs->append("\n" + log);
    }

    if (request.get_type() == types::players ||
        request.get_type() == types::logs) {
      auto players_ptr = request.get_players();
      ui->lives_of_players->clear();
      for (auto player : *players_ptr) {
        if (player.get_name() == client->get_name()) {
          ui->life->setText(QString::number(player.get_lives()));
        }
        ui->lives_of_players->setText(ui->lives_of_players->text() + "\n" +
                                      player.get_name() + ": " +
                                      QString::number(player.get_lives()));
        if (player.get_lives() <= 0) {
          players_death(std::make_shared<controller::JsonPlayer>(player));
        }
      }
    }

    if (request.get_type() == types::cards) {
      cards_buttons = {ui->card_1, ui->card_2, ui->card_3,
                       ui->card_4, ui->card_5, ui->card_6};
      auto json_cards_ptr = request.get_cards();
      int i = 0;
      for (auto card : *json_cards_ptr) {
        cards_in_hand[i] = card;
        std::string lower_type_of_spell =
            card.get_type_of_spell().toStdString();
        std::transform(lower_type_of_spell.begin(), lower_type_of_spell.end(),
                       lower_type_of_spell.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        QString path = ":/" + QString::fromStdString(lower_type_of_spell) +
                       "_cards/" + card.get_type_of_spell() + "_" +
                       QString::number(card.get_number()) + ".png";
        QIcon icon;
        QPixmap pixmap;
        if (pixmap.load(path)) {
          icon.addPixmap(pixmap);
          cards_buttons[i]->setIcon(icon);
          cards_buttons[i]->setIconSize(QSize(ui->card_1->width() * 9 / 10,
                                              ui->card_1->height() * 9 / 10));
        }
        i++;
      }
    }
    if (request.get_type() == types::game_over) {
      if (request.get_name() == client->get_name()) {
        ui->info->setText(
            "You have won. Congratulations to you! The game is over");
      } else {
        ui->info->setText("\nWizard " + request.get_name() +
                          " wins. The game is over");
      }
    }
    if (request.get_type() == types::laying_out) {
      cards_buttons = {ui->card_1, ui->card_2, ui->card_3,
                       ui->card_4, ui->card_5, ui->card_6};
      for (auto card : cards_buttons) {
        card->setStyleSheet(not_clicked_style);
      }
      game_status = status::laying_out_cards;
      ui->info->setText(game_status_info[game_status]);
    }
  }
}

Board::~Board() { delete ui; }

void Board::card_clicked(int i) {
  cards_buttons = {ui->card_1, ui->card_2, ui->card_3,
                   ui->card_4, ui->card_5, ui->card_6};
  if (cards_buttons[i]->styleSheet() == clicked_style) {
    ui->info->setText("This card has already been selected");
  } else if (selected_types[cards_in_hand[i].get_type_of_spell()]) {
    ui->info->setText("This type of spell has already been selected");
  } else if (game_status == status::spells_applying) {
    ui->info->setText("You can't lay out the cards right now. Please wait");
  } else if (selected_cards.size() >= 3) {
    ui->info->setText("You've already laid out three cards. Click DO MOVE");
  } else if (game_status == status::laying_out_cards &&
             selected_cards.size() < 3) {
    selected_cards.append(cards_in_hand[i]);
    selected_types[cards_in_hand[i].get_type_of_spell()] = true;
    cards_buttons[i]->setStyleSheet(clicked_style);
  }
}

void Board::on_card_1_clicked() { card_clicked(0); }

void Board::on_card_2_clicked() { card_clicked(1); }

void Board::on_card_3_clicked() { card_clicked(2); }

void Board::on_card_4_clicked() { card_clicked(3); }

void Board::on_card_5_clicked() { card_clicked(4); }

void Board::on_card_6_clicked() { card_clicked(5); }

void Board::on_do_move_button_clicked() {
  if (selected_cards.size() == 0) {
    ui->info->setText("You didn't choose the cards");
  }
  if (game_status == status::laying_out_cards) {
    auto request = Request(types::cards);
    request.set_cards(selected_cards);
    selected_cards.clear();
    client->send_json(request.to_json_object());
    game_status = status::spells_applying;
    ui->info->setText("Your cards are laid out. " +
                      game_status_info[game_status]);
    for (auto &[type, flag] : selected_types) {
      selected_types[type] = false;
    }
  }
}
