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

        std::vector<card::Card *> cards;  // list will be better?

        std::vector<std::pair<card::Card *, int>> spell;

    public:

        explicit Player(std::string &name_);

        ~Player() = default;

        void set_name(std::string name_);

        [[nodiscard]] std::string& get_name();

        [[nodiscard]] std::vector<std::pair<card::Card *, int>> &get_spell();

        [[nodiscard]] int get_lives() const;

        [[nodiscard]] const std::vector<card::Card *> &get_cards();

        void change_lives(int new_lives);

        void add_card(card::Card *new_card);

        void select_card(int index);

        void sort_cards_in_spell();

        bool is_move_correct();

    };
}  // namespace player
#endif // PLAYER_H
