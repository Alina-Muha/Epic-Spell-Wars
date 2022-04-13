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
                                player::Player &victim);
    void damage_for_enemy_and_current_player(const int type,
                                             const int sum,
                                             player::Player &enemy,
                                             player::Player &current_player);
    void damage_for_all_players(const int type,
                                player::Player &current_player,
                                std::vector<&player::Player> &all_players);
    void delivery_vigorous_synthesis(const int sum,
                                     player::Player &victim,
                                     player::Player &left_neigh,
                                     player::Player &right_neigh);
    void delivery_snake_hunger(const int sum,
                               player::Player &left_neigh,
                               player::Player &right_neigh,
                               player::Player &current_player);
    void quality_spiny(const int sum, player::Player &victim, player::Player &current_player);
    void copy_source(player::Player &current_player);
    void copy_delivery(player::Player &current_player);
    void quality_discotheque(player::Player &current_player);
    void quality_thunderous(player::Player &current_player,
                            std::vector<&player::Player> &all_players);
    void source_bradostrel(player::Player &current_player);
    void deck_search(const int type,
                     std::vector<card::Card> cards,
                     player::Player &current_player);
    void source_for_current_player(player::Player &current_player, const int sum = 0);
};

#endif  // CARDS_FUNCTIONS_H
