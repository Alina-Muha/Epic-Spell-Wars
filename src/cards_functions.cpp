#include <iostream>
#include <vector>
#include "player.h"
#include "cards_functions.h"
#include "card.h"
void CardsFunctions::delivery_for_one_enemy(const int sum,
                                            const int damage1,
                                            const int damage2,
                                            const int damage3,
                                            player::Player &victim) {
    return;
}
void CardsFunctions::damage_for_enemy_and_current_player(const int type,
                                                         const int sum,
                                                         player::Player &enemy,
                                                         player::Player &current_player) {
    return;
}
void CardsFunctions::damage_for_all_players(
        const int type,
        player::Player &current_player,
        std::vector<player::Player> &all_players) {  // how to contact all players??
    return;
}
void CardsFunctions::delivery_vigorous_synthesis(const int sum,
                                                 player::Player &victim,
                                                 player::Player &left_neigh,
                                                 player::Player &right_neigh) {
    return;
}
void CardsFunctions::delivery_snake_hunger(const int sum,
                                           player::Player &left_neigh,
                                           player::Player &right_neigh,
                                           player::Player &current_player) {
    return;
}
void CardsFunctions::quality_spiny(const int sum, player::Player &victim, player::Player &current_player) {
    return;
}
void CardsFunctions::copy_source(player::Player &current_player) {
    return;
}
void CardsFunctions::copy_delivery(player::Player &current_player) {
    return;
}
void CardsFunctions::quality_discotheque(player::Player &current_player) {  // if necessary
    return;
};
void CardsFunctions::quality_thunderous(player::Player &current_player,
                                        std::vector<player::Player> &all_players) {
    return;
}
void CardsFunctions::source_bradostrel(player::Player &current_player) {  // if necessary
    return;
}
void CardsFunctions::deck_search(const int type,
                                 std::vector<card::Card> cards,
                                 player::Player &current_player) {
    return;
}
void CardsFunctions::source_for_current_player(player::Player &current_player, const int sum) {
    return;
}

