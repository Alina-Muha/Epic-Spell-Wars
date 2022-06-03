#ifndef ROUND_H
#define ROUND_H
#include <set>
#include <vector>
#include "card.h"
#include "player.h"
#include "dice.h"
namespace round_of_game {
    class Round {

    private:

        std::vector<std::shared_ptr<player::Player>> alive_players;

        std::vector<std::shared_ptr<card::Card>> main_deck;

        int count_of_alive_players = alive_players.size();

    public:

        const int number_of_cards_in_hand=6;

        void distribute_cards();
        std::vector<std::shared_ptr<player::Player>> &get_players();


        void sort_priority_of_the_turn();

        void play_circle();

        std::shared_ptr<player::Player> play_round();

        void play_cards(std::shared_ptr<player::Player> gamer);


        void move_cards_from_hand_to_discard();


        std::vector<std::shared_ptr<player::Player>> get_alive_players();

        std::vector<std::shared_ptr<card::Card>> get_main_deck();

        void load_players(std::vector<std::shared_ptr<player::Player>>& players);

        void load_cards(std::vector<std::shared_ptr<card::Card>> new_deck);

        int count_the_number_of_dices(std::vector<std::shared_ptr<card::Card>>& cur_spell, std::shared_ptr<card::Card>& cur_card);

        // for card functions
        int get_num_of_player_in_circle(std::shared_ptr<player::Player> &current_player);
        std::shared_ptr<player::Player> get_the_strongest_player(std::shared_ptr<player::Player> &current_player);
        std::shared_ptr<player::Player> get_the_weakest_player(std::shared_ptr<player::Player> &current_player);
        std::shared_ptr<player::Player> get_the_weakest_player_in_round();

        // card_functions:
        // damage is dealt depending on the number of points dropped
        void damage_to_the_strongest_player(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                            std::shared_ptr<player::Player> &chosen_foe);
        void damage_to_the_weakest_player(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                          std::shared_ptr<player::Player> &chosen_foe);
        void damage_to_the_left_neighbour(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                          std::shared_ptr<player::Player> &chosen_foe);
        void damage_to_the_right_neighbour(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                           std::shared_ptr<player::Player> &chosen_foe);
        void damage_to_chosen_foe(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                  std::shared_ptr<player::Player> &chosen_foe);
        void damage_to_random_foe(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                  std::shared_ptr<player::Player> &chosen_foe);
        void hp_to_current_player(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                  std::shared_ptr<player::Player> &chosen_foe);
        // TODO: check Pam and Hecuba's function (type = 5)
        void damage_for_several_foes(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                     std::shared_ptr<player::Player> &chosen_foe);

        // damage is dealt depending on the type of cards
        void type_of_cards_damage(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                  std::shared_ptr<player::Player> &chosen_foe);

        // damage doesn't depend on the numbers of point dropped or on the type of cards
        void damage_without_parametrs(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                      std::shared_ptr<player::Player> &chosen_foe);

        //copy the text of other card
        //TODO: check
        void copy_the_text_of_card(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                   std::shared_ptr<player::Player> &chosen_foe);

        // change the player's spell
        void change_spell(std::shared_ptr<player::Player> &current_player, int sum, int type,
                          std::shared_ptr<player::Player> &chosen_foe);

        // change the turn order
        void change_order(std::shared_ptr<player::Player> &current_player, int sum, int type,
                          std::shared_ptr<player::Player> &chosen_foe);

        void do_card_effects(std::shared_ptr<card::Card> &executable_card, std::shared_ptr<player::Player> &current_player, int sum,
                             std::shared_ptr<player::Player> &chosen_foe);


    };
}

#endif //EPIC_SPELL_WARS_ROUND_H
