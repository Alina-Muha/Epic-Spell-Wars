#ifndef ROUND_H
#define ROUND_H
#include <set>
#include <vector>
#include "card.h"
#include "player.h"

namespace round {
    class Round {

    private:

        std::vector<player::Player *> alive_players;
        std::vector<card::Card *> main_deck;

    public:

        const int number_of_cards_in_hand=7;

        void distribute_cards();


        void sort_priority_of_the_turn();

        void play_circle();

        void play_round();

        void play_cards(player::Player *gamer);


        void move_cards_from_hand_to_discard();
        std::vector<player::Player *> get_alive_players();
        std::vector<card::Card *> get_main_deck();
    };
}

#endif //EPIC_SPELL_WARS_ROUND_H