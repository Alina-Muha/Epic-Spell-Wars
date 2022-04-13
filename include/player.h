#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>

#include "card.h"

namespace player {
    class Player {
    private:
        std::string name;
        int lives;
        std::vector<card::Card> cards;

    public:
        explicit Player(std::string &name_);

        ~Player() = default;

        [[nodiscard]] std::string& get_name();

        void set_name(std::string name_);

        [[nodiscard]] int get_lives() const;

        [[nodiscard]] const std::vector<card::Card> &get_cards();

        void change_lives(int new_lives);

        void change_cards();
    };
}  // namespace player
#endif // PLAYER_H
