//#include "start_window.h"
#include "round.h"
#include "player.h"
#include "cards_functions.h"
#include <QApplication>
#include <iostream>
#include <cassert>
int main(int argc, char *argv[])
{
    round_of_game::Round round;
    std::shared_ptr<round_of_game::Round> round_ptr = std::make_shared<round_of_game::Round>(round);
    player::Player player1("Alina");
    player::Player player2("Diana");
    player::Player player3("Nikita");
    player::Player player4("German");
    std::shared_ptr<player::Player> player_ptr_1 = std::make_shared<player::Player>(player1);
    std::shared_ptr<player::Player> player_ptr_2 = std::make_shared<player::Player>(player2);
    std::shared_ptr<player::Player> player_ptr_3 = std::make_shared<player::Player>(player3);
    std::shared_ptr<player::Player> player_ptr_4 = std::make_shared<player::Player>(player4);
    round_ptr->alive_players.emplace_back(player_ptr_1);
    round_ptr->alive_players.emplace_back(player_ptr_2);
    round_ptr->alive_players.emplace_back(player_ptr_3);
    round_ptr->alive_players.emplace_back(player_ptr_4);
    player_ptr_1.get()->change_lives(21);
    player_ptr_2.get()->change_lives(22);
    player_ptr_3.get()->change_lives(23);
    player_ptr_4.get()->change_lives(10);
    for (auto player : round_ptr.get()->get_alive_players()){
        std::cout << player.get()->get_name() << ": " << player.get()->get_lives() << '\n';
    }
    card_functions::CardFunctions card;
    std::cout << "Strongest player is: " << card.get_the_strongest_player(round_ptr).get()->get_name() << '\n';
    std::cout << "Weakest player is: " << card.get_the_weakest_player(round_ptr).get()->get_name() << '\n';
    return 0;
}
