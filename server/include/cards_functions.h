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
public:
    // auxiliary function
    int get_num_of_player_in_circle(std::shared_ptr<round_of_game::Round> round, std::shared_ptr<player::Player> current_player);
    std::shared_ptr<player::Player> get_the_strongest_player(std::shared_ptr<round_of_game::Round> round);
    std::shared_ptr<player::Player> get_the_weakest_player(std::shared_ptr<round_of_game::Round> round);
    std::map<card::Card::type, int> number_of_types_in_spell(std::shared_ptr<player::Player> current_player);
    int unique_types_in_spell (std::shared_ptr<player::Player> current_player);

    // damage is dealt depending on the number of points dropped
    void damage_to_the_strongest_player(std::shared_ptr<round_of_game::Round> round, int type, int sum, std::shared_ptr<player::Player> current_player);
    void damage_to_the_weakest_player(std::shared_ptr<round_of_game::Round> round, int sum);
    void damage_to_the_left_neighbour(std::shared_ptr<round_of_game::Round> round, int sum, std::shared_ptr<player::Player> current_player);
    void damage_to_the_right_neighbour(std::shared_ptr<round_of_game::Round> round, int type, int sum, std::shared_ptr<player::Player> current_player);
    void damage_to_chosen_foe(int type, int sum, std::shared_ptr<player::Player> current_player, std::shared_ptr<player::Player> chosen_foe, std::shared_ptr<card::Card> card = nullptr);
    void hp_to_current_player(int sum, std::shared_ptr<player::Player> current_player);
    void damage_for_several_foes(std::shared_ptr<round_of_game::Round> round, int type, int sum, std::shared_ptr<player::Player> current_player);

    // damage is dealt depending on the type of cards
    void type_of_cards_damage(std::shared_ptr<round_of_game::Round> round, int type, std::shared_ptr<player::Player> current_Player);

    // damage doesn't depend on the numbers of point dropped or on the type of cards
    void damage_without_parametrs(std::shared_ptr<round_of_game::Round> round, int type, std::shared_ptr<player::Player> current_player, int chosen = 0);

    // player rolls dice
    void rolling_the_dice(std::shared_ptr<round_of_game::Round> round, int type, int sum_1, std::shared_ptr<player::Player> current_player, std::map<std::shared_ptr<player::Player>, int> point_of_foes = {}, int sum_2 = 0);

    //copy the text of other card
    void copy_the_text_of_card(int type, std::shared_ptr<player::Player> current_player);

    // change the player's spell
    void change_spell(std::shared_ptr<round_of_game::Round> round, int type, std::shared_ptr<player::Player> current_player);

    // change the turn order
    void change_order(std::shared_ptr<round_of_game::Round> round, int type, std::shared_ptr<player::Player> current_player);

    // the player interacts with the deck
    void interaction_with_the_deck(std::shared_ptr<round_of_game::Round> round, int type, std::shared_ptr<player::Player> current_player);

    void do_card_effects(std::shared_ptr<round_of_game::Round> round, std::shared_ptr<card::Card> executable_card, std::shared_ptr<player::Player> current_player, int sum = 0,  int sum_1 = 0, int sum_2 = 0,
                         std::map<std::shared_ptr<player::Player>, int> points_of_foes = {}, int chosen = 0, std::shared_ptr<card::Card> chosen_card = nullptr, std::shared_ptr<player::Player> chosen_foe = nullptr);
};
} //card_functions

#endif  // CARDS_FUNCTIONS_H
