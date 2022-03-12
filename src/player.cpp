#include "../include/player.h"

namespace player {
    Player::Player(std::string &name_) {
    }

    std::string& Player::get_name() {
        return name;
    }

    void Player::set_name(std::string name_){
        return;
    }

    const int Player::get_lives() {
        return lives;
    }

    const std::vector<Card> &get_cards() {
        return cards;
    }

    void Player::change_lives() {
        return;
    }

    void change_cards() {
        return;
    }

    int roll_the_dice(int n = 1) {
        return 0;
    }

    void make_move(Card &first, Card &second, Card &third) {

    }
}  // namespace player
