#include <iostream>
#include <vector>
<<<<<<< HEAD
#include "../include/Player.h"
#include "../include/cards_functions.h"
#include "../include/сard.h"
class CardsFunctions {
    void delivery_for_one_enemy(const int sum,
                                const int damage1,
                                const int damage2,
                                const int damage3,
                                Player &victim) {
        return;
    }
    void damage_for_enemy_and_current_player(const int type,
                                             const int sum,
                                             Player &enemy,
                                             Player &current_player) {
        return;
    }
    void damage_for_all_players(
            const int type,
            Player &current_player,
            std::vector<&Player> &all_players) {  // how to contact all players??
        return;
    }
    void delivery_vigorous_synthesis(const int sum,
                                     Player &victim,
                                     Player &left_neigh,
                                     Player &right_neigh) {
        return;
    }
    void delivery_snake_hunger(const int sum,
                               Player &left_neigh,
                               Player &right_neigh,
                               Player &current_player) {
        return;
    }
    void quality_spiny(const int sum, Player &victim, Player &current_player) {
        return;
    }
    void copy_source(Player &current_player) {
        return;
    }
    void copy_delivery(Player &current_player) {
        return;
    }
    void quality_discotheque(Player &current_player) {  // if necessary
        return;
    };
    void quality_thunderous(Player &current_player,
                            std::vector<&Player> &all_players) {
        return;
    }
    void source_bradostrel(Player &current_player) {  // if necessary
        return;
    }
    void deck_search(const int type,
                     std::vector<card> cards,
                     Player &current_player) {
        return;
    }
    void source_for_current_player(Player &current_player, const int sum = 0) {
        return;
    }
};
=======
#include "player.h"
#include "cards_functions.h"
#include "card.h"
void CardsFunctions::delivery_for_one_enemy(const int sum,
                            const int damage1,
                            const int damage2,
                            const int damage3,
                            player::Player &victim) {
    return;
}
void CardsFunctions::damage_for_enemy_and_current_player(const int type,
                                         const int sum,
                                         player::Player &enemy,
                                         player::Player &current_player) {
    return;
}
void CardsFunctions::damage_for_all_players(
        const int type,
        player::Player &current_player,
        std::vector<player::Player> &all_players) {  // how to contact all players??
    return;
}
void CardsFunctions::delivery_vigorous_synthesis(const int sum,
                                 player::Player &victim,
                                 player::Player &left_neigh,
                                 player::Player &right_neigh) {
    return;
}
void CardsFunctions::delivery_snake_hunger(const int sum,
                           player::Player &left_neigh,
                           player::Player &right_neigh,
                           player::Player &current_player) {
    return;
}
void CardsFunctions::quality_spiny(const int sum, player::Player &victim, player::Player &current_player) {
    return;
}
void CardsFunctions::copy_source(player::Player &current_player) {
    return;
}
void CardsFunctions::copy_delivery(player::Player &current_player) {
    return;
}
void CardsFunctions::quality_discotheque(player::Player &current_player) {  // if necessary
    return;
};
void CardsFunctions::quality_thunderous(player::Player &current_player,
                        std::vector<player::Player> &all_players) {
    return;
}
void CardsFunctions::source_bradostrel(player::Player &current_player) {  // if necessary
    return;
}
void CardsFunctions::deck_search(const int type,
                 std::vector<card::Card> cards,
                 player::Player &current_player) {
    return;
}
void CardsFunctions::source_for_current_player(player::Player &current_player, const int sum) {
    return;
}
>>>>>>> 1ed37e42f8ec6d5f894cd04e8777323170e07407
