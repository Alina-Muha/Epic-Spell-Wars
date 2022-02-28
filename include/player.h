#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>

#include "card.h"

class Player {
private:
    std::string name;
    int lives;
    std::vector<Card> cards;

public:
    explicit Player(std::string &name_);
    ~Player() = default;

    std::string get_name();
    const int get_lives();
    const std::vector<Card>& get_cards();

    int change_lives();

    std::vector<Card>& change_cards();

    int roll_the_dice(int n=1);

    void make_move(Card &first, Card &second, Card &third);
};
#endif // PLAYER_H
