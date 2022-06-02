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



    };
}

#endif //EPIC_SPELL_WARS_ROUND_H
