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
        std::vector<Card> cards;

    public:
        explicit Player(std::string &name_);

        ~Player() = default;

        [[nodiscard]] std::string& get_name();

        void set_name(std::string name_);

        const int get_lives();

        const std::vector<Card> &get_cards();

        void change_lives();

        void change_cards();

        int roll_the_dice(int n = 1);

        void make_move(Card &first, Card &second, Card &third);
    };
}  // namespace player
#endif // PLAYER_H
