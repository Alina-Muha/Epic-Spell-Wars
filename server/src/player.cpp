#include "player.h"

namespace player {
Player::Player(std::string &name_) : name(std::move(name_)), lives(20) {}

void Player::set_name(std::string name_) { name = std::move(name_); }

int Player::get_num_of_cards() { return cards.size(); }

std::string &Player::get_name() { return name; }

std::vector<std::shared_ptr<card::Card>> &Player::get_spell() { return spell; }

int Player::get_lives() const { return lives; }

std::vector<std::shared_ptr<card::Card>> &Player::get_cards() { return cards; }

void Player::add_lives(int lives_to_add) { lives += lives_to_add; }

void Player::subtract_lives(int lives_to_subtract) {
  lives -= lives_to_subtract;
}

void Player::change_lives(int new_lives) { lives = new_lives; }

void Player::add_card(std::shared_ptr<card::Card> new_card) {
  cards.push_back(new_card);
}

void Player::select_card(int index) {
  spell.push_back({cards[index], 0});
  for (int j = index; j < cards.size() - 1; j++) {
    cards[j] = cards[j + 1];
    cards.pop_back();
  }
}

bool Player::is_move_correct() {
  if (spell.size() > 3 || spell.size() < 1) {
    return false;
  }
  for (int i = 0; i < spell.size(); i++) {
    if ((*(spell[i])).get_type_of_the_spell_component() ==
        (*(spell[i + 1])).get_type_of_the_spell_component()) {
      return false;
    }
  }
  return true;
}

void Player::add_card_to_spell(std::shared_ptr<card::Card> new_card) {
  spell.push_back(new_card);
}

// for card_functions

int Player::get_achane_num_in_spell() {
  int num = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_card_type() == card::Card::type::ahcane) {
      num++;
    }
  }
  return num;
}

int Player::get_dark_num_in_spell() {
  int num = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_card_type() == card::Card::type::dark) {
      num++;
    }
  }
  return num;
}

int Player::get_illusion_num_in_spell() {
  int num = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_card_type() == card::Card::type::illusion) {
      num++;
    }
  }
  return num;
}

int Player::get_primal_num_in_spell() {
  int num = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_card_type() == card::Card::type::primal) {
      num++;
    }
  }
  return num;
}

int Player::get_elemental_num_in_spell() {
  int num = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_card_type() == card::Card::type::elemental) {
      num++;
    }
  }
  return num;
}

int Player::unique_types_in_spell() {
  return static_cast<int>(this->get_achane_num_in_spell() != 0) +
         static_cast<int>(this->get_dark_num_in_spell() != 0) +
         static_cast<int>(this->get_illusion_num_in_spell() != 0) +
         static_cast<int>(this->get_primal_num_in_spell() != 0) +
         static_cast<int>(this->get_elemental_num_in_spell() != 0);
}

int Player::get_delivery_card_in_spell() {
  int num = -1;
  int i = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_type_of_the_spell_component() ==
        card::Card::type_of_spell_component::delivery) {
      num = i;
      break;
    }
    i++;
  }
  return num;
}

int Player::get_source_card_in_spell() {
  int num = -1;
  int i = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_type_of_the_spell_component() ==
        card::Card::type_of_spell_component::source) {
      num = i;
      break;
    }
    i++;
  }
  return num;
}

int Player::get_quality_card_in_spell() {
  int num = -1;
  int i = 0;
  for (auto &card : this->get_spell()) {
    if (card.get()->get_type_of_the_spell_component() ==
        card::Card::type_of_spell_component::quality) {
      num = i;
      break;
    }
    i++;
  }
  return num;
}

void Player::delete_card(int num_of_card) {
  this->get_cards().erase(this->get_cards().begin() + num_of_card);
}

void Player::delete_card_from_spell(int num_of_card) {
  this->get_spell().erase(this->get_spell().begin() + num_of_card);
}
void Player::deliting_card(std::shared_ptr<card::Card> card_) {
  std::vector<std::shared_ptr<card::Card>> temp_cards;
  for (auto i : cards) {
    if (i->get_number() == card_->get_number() &&
        i->get_card_component() == card_->get_card_component()) {

    } else {
      temp_cards.push_back(i);
    }
  }
  cards = temp_cards;
}
} // namespace player
