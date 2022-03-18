#include <iostream>
#include <vector>
#include "../include/Player.h"
#include "../include/cards_funstions.h"
#include "../include/сard.h"
class CardsFunctions {
    void delivery_for_one_enemy(const int sum,
                                const int damage1,
                                const int damage2,
                                const int damage3,
                                Player &victim) {
        return;
    }
    void damage_for_enemy_and_current_player(const int type,
                                             const int sum,
                                             Player &enemy,
                                             Player &current_player) {
        return;
    }
    void damage_for_all_players(
            const int type,
            Player &current_player,
            std::vector<&Player> &all_players) {  // how to contact all players??
        return;
    }
    void delivery_vigorous_synthesis(const int sum,
                                     Player &victim,
                                     Player &left_neigh,
                                     Player &right_neigh) {
        return;
    }
    void delivery_snake_hunger(const int sum,
                               Player &left_neigh,
                               Player &right_neigh,
                               Player &current_player) {
        return;
    }
    void quality_spiny(const int sum, Player &victim, Player &current_player) {
        return;
    }
    void copy_source(Player &current_player) {
        return;
    }
    void copy_delivery(Player &current_player) {
        return;
    }
    void quality_discotheque(Player &current_player) {  // if necessary
        return;
    };
    void quality_thunderous(Player &current_player,
                            std::vector<&Player> &all_players) {
        return;
    }
    void source_bradostrel(Player &current_player) {  // if necessary
        return;
    }
    void deck_search(const int type,
                     std::vector<card> cards,
                     Player &current_player) {
        return;
    }
    void source_for_current_player(Player &current_player, const int sum = 0) {
        return;
    }
};