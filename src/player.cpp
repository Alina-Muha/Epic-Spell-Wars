#include "../include/player.h"

#include <utility>

namespace player {
    Player::Player(std::string &name_) : name(std::move(name_)), lives(20) {
    }

    std::string& Player::get_name() {
        return name;
    }

    void Player::set_name(std::string name_){
        name = std::move(name_);
    }

    int Player::get_lives() const {
        return lives;
    }

    const std::vector<card::Card> &Player::get_cards() {
        return cards;
    }

    void Player::change_lives(int new_lives) {
        lives = new_lives;
    }

    void change_cards() {
        return;
    }

    int roll_the_dice(int n = 1) {
        return 0;
    }

    void make_move(card::Card &first, card::Card &second, card::Card &third) {

    }
}  // namespace player
