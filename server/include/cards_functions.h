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
    int get_num_of_player_in_circle(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round);
    std::shared_ptr<player::Player> get_the_strongest_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round);
    std::shared_ptr<player::Player> get_the_weakest_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round);
    std::shared_ptr<player::Player> get_the_weakest_player_in_round(std::shared_ptr<round_of_game::Round> &round);

    int get_achane_num_in_spell(std::shared_ptr<player::Player> &current_player);
    int get_dark_num_in_spell(std::shared_ptr<player::Player> &current_player);
    int get_illusion_num_in_spell(std::shared_ptr<player::Player> &current_player);
    int get_primal_num_in_spell(std::shared_ptr<player::Player> &current_player); // it works!
    int get_elemental_num_in_spell(std::shared_ptr<player::Player> &current_player); // it works!

    int unique_types_in_spell (std::shared_ptr<player::Player> &current_player); // it works!

    int get_delivery_card_in_spell(std::shared_ptr<player::Player> &current_player);
    int get_source_card_in_spell(std::shared_ptr<player::Player> &current_player);

    // damage is dealt depending on the number of points dropped
    void damage_to_the_strongest_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                        std::shared_ptr<player::Player> &chosen_foe);
    void damage_to_the_weakest_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                      std::shared_ptr<player::Player> &chosen_foe);
    void damage_to_the_left_neighbour(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                      std::shared_ptr<player::Player> &chosen_foe);
    void damage_to_the_right_neighbour(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                       std::shared_ptr<player::Player> &chosen_foe);
    void damage_to_chosen_foe(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                              std::shared_ptr<player::Player> &chosen_foe);
    void damage_to_random_foe(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                              std::shared_ptr<player::Player> &chosen_foe);
    void hp_to_current_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                              std::shared_ptr<player::Player> &chosen_foe);
    // TODO: check Pam and Hecuba's function (type = 5)
    void damage_for_several_foes(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                 std::shared_ptr<player::Player> &chosen_foe);

    // damage is dealt depending on the type of cards
    void type_of_cards_damage(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                              std::shared_ptr<player::Player> &chosen_foe);

    // damage doesn't depend on the numbers of point dropped or on the type of cards
    void damage_without_parametrs(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                  std::shared_ptr<player::Player> &chosen_foe);

    //copy the text of other card
    //TODO: check
    void copy_the_text_of_card(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                               std::shared_ptr<player::Player> &chosen_foe); // it's not verified

    // change the player's spell
    void change_spell(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                      std::shared_ptr<player::Player> &chosen_foe); // it's not verified

    // change the turn order
    void change_order(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                      std::shared_ptr<player::Player> &chosen_foe); // it's not verified

    void do_card_effects(std::shared_ptr<card::Card> &executable_card, std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum,
                         std::shared_ptr<player::Player> &chosen_foe);
};
} //card_functions

#endif  // CARDS_FUNCTIONS_H
