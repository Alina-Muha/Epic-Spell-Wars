#ifndef ROUND_H
#define ROUND_H
#include <set>
#include <vector>
#include "card.h"
#include "player.h"
namespace round_of_game {
    class Round {

    private:

        static std::vector<std::shared_ptr<player::Player>> alive_players;

        static std::vector<std::shared_ptr<card::Card>> main_deck;

    public:

        const int number_of_cards_in_hand=7;

        void distribute_cards();
        std::vector<std::shared_ptr<player::Player>> &get_players();


        static void sort_priority_of_the_turn();

        static void play_circle();

        static std::shared_ptr<player::Player> play_round();

        static void play_cards(std::shared_ptr<player::Player> gamer);


        void move_cards_from_hand_to_discard();


        std::vector<std::shared_ptr<player::Player>> get_alive_players();

        std::vector<std::shared_ptr<card::Card>> get_main_deck();

        static void load_players(std::vector<std::shared_ptr<player::Player>>& players);

        static void load_cards(std::vector<std::shared_ptr<card::Card>> new_deck);

    };
}

#endif //EPIC_SPELL_WARS_ROUND_H