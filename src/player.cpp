#include "../include/player.h"

Player::Player(std::string &name_){
}

std::string Player::get_name(){
    return name;
}
const int Player::get_lives(){
    return lives;
}
const std::vector<Card>& get_cards() {
    return cards;
}

int Player::change_lives(){
    return lives;
}

std::vector<Card>& change_cards() {
    return cards;
}

int roll_the_dice(int n=1){
    return 0;
}

void make_move(Card &first, Card &second, Card &third){

}
