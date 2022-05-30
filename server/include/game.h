#ifndef EPIC_SPELL_WARS_GAME_H
#define EPIC_SPELL_WARS_GAME_H
#include "card.h"
#include "player.h"
#include "round.h"
namespace game {

    class Game {

    private:

        std::vector<std::shared_ptr<card::Card>> deck; // по идее здесь можно просто явно проинициализоровать набор на котором играем

        std::vector<std::shared_ptr<player::Player>> players;

        round_of_game::Round round;
    public:

        void reload_deck();

        bool increase_players_wins(std::shared_ptr<player::Player> winner_of_the_round);

        void play_game();

        std::shared_ptr<player::Player> find_player(const std::string & name);

        void add_player(std::shared_ptr<player::Player> gamer);
    };
}

#endif //EPIC_SPELL_WARS_GAME_H
