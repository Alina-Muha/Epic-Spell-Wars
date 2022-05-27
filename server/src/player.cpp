#include "player.h"

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

    std::vector <std::pair<std::shared_ptr<card::Card>, int>> &Player::get_spell() {
        return spell;
    }

    int Player::get_lives() const {
        return lives;
    }

    const std::vector<std::shared_ptr<card::Card>> &Player::get_cards() {
        return cards;
    }

    void Player::add_lives(int lives_to_add) {
        lives += lives_to_add;
        std::string log = "Player " + this->get_name() + " casts a spell. You get " + std::to_string(lives_to_add) + "lives";
        //TODO: передать log
    }

    void Player::subtract_lives(int lives_to_subtract) {
        lives -= lives_to_subtract;
        std::string log = "Player " + this->get_name() + " casts a spell. You lose " + std::to_string(lives_to_subtract) + "lives";
        //TODO: передать log
    }

    void Player::change_lives(int new_lives) {
        lives = new_lives;
    }

    void Player::add_card(std::shared_ptr<card::Card> new_card) {
        cards.push_back(new_card);
    }

    void Player::select_card(int index) {
        spell.push_back({cards[index], 0});
        for (int j = index; j < cards.size() - 1; j++) {
            cards[j] = cards[j+1];
            cards.pop_back();
        }
    }

    void Player::sort_cards_in_spell() {
        std::sort(spell.begin(), spell.end(), [](std::pair<card::Card *, int> x, std::pair<card::Card *, int> y) {
            return (*(x.first)).get_type_of_the_spell_component() < (*(x.first)).get_type_of_the_spell_component();
        });
    }

    bool Player::is_move_correct() {
        if (spell.size() > 3 || spell.size() < 1) {
            return false;
        }
        sort_cards_in_spell();
        for (int i = 0; i < spell.size(); i++) {
            if ((*(spell[i].first)).get_type_of_the_spell_component() == (*(spell[i + 1].first)).get_type_of_the_spell_component()) {
                return false;
            }
        }
        return true;
    }

    void Player::add_card_to_spell(std::shared_ptr<card::Card> new_card) {
        spell.push_back({new_card, 0});
    }

}  // namespace player
