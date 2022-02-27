#ifndef EPIC_SPELL_WARS_ROUND_H
#define EPIC_SPELL_WARS_ROUND_H
#include <set>
#include <vector>
#include "card.h"


namespace round {
    class round {
    private:
        std::vector<bool> alive_players;
        std::vector<card::card *> main_deck;
        std::vector<card::card *> used_cards;
    public:
        void distribute_cards();
        void move_cards_from_hand_to_discard();
        void playing_cards();

    };
}

#endif //EPIC_SPELL_WARS_ROUND_H
