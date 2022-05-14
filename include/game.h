#ifndef EPIC_SPELL_WARS_GAME_H
#define EPIC_SPELL_WARS_GAME_H
#include "card.h"
#include "player.h"
#include "round.h"
namespace game {

    class Game {

    private:

        std::vector<card::Card *> deck; // по идее здесь можно просто явно проинициализоровать набор на котом играем
        std::vector<player::Player *> players;
    public:

        void reload_deck();
        bool increase_players_wins(player::Player* winner_of_the_round);
        void play_game();

    };
}

#endif //EPIC_SPELL_WARS_GAME_H
