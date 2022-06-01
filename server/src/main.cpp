//#include "start_window.h"
#include "round.h"
#include "player.h"
#include "cards_functions.h"
#include <QApplication>
#include <iostream>
#include <cassert>
#include "card.h"
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

    card_functions::CardFunctions card_functions;
    std::cout << "Strongest player is: " << card_functions.get_the_strongest_player(round_ptr, player_ptr_2).get()->get_name() << '\n';
    std::cout << "Weakest player is: " << card_functions.get_the_weakest_player(round_ptr, player_ptr_1).get()->get_name() << '\n';


    card::Card card_for_player1_1(1, card::Card::type::elemental, card::Card::type_of_spell_component::delivery, 1);
    card::Card card_for_player1_2(10, card::Card::type::elemental, card::Card::type_of_spell_component::delivery, 2);
    card::Card card_for_player1_3(11, card::Card::type::illusion, card::Card::type_of_spell_component::delivery, 3);
    card::Card card_for_player1_4(12, card::Card::type::primal, card::Card::type_of_spell_component::delivery, 4);
    card::Card card_for_player1_5(13, card::Card::type::illusion, card::Card::type_of_spell_component::delivery, 5);
    std::shared_ptr<card::Card> card_for_player1_1_ptr = std::make_shared<card::Card>(card_for_player1_1);
    std::shared_ptr<card::Card> card_for_player1_2_ptr = std::make_shared<card::Card>(card_for_player1_2);
    std::shared_ptr<card::Card> card_for_player1_3_ptr = std::make_shared<card::Card>(card_for_player1_3);
    std::shared_ptr<card::Card> card_for_player1_4_ptr = std::make_shared<card::Card>(card_for_player1_4);
    std::shared_ptr<card::Card> card_for_player1_5_ptr = std::make_shared<card::Card>(card_for_player1_5);


    card::Card card_for_player2_1(14, card::Card::type::dark, card::Card::type_of_spell_component::delivery, 1);
    card::Card card_for_player2_2(2, card::Card::type::dark, card::Card::type_of_spell_component::delivery, 2);
    card::Card card_for_player2_3(3, card::Card::type::elemental, card::Card::type_of_spell_component::delivery, 3);
    card::Card card_for_player2_4(4, card::Card::type::elemental, card::Card::type_of_spell_component::delivery, 4);
    card::Card card_for_player2_5(5, card::Card::type::primal, card::Card::type_of_spell_component::delivery, 5);
    std::shared_ptr<card::Card> card_for_player2_1_ptr = std::make_shared<card::Card>(card_for_player2_1);
    std::shared_ptr<card::Card> card_for_player2_2_ptr = std::make_shared<card::Card>(card_for_player2_2);
    std::shared_ptr<card::Card> card_for_player2_3_ptr = std::make_shared<card::Card>(card_for_player2_3);
    std::shared_ptr<card::Card> card_for_player2_4_ptr = std::make_shared<card::Card>(card_for_player2_4);
    std::shared_ptr<card::Card> card_for_player2_5_ptr = std::make_shared<card::Card>(card_for_player2_5);


    card::Card card_for_player3_1(6, card::Card::type::primal, card::Card::type_of_spell_component::delivery, 1);
    card::Card card_for_player3_2(7, card::Card::type::primal, card::Card::type_of_spell_component::delivery, 2);
    card::Card card_for_player3_3(8, card::Card::type::dark, card::Card::type_of_spell_component::delivery, 3);
    card::Card card_for_player3_4(9, card::Card::type::dark, card::Card::type_of_spell_component::delivery, 4);
    card::Card card_for_player3_5(1, card::Card::type::primal, card::Card::type_of_spell_component::quality, 5);
    std::shared_ptr<card::Card> card_for_player3_1_ptr = std::make_shared<card::Card>(card_for_player3_1);
    std::shared_ptr<card::Card> card_for_player3_2_ptr = std::make_shared<card::Card>(card_for_player3_2);
    std::shared_ptr<card::Card> card_for_player3_3_ptr = std::make_shared<card::Card>(card_for_player3_3);
    std::shared_ptr<card::Card> card_for_player3_4_ptr = std::make_shared<card::Card>(card_for_player3_4);
    std::shared_ptr<card::Card> card_for_player3_5_ptr = std::make_shared<card::Card>(card_for_player3_5);


    card::Card card_for_player4_1(10, card::Card::type::primal, card::Card::type_of_spell_component::quality, 1);
    card::Card card_for_player4_2(11, card::Card::type::primal, card::Card::type_of_spell_component::quality, 2);
    card::Card card_for_player4_3(12, card::Card::type::dark, card::Card::type_of_spell_component::quality, 3);
    card::Card card_for_player4_4(13, card::Card::type::primal, card::Card::type_of_spell_component::quality, 4);
    card::Card card_for_player4_5(2, card::Card::type::elemental, card::Card::type_of_spell_component::quality, 5);
    std::shared_ptr<card::Card> card_for_player4_1_ptr = std::make_shared<card::Card>(card_for_player4_1);
    std::shared_ptr<card::Card> card_for_player4_2_ptr = std::make_shared<card::Card>(card_for_player4_2);
    std::shared_ptr<card::Card> card_for_player4_3_ptr = std::make_shared<card::Card>(card_for_player4_3);
    std::shared_ptr<card::Card> card_for_player4_4_ptr = std::make_shared<card::Card>(card_for_player4_4);
    std::shared_ptr<card::Card> card_for_player4_5_ptr = std::make_shared<card::Card>(card_for_player4_5);

    player_ptr_1.get()->add_card(card_for_player1_1_ptr);
    player_ptr_1.get()->add_card(card_for_player1_2_ptr);
    player_ptr_1.get()->add_card(card_for_player1_3_ptr);
    player_ptr_1.get()->add_card(card_for_player1_4_ptr);
    player_ptr_1.get()->add_card(card_for_player1_5_ptr);

    player_ptr_2.get()->add_card(card_for_player2_1_ptr);
    player_ptr_2.get()->add_card(card_for_player2_2_ptr);
    player_ptr_2.get()->add_card(card_for_player2_3_ptr);
    player_ptr_2.get()->add_card(card_for_player2_4_ptr);
    player_ptr_2.get()->add_card(card_for_player2_5_ptr);

    player_ptr_3.get()->add_card(card_for_player3_1_ptr);
    player_ptr_3.get()->add_card(card_for_player3_2_ptr);
    player_ptr_3.get()->add_card(card_for_player3_3_ptr);
    player_ptr_3.get()->add_card(card_for_player3_4_ptr);
    player_ptr_3.get()->add_card(card_for_player3_5_ptr);

    player_ptr_4.get()->add_card(card_for_player4_1_ptr);
    player_ptr_4.get()->add_card(card_for_player4_2_ptr);
    player_ptr_4.get()->add_card(card_for_player4_3_ptr);
    player_ptr_4.get()->add_card(card_for_player4_4_ptr);
    player_ptr_4.get()->add_card(card_for_player4_5_ptr);

    player_ptr_1.get()->add_card_to_spell(card_for_player1_1_ptr);
    player_ptr_1.get()->add_card_to_spell(card_for_player1_2_ptr);
    player_ptr_1.get()->add_card_to_spell(card_for_player1_3_ptr);

    player_ptr_2.get()->add_card_to_spell(card_for_player2_1_ptr);
    player_ptr_2.get()->add_card_to_spell(card_for_player2_2_ptr);
    player_ptr_2.get()->add_card_to_spell(card_for_player2_3_ptr);

    player_ptr_3.get()->add_card_to_spell(card_for_player3_1_ptr);
    player_ptr_3.get()->add_card_to_spell(card_for_player3_2_ptr);
    player_ptr_3.get()->add_card_to_spell(card_for_player3_3_ptr);

    player_ptr_4.get()->add_card_to_spell(card_for_player4_1_ptr);
    player_ptr_4.get()->add_card_to_spell(card_for_player4_2_ptr);
    player_ptr_4.get()->add_card_to_spell(card_for_player4_3_ptr);

    card_functions.damage_without_parametrs(round_ptr, 7, player_ptr_4);
    for (auto &player : round_ptr.get()->get_alive_players()){
        std::cout << player.get()->get_name() << ": " << player.get()->get_lives() << '\n';
    }
    /*for (auto &player: round_ptr.get()->get_alive_players()){
        for (auto &card : player.get()->get_spell()){
            std::cout << card.first.get()->get_number() << ' ';
        }
        std::cout << '\n';
    }*/
    return 0;
}
