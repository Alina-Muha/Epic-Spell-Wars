#ifndef ROUND_H
#define ROUND_H
#include <set>
#include <vector>
#include "Card.h"
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

        void play_cards();

    };
}

#endif //EPIC_SPELL_WARS_ROUND_H
