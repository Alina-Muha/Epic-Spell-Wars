#ifndef EPIC_SPELL_WARS_GAME_H
#define EPIC_SPELL_WARS_GAME_H
#include "card.h"
#include "player.h"
#include "round.h"
namespace game {

    class Game {

    private:

        std::vector<std::shared_ptr<card::Card>> deck{
        std::make_shared<card::Card>(card::Card(1, card::Card::type::elemental,card::Card::type_of_spell_component::delivery, 10)),
        std::make_shared<card::Card>(card::Card(2, card::Card::type::dark,card::Card::type_of_spell_component::delivery, 5)),
        std::make_shared<card::Card>(card::Card(4, card::Card::type::elemental,card::Card::type_of_spell_component::delivery, 9)),
        std::make_shared<card::Card>(card::Card(5, card::Card::type::primal,card::Card::type_of_spell_component::delivery, 2)),
        std::make_shared<card::Card>(card::Card(6, card::Card::type::primal,card::Card::type_of_spell_component::delivery, 12)),
        std::make_shared<card::Card>(card::Card(7, card::Card::type::primal,card::Card::type_of_spell_component::delivery, 14)),
        std::make_shared<card::Card>(card::Card(8, card::Card::type::dark,card::Card::type_of_spell_component::delivery, 11)),
        std::make_shared<card::Card>(card::Card(9, card::Card::type::dark,card::Card::type_of_spell_component::delivery, 8)),
        std::make_shared<card::Card>(card::Card(10, card::Card::type::elemental,card::Card::type_of_spell_component::delivery, 3)),
        std::make_shared<card::Card>(card::Card(11, card::Card::type::illusion,card::Card::type_of_spell_component::delivery, 19)),
        std::make_shared<card::Card>(card::Card(12, card::Card::type::primal,card::Card::type_of_spell_component::delivery, 1)),
        std::make_shared<card::Card>(card::Card(13, card::Card::type::illusion,card::Card::type_of_spell_component::delivery, 17)),
        std::make_shared<card::Card>(card::Card(14, card::Card::type::dark,card::Card::type_of_spell_component::delivery, 18)),
        std::make_shared<card::Card>(card::Card(1, card::Card::type::primal,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(2, card::Card::type::elemental,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(3, card::Card::type::dark,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(4, card::Card::type::elemental,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(5, card::Card::type::illusion,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(6, card::Card::type::dark,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(7, card::Card::type::ahcane,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(8, card::Card::type::elemental,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(9, card::Card::type::dark,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(10, card::Card::type::primal,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(11, card::Card::type::primal,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(12, card::Card::type::dark,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(13, card::Card::type::primal,card::Card::type_of_spell_component::quality, 0)),
        std::make_shared<card::Card>(card::Card(1, card::Card::type::ahcane,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(2, card::Card::type::ahcane,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(3, card::Card::type::primal,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(4, card::Card::type::primal,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(5, card::Card::type::elemental,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(6, card::Card::type::dark,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(7, card::Card::type::primal,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(8, card::Card::type::dark,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(9, card::Card::type::illusion,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(10, card::Card::type::illusion,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(11, card::Card::type::primal,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(12, card::Card::type::elemental,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(13, card::Card::type::elemental,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(14, card::Card::type::illusion,card::Card::type_of_spell_component::source, 0)),
        std::make_shared<card::Card>(card::Card(15, card::Card::type::elemental,card::Card::type_of_spell_component::source, 0))
        }; // по идее здесь можно просто явно проинициализоровать набор на котором играем

        std::vector<std::shared_ptr<player::Player>> players;

        round_of_game::Round round;
    public:

        void reload_deck();

        bool increase_players_wins(std::shared_ptr<player::Player> winner_of_the_round);

        void play_game();

        std::shared_ptr<player::Player> find_player(const std::string & name);
        round_of_game::Round& get_round();

        void add_player(std::shared_ptr<player::Player> gamer);

    };
}

#endif //EPIC_SPELL_WARS_GAME_H
