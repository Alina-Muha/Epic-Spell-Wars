#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "card.h"
#include "dice.h"

namespace player {
    class Player {
    private:
        std::string name;
        int lives;


        std::vector<std::shared_ptr<card::Card>> cards;

        std::vector<std::pair<std::shared_ptr<card::Card>, int>> spell;

    public:

        explicit Player(const std::string &name_);

        ~Player() = default;

        void set_name(std::string name_);

        [[nodiscard]] std::string& get_name();

        [[nodiscard]] std::vector<std::pair<std::shared_ptr<card::Card>, int>> &get_spell();

        [[nodiscard]] int get_lives() const;

        [[nodiscard]] const std::vector<std::shared_ptr<card::Card>> &get_cards();

        void add_lives(int lives_to_add);

        void subtract_lives(int lives_to_subtract);

        void change_lives(int new_lives);

        void add_card(std::shared_ptr<card::Card> new_card);

        void select_card(int index);

        void sort_cards_in_spell();

        bool is_move_correct();

        void add_card_to_spell(std::shared_ptr<card::Card> new_card);

    };
}  // namespace player
#endif // PLAYER_H
