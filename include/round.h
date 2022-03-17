#ifndef EPIC_SPELL_WARS_ROUND_H
#define EPIC_SPELL_WARS_ROUND_H
#include <set>
#include <vector>
#include "card.h"


namespace round {
    class Round {
    private:
        std::vector<player::Player *> alive_players;
        std::vector<card::Card *> main_deck;

    public:
        void distribute_cards();
        void move_cards_from_hand_to_discard();
        void play_cards();
    };
}

#endif //EPIC_SPELL_WARS_ROUND_H
