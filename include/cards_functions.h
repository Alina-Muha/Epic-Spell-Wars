#ifndef CARDS_FUNCTIONS_H
#define CARDS_FUNCTIONS_H
#include <iostream>
#include <vector>
#include "player.h"
#include "card.h"
#include "round.h"
namespace card_functions{
struct CardFunctions{
private:
    round::Round round;
public:
    // auxiliary function
    int get_num_of_player_in_circle(player::Player *current_player);
    player::Player *get_the_strongest_player();

    // damage is dealt depending on the number of points dropped
    void damage_to_the_strongest_player(int type, int sum, player::Player *current_player);
    void damage_to_the_weakest_player(int sum);
    void damage_to_the_left_neighbour(int sum, player::Player *current_player);
    void damage_to_the_right_neighbour(int type, int sum, player::Player *current_player);
    void damage_to_chosen_foe(int type, int sum, player::Player *current_player, player::Player *chosen_foe, card::Card *card = nullptr);
    void hp_to_current_player(int sum, player::Player *current_player);
    void damage_for_several_foes(int type, int sum, player::Player *current_player);

    // damage is dealt depending on the type of cards
    void type_of_cards_damage(int type, player::Player *current_Player);

    // damage doesn't depend on the numbers of point dropped or on the type of cards
    void damage_without_parametrs(int type, player::Player *current_player, int chosen = 0);

    // player rolls dice
    void rolling_the_dice(int type, int sum_1, player::Player *current_player, std::vector<int> points_of_foes, int sum_2 = 0);
};
} //card_functions

#endif  // CARDS_FUNCTIONS_H
