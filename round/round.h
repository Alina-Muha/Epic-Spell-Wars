#ifndef EPIC_SPELL_WARS_ROUND_H
#define EPIC_SPELL_WARS_ROUND_H
#include "card.h"
#include <set>

class round {
    std::vector<bool> alive_players;
    std::vector<card*> main_deck;
    std::vector<card*> used_cards;

};


#endif //EPIC_SPELL_WARS_ROUND_H
