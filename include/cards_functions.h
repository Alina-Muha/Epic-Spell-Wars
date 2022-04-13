#ifndef CARDS_FUNCTIONS_H
#define CARDS_FUNCTIONS_H
#include <iostream>
#include <vector>
#include "player.h"
#include "card.h"
class CardsFunctions {
    void delivery_for_one_enemy(const int sum,
                                const int damage1,
                                const int damage2,
                                const int damage3,
                                Player &victim);
    void damage_for_enemy_and_current_player(const int type,
                                             const int sum,
                                             Player &enemy,
                                             Player &current_player);
    void damage_for_all_players(const int type,
                                Player &current_player,
                                std::vector<&Player> &all_players);
    void delivery_vigorous_synthesis(const int sum,
                                     Player &victim,
                                     Player &left_neigh,
                                     Player &right_neigh);
    void delivery_snake_hunger(const int sum,
                               Player &left_neigh,
                               Player &right_neigh,
                               Player &current_player);
    void quality_spiny(const int sum, Player &victim, Player &current_player);
    void copy_source(Player &current_player);
    void copy_delivery(Player &current_player);
    void quality_discotheque(Player &current_player);
    void quality_thunderous(Player &current_player,
                            std::vector<&Player> &all_players);
    void source_bradostrel(Player &current_player);
    void deck_search(const int type,
                     std::vector<card> cards,
                     Player &current_player);
    void source_for_current_player(Player &current_player, const int sum = 0);
};

#endif  // CARDS_FUNCTIONS_H
