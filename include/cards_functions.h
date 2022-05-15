#ifndef CARDS_FUNCTIONS_H
#define CARDS_FUNCTIONS_H
#include <iostream>
#include <vector>
#include <map>
#include "player.h"
#include "card.h"
#include "round.h"
namespace card_functions{
struct CardFunctions{
private:
    round_of_game::Round round;
public:
    // auxiliary function
    int get_num_of_player_in_circle(player::Player *current_player);
    player::Player *get_the_strongest_player();
    player::Player *get_the_weakest_player();
    std::map<card::Card::type, int> number_of_types_in_spell(player::Player *current_player);
    int unique_types_in_spell (player::Player *current_player);

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
    void rolling_the_dice(int type, int sum_1, player::Player *current_player, std::map<player::Player*, int> point_of_foes = {}, int sum_2 = 0);

    //copy the text of other card
    void copy_the_text_of_card(int type, player::Player *current_player);

    // change the player's spell
    void change_spell(int type, player::Player *current_player);

    // change the turn order
    void change_order(int type, player::Player *current_player);

    // the player interacts with the deck
    void interaction_with_the_deck(int type, player::Player *current_player);
};
} //card_functions

#endif  // CARDS_FUNCTIONS_H
