#include "../include/player.h"

#include <utility>

namespace player {
    Player::Player(std::string &name_) : name(std::move(name_)), lives(20) {
    }

    void Player::set_name(std::string name_) {
        name = std::move(name_);
    }

    std::string &Player::get_name() {
        return name;
    }

    std::vector <std::pair<card::Card *, int>> &Player::get_spell() {
        return spell;
    }

    int Player::get_lives() const {
        return lives;
    }

    const std::vector<card::Card *> &Player::get_cards() {
        return cards;
    }

    void Player::change_lives(int new_lives) {
        lives = new_lives;
    }

    void Player::add_card(card::Card *new_card) {
        cards.push_back(new_card);
    }

    void select_card(int index) {
        spell.push_back({cards[i], 0});
        for (int j = i; j < cards.size() - 1; j++) {  // list will be better?
            cards[j] = cards[j+1];
            cards.pop_back();
        }
    }

    void sort_cards_in_spell() {
        std::sort(spell.begin(), spell.end(), [](std::pair<card::Card *, int> x, std::pair<card::Card *, int> y) {
            return (*(x.first)).type_of_spell_component < (*(x.first)).type_of_spell_component
        })
    }

    bool is_move_correct() {
        if (spell.size() > 3 || spell.size() < 1) {
            return false;
        }
        sort_cards_in_spell();
        for (int i = 0; i < spell.size(); i++) {
            if ((*(spell[i].first)).type_of_spell_component == (*(spell[i + 1].first)).type_of_spell_component) {
                return false;
            }
        }
        return true;
    }
}  // namespace player
