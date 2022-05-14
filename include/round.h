#ifndef ROUND_H
#define ROUND_H
#include <set>
#include <vector>
#include "card.h"
#include "player.h"
namespace round_of_game {
    class Round {

    private:

        static std::vector<player::Player *> alive_players;

        static std::vector<card::Card *> main_deck;

    public:

        const int number_of_cards_in_hand=7;

        void distribute_cards();
        std::vector<player::Player *> &get_players();


        static void sort_priority_of_the_turn();

        static void play_circle();

        static player::Player* play_round();

        static void play_cards(player::Player *gamer);


        void move_cards_from_hand_to_discard();


        std::vector<player::Player *> get_alive_players();

        std::vector<card::Card *> get_main_deck();

        static void load_players(std::vector<player::Player *>& players);

        static void load_cards(std::vector<card::Card *> new_deck);

    };
}

#endif //EPIC_SPELL_WARS_ROUND_H
