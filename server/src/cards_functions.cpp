#include <iostream>
#include <vector>
#include "cards_functions.h"
namespace card_functions{
// it works!
int CardFunctions::get_num_of_player_in_circle(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round){
    int num = 0; // the number of the player in the circle
    for (auto &player : round.get()->get_alive_players()){
        if (player.get()->get_name() == current_player.get()->get_name()){ // players have different names
            break;
        }
        num++;
    }
    return num;
}

// it works!
std::shared_ptr<player::Player> CardFunctions::get_the_strongest_player(std::shared_ptr<player::Player> &current_player,
                                                                        std::shared_ptr<round_of_game::Round> &round){
    int life = 0;
    std::shared_ptr<player::Player>strongest_player = nullptr;
    for (auto &player : round.get()->get_alive_players()){
        if (player.get()->get_lives() > life && current_player.get() != player.get()){
           strongest_player = player;
           life = player.get()->get_lives();
        }
    }
    return strongest_player;
}

// it works!
std::shared_ptr<player::Player> CardFunctions::get_the_weakest_player(std::shared_ptr<player::Player> &current_player,
                                                                      std::shared_ptr<round_of_game::Round> &round){
    int life = 200;
    std::shared_ptr<player::Player>weakest_player = nullptr;
    for (auto &player : round.get()->get_alive_players()){
        if (player.get()->get_lives() < life && player.get() != current_player.get()){
            weakest_player = player;
            life = player.get()->get_lives();
        }
    }
    return weakest_player;
}

// it works!
int CardFunctions::get_achane_num_in_spell(std::shared_ptr<player::Player> &current_player){
    int num = 0;
    for (auto &card: current_player.get()->get_spell()){
        if (card.get()->get_card_type() == card::Card::type::ahcane){
            num++;
        }
    }
    return num;
}

int CardFunctions::get_dark_num_in_spell(std::shared_ptr<player::Player> &current_player){
    int num = 0;
    for (auto &card: current_player.get()->get_spell()){
        if (card.get()->get_card_type() == card::Card::type::dark){
            num++;
        }
    }
    return num;
}

// it works!
int CardFunctions::get_illusion_num_in_spell(std::shared_ptr<player::Player> &current_player){
    int num = 0;
    for (auto &card: current_player.get()->get_spell()){
        if (card.get()->get_card_type() == card::Card::type::illusion){
            num++;
        }
    }
    return num;
}

// it works!
int CardFunctions::get_primal_num_in_spell(std::shared_ptr<player::Player> &current_player){
    int num = 0;
    for (auto &card: current_player.get()->get_spell()){
        if (card.get()->get_card_type() == card::Card::type::primal){
            num++;
        }
    }
    return num;
}

// it works!
int CardFunctions::get_elemental_num_in_spell(std::shared_ptr<player::Player> &current_player){
    int num = 0;
    for (auto &card: current_player.get()->get_spell()){
        if (card.get()->get_card_type() == card::Card::type::elemental){
            num++;
        }
    }
    return num;
}

// it works!
int CardFunctions::unique_types_in_spell(std::shared_ptr<player::Player> &current_player){
    return static_cast<int>(get_achane_num_in_spell(current_player) != 0) + static_cast<int>(get_dark_num_in_spell(current_player) != 0)
            + static_cast<int>(get_illusion_num_in_spell(current_player) != 0)
            + static_cast<int>(get_primal_num_in_spell(current_player) != 0) + static_cast<int>(get_elemental_num_in_spell(current_player) != 0);
}

// it works!
int CardFunctions::get_delivery_card_in_spell(std::shared_ptr<player::Player> &current_player){
    int num = -1;
    int i = 0;
    for (auto &card : current_player.get()->get_spell()){
        if (card.get()->get_type_of_the_spell_component() == card::Card::type_of_spell_component::delivery){
            num = i;
            break;
        }
        i++;
    }
    return num;
}

void CardFunctions::damage_to_the_strongest_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                                   [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player, round);
    int num = get_num_of_player_in_circle(strongest_player, round);
    int count = round.get()->get_alive_players().size();
    std::shared_ptr<player::Player> right_neighbour = round.get()->get_alive_players()[(num + 1) % count];
    std::shared_ptr<player::Player> left_neighbour = round.get()->get_alive_players()[(count + num - 1) % count];

    // it works!
    //type = 1 - card Nuke-U-Lur Meltdown (Delivery_1.png)
    if (type == 1){
        if (sum >= 1 && sum <= 4){
           strongest_player.get()->subtract_lives(1);
        }
        else{
            right_neighbour.get()->subtract_lives(1);
            if (count > 2){
                left_neighbour.get()->subtract_lives(1);
            }
            if (sum >= 5 && sum <= 9){
                strongest_player.get()->subtract_lives(3);
            }
            if (sum >= 10){
                strongest_player.get()->subtract_lives(5);
            }
        }
    }

    // it works!
    // type = 2 - card Gore-Nado (Delivery_5.png)
    if (type == 2){
        if (sum >= 1 && sum <= 4){
            strongest_player.get()->subtract_lives(2);
        }
        if (sum >= 5 && sum <= 9){
            strongest_player.get()->subtract_lives(3);
        }
        if (sum >= 10){
            strongest_player.get()->subtract_lives(6);
        }
    }

    // it works!
    // type = 3 - card Chicken (Delivery_10.png)
    if (type == 3){
        if (sum < 10){
            strongest_player.get()->subtract_lives(1);
        }
        else{
            strongest_player.get()->subtract_lives(7);
        }
    }

    // it works!
    // type = 4 - card Pact With Devil (Delivery_14.png)
    if (type == 4){
        if (sum >= 1 && sum <= 4){
            strongest_player.get()->subtract_lives(1);
        }
        else{
            strongest_player.get()->subtract_lives(2);
            if (sum >= 10){
                int delivery_num = get_delivery_card_in_spell(strongest_player);
                int current_player_num = get_num_of_player_in_circle(current_player, round);
                if (delivery_num != -1 && num > current_player_num){
                    std::shared_ptr<card::Card> delivery_card = strongest_player.get()->get_spell()[delivery_num];
                    strongest_player.get()->get_spell().erase(strongest_player.get()->get_spell().begin() + delivery_num);
                    current_player.get()->add_card_to_spell(delivery_card);
                }
            }
        }
    }
}

// it works!
void CardFunctions::damage_to_the_weakest_player(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum,
                                                 [[maybe_unused]] int type,
                                                 [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    // card Mercy Killing (Delivery_2.png)
    std::shared_ptr<player::Player> weakest_player = get_the_weakest_player(current_player, round);
    if (sum >= 1 && sum <= 4){
        weakest_player.get()->subtract_lives(2);
    }
    if (sum >= 5 && sum <= 9){
        weakest_player.get()->subtract_lives(3);
    }
    if (sum >= 10){
        weakest_player.get()->subtract_lives(4);
    }
}

// it works!
void CardFunctions::damage_to_the_left_neighbour(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum,
                                                 [[maybe_unused]] int type,
                                                 [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    // card Fist O'Nature (Delivery_7.png)
    int num = get_num_of_player_in_circle(current_player, round); // num of current player in cicle
    int count = round.get()->get_alive_players().size(); // count of alive players
    std::shared_ptr<player::Player> left_neighbour = round.get()->get_alive_players()[(count + num - 1) % count];
    if (sum >= 1 && sum <= 4){
        left_neighbour.get()->subtract_lives(1);
    }
    if (sum >= 5 && sum <= 9){
        left_neighbour.get()->subtract_lives(2);
    }
    if (sum >= 10){
        left_neighbour.get()->subtract_lives(4);
    }
};

void CardFunctions::damage_to_the_right_neighbour(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                                  [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    int num = get_num_of_player_in_circle(current_player, round);
    int count = round.get()->get_alive_players().size();
    std::shared_ptr<player::Player> right_neighbour = round.get()->get_alive_players()[(num + 1) % count];

    // type = 1 - card Death-Wish (Delivery_9.png)
    // it works!
    if (type == 1){
        current_player.get()->subtract_lives(1);
        if (sum >= 1 && sum <= 4){
            right_neighbour.get()->subtract_lives(2);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour.get()->subtract_lives(3);
        }
        if (sum >= 10){
            right_neighbour.get()->subtract_lives(5);
        }
    }

    // type = 2 - card Phantasmagoons (Delivery_13.png)
    // it works!
    if (type == 2){
        if (sum >= 1 && sum <= 4){
            right_neighbour.get()->subtract_lives(1);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour.get()->subtract_lives(3);
        }
        if (sum >= 10){
            right_neighbour.get()->subtract_lives(4);
        }
    }

    // type = 3 - card Prickly (Quality_11.png)
    // it works!
    if (type == 3){
        if (sum >= 1 && sum <= 4){
            right_neighbour.get()->subtract_lives(1);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour.get()->subtract_lives(1);
            current_player.get()->add_lives(1);
        }
        if (sum >= 10){
            right_neighbour.get()->subtract_lives(3);
            current_player.get() -> add_lives(3);
        }
    }
}

// for this void it needs to to understand how to get information about the chosen foe, we need client-server
void CardFunctions::damage_to_chosen_foe(std::shared_ptr<player::Player> &current_player, [[maybe_unused]] std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                         std::shared_ptr<player::Player> &chosen_foe){
    // type = 1 - card Deulicious (Quality_3.png)
    // it works!
    if (type == 1){
        if (sum >= 1 && sum <= 4){
            chosen_foe.get()->subtract_lives(2);
        }
        if (sum >= 5 && sum <= 9){
            chosen_foe.get()->subtract_lives(4);
            current_player.get()->subtract_lives(1);
        }
        if (sum >= 10){
            chosen_foe.get()->subtract_lives(5);
            current_player.get()->subtract_lives(2);
        }
    }

    // type = 2 - card Ritualistic (Quality_12.png)
    // it works!
    if (type == 2){
        if (sum >= 1 && sum <= 4){
            current_player.get()->subtract_lives(3);
        }
        if (sum >= 5 && sum <= 9){
            chosen_foe.get()->subtract_lives(3);
        }
        if (sum >= 10){
            chosen_foe.get()->subtract_lives(5);
        }
    }

    // type = 3 - card Bedazzlement (Delivery_11.png)
    // it works!
    if (type == 3){
        if (sum >= 1 && sum <= 4){
            chosen_foe.get()->subtract_lives(1);
        }
        else{
            chosen_foe.get()->subtract_lives(1);
            if (sum >= 5 && sum <= 9){
                int count_of_cards = current_player.get()->get_cards().size();
                std::random_device dev; // random card
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_cards - 1);
                int num_of_card = roll(rng);
                current_player.get()->add_card_to_spell(current_player.get()->get_cards()[num_of_card]);
            }
        }
    }
}

void CardFunctions::hp_to_current_player(std::shared_ptr<player::Player> &current_player,
                                         [[maybe_unused]] std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                         [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    // type = 1 - card Fountain of Youth (Delivery_6.png)
    // it works!
    if (type == 1){
        if (sum >= 5 && sum <= 9){
            current_player.get()->add_lives(2);
        }
        if (sum >= 10){
            current_player.get()->add_lives(4);
        }
    }

    // type = 2 - card Old Scratch's (Source_8.png)
    // it works!
    if (type == 2){
        if (sum >= 1 && sum <= 3){
            current_player.get()->subtract_lives(sum);
        }
        if (sum >= 4 && sum <= 6){
            current_player.get()->add_lives(sum);
        }
    }
}

void CardFunctions::damage_for_several_foes(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum, int type,
                                            [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    int cur_lives = current_player.get()->get_lives();

    // type = 1 - card Meatier Swarm (Delivery_3.png)
    // it works!
    if (type == 1){
        for (auto &player : round.get()->get_alive_players()){
            int foe_lives = player.get()->get_lives();
            if (foe_lives > cur_lives){
                if (sum >= 1 && sum <= 4){
                    player.get()->subtract_lives(1);
                }
                if (sum >= 5 && sum <= 9){
                    player.get()->subtract_lives(3);
                }
                if (sum >= 10){
                    player.get()->subtract_lives(4);
                }
            }
        }
    }

    // type = 2 - card Lightning-Bolt (Delivery_4.png)
    // it works!
    if (type == 2){
        int num = get_num_of_player_in_circle(current_player, round);
        int count = round.get()->get_alive_players().size();
        std::shared_ptr<player::Player> left_neighbour = round.get()->get_alive_players()[(count + num - 1) % count];
        std::shared_ptr<player::Player> left_left_neighbour = round.get()->get_alive_players()[(count + num - 2) % count];
        if (sum >= 1 && sum <= 4){
            left_neighbour.get()->subtract_lives(1);
            if (count > 2){
                left_left_neighbour.get()->subtract_lives(1);
            }
        }
        if (sum >= 5 && sum <= 9){
            left_neighbour.get()->subtract_lives(2);
            if (count > 2){
                left_left_neighbour.get()->subtract_lives(2);
            }
        }
        if (sum >= 10){
            left_neighbour.get()->subtract_lives(4);
            if (count > 2){
                left_left_neighbour.get()->subtract_lives(4);
            }
        }
    }
    // type = 3 - card Exorcism (Delivery_8.png)
    // it works!
    if (type == 3){
        if (sum >= 1 && sum <= 4){
            current_player.get()->subtract_lives(1);
        }
        for (auto &player : round.get()->get_alive_players()){
            if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                if (sum >= 5 && sum <= 9){
                    player.get()->subtract_lives(2);
                }
                if (sum >= 10){
                    player->subtract_lives(4);
                }
            }
        }
    }

    // type = 4 - card Snakedance (Delivery_12.png)
    // it works!
    if (type == 4){
        int num = get_num_of_player_in_circle(current_player, round);
        int count = round.get()->get_alive_players().size(); // count of alive players
        std::shared_ptr<player::Player> right_neighbour = round.get()->get_alive_players()[(num + 1) % count];
        std::shared_ptr<player::Player> left_neighbour = round.get()->get_alive_players()[(count + num - 1) % count];
        if (sum >= 1 && sum <= 4){
            right_neighbour.get()->subtract_lives(1);
            if (count > 2){
                left_neighbour.get()->subtract_lives(1);
            }
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour.get()->subtract_lives(2);
            if (count > 2){
                left_neighbour.get()->subtract_lives(2);
            }
        }
        if (sum >= 10){
            int primal = get_primal_num_in_spell(current_player);
            right_neighbour.get()->subtract_lives(2 * primal);
            if (count > 2){
                left_neighbour.get()->subtract_lives(2 * primal);
            }
        }
    }

    // type = 5 - card Pam and Hecuba's (Source_9.png)
    //
    if (type == 5){
        int primal = get_primal_num_in_spell(current_player);
        int num = get_delivery_card_in_spell(current_player);
        if (num != -1){
            std::shared_ptr<card::Card> delivery_card = current_player.get()->get_spell()[num];
            current_player.get()->get_spell().erase(current_player.get()->get_spell().begin() + num);
            for (auto &player : round.get()->get_alive_players()){
                if (player.get()->get_name() != current_player.get()->get_name()){
                    if (delivery_card.get()->get_number() == 10){
                        if (sum >= 1 && sum <= 9){
                            player.get()->subtract_lives(1);
                        }
                        else{
                            player.get()->subtract_lives(7);
                        }
                    }
                    if (delivery_card.get()->get_number() == 11){
                        player.get()->subtract_lives(1);
                    }
                    if (delivery_card.get()->get_number() == 11){
                        if (sum >= 5 && sum <= 9){
                            int count_of_cards = current_player.get()->get_cards().size();
                            std::random_device dev; // random card
                            std::mt19937 rng(dev());
                            std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_cards - 1);
                            int num_of_card = roll(rng);
                            current_player.get()->add_card_to_spell(current_player.get()->get_cards()[num_of_card]);
                        }
                    }
                    if (delivery_card.get()->get_number() == 12){
                        if (sum >= 1 && sum <= 4){
                            player.get()->subtract_lives(1);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->subtract_lives(2);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(2 * primal);
                        }
                    }
                    if (delivery_card.get()->get_number() == 13){
                        if (sum >= 1 && sum <= 4){
                            player.get()->subtract_lives(1);
                        }
                        if (sum >=5 && sum <= 9){
                            player.get()->subtract_lives(3);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(4);
                        }
                    }
                    if (delivery_card.get()->get_number() == 14){
                        if (sum >=1 && sum <= 4){
                            player.get()->subtract_lives(1);
                        }
                        else{
                            player.get()->subtract_lives(2);
                        }
                    }
                    if (delivery_card.get()->get_number() == 2){
                        if (sum >= 1 && sum <= 4){
                            player.get()->subtract_lives(2);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->subtract_lives(3);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(4);
                        }
                    }
                    if (delivery_card.get()->get_number() == 3){
                        if (sum >= 1 && sum <= 4){
                            player.get()->subtract_lives(1);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->subtract_lives(3);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(4);
                        }
                    }
                    if (delivery_card.get()->get_number() == 4 || delivery_card.get()->get_number() == 7){
                        if (sum >= 1 && sum <= 4){
                            player.get()->subtract_lives(1);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->subtract_lives(2);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(4);
                        }
                    }
                    if (delivery_card.get()->get_number() == 5){
                        if (sum >= 1 && sum <= 4){
                            player.get()->subtract_lives(2);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->subtract_lives(3);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(6);
                        }
                    }
                    if (delivery_card.get()->get_number() == 6){
                        if (sum >= 5 && sum <= 9){
                            player.get()->add_lives(2);
                        }
                        if (sum >= 10){
                            player.get()->add_lives(4);
                        }
                    }
                    if (delivery_card.get()->get_number() == 9){
                        if (sum >= 1 && sum <= 4){
                            player.get()->add_lives(2);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->add_lives(3);
                        }
                        if (sum >= 10){
                            player.get()->add_lives(5);
                        }
                    }

                }
            }
            if (delivery_card.get()->get_number() == 9){
                current_player.get()->subtract_lives(1);
            }
        }
    }
}

void CardFunctions::type_of_cards_damage(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, [[maybe_unused]] int sum, int type,
                                         [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foee){
    int unique = unique_types_in_spell(current_player);

    // type = 1 - card Wyrmtor's (Source_15.png)
    // it works!
    if (type == 1){
        for (auto &player : round.get()->get_alive_players()){
            if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                player->subtract_lives(unique);
            }
        }
    }

    // type = 2 - card Delicious (Quality_2.png)
    // it works!
    if (type == 2){
        for (auto &player : round.get()->get_alive_players()){
            int foe_lives = player.get()->get_lives();
            if (player.get()->get_name() != current_player.get()->get_name() && foe_lives % 2 != 0){ // all players have different names
                player.get()->subtract_lives(unique);
            }
        }
    }

    // type = 3 - card Inferno Tastic (Quality_8.png)
    // it works!
    if (type == 3){
        int elemental = get_elemental_num_in_spell(current_player);
        for (auto &player : round.get()->get_alive_players()){
            if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                player.get()->subtract_lives(elemental);
            }
        }
    }

    // type = 4 - card  Maggoty (Quality_9.png)
    // it works!
    if (type == 4){
        int dark = get_dark_num_in_spell(current_player);
        std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player, round);
        strongest_player.get()->subtract_lives(2 * dark);
    }

    // type = 5 - card Thundering (Quality_13.png)
    // it works!
    if (type == 5){
        std::vector<std::shared_ptr<player::Player>> foes;
        for (auto &player : round.get()->get_alive_players()){
            if (player.get()->get_name() != current_player.get()->get_name()){
                foes.push_back(player);
            }
        }
        int count_of_foes = foes.size();
        for (int i = 0; i < unique; i++){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_foes - 1);
            int num = roll(rng);
            std::shared_ptr<player::Player> random_player = foes[num];
            random_player.get()->subtract_lives(2);
        }
    }

    // type = 6 - card Rose Bottom's (Source_11.png)
    // it works!
    if (type == 6){
        current_player.get()->add_lives( unique);
    }
}

void CardFunctions::damage_without_parametrs(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, [[maybe_unused]]int sum, int type,
                                             [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    int count = round.get()->get_alive_players().size();
    std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player, round);

    // type = 1 - card King Oberon's(Source_4.png)
    // it works!
    if (type == 1){
        current_player.get()->add_lives(2);
    }

    // type = 2 - card Magma Gog's (Source_5.png)
    // it works!
    if (type == 2){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> roll(0, 1);
        int kind = roll(rng);
        if (kind == 0){ // if kind = 0 - player chose left neighbour
            int num = get_num_of_player_in_circle(current_player, round);
            int count = round.get()->get_alive_players().size();
            std::shared_ptr<player::Player> left_neighbour = round.get()->get_alive_players()[(count + num - 1) % count];
            left_neighbour.get()->subtract_lives(2);
        }
        else{ // if kind = 1 - player chose each foe
            for (auto &player : round->get_alive_players()){
                if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                    player.get()->subtract_lives(1);
                }
            }
        }
    }

    // type = 3 - card Midnight Merlin's (Source_6.png)
    // it works!
    if (type == 3){
        strongest_player.get()->subtract_lives(count);
    }

    // type = 4 - card Scorchis's (Source_12.png)
    // it works!
    if (type == 4){
        strongest_player.get()->subtract_lives(3);
    }

    // type = 5 - card Thai-Foon's (Source_13.png)
    // it works!
    if (type == 5){
        int num = get_num_of_player_in_circle(current_player, round);
        for (int i = 0; i < num; i++){
            if (round.get()->get_alive_players()[i].get()->get_name() != current_player.get()->get_name()){
                round.get()->get_alive_players()[i].get()->subtract_lives(3);
            }
        }
    }

    // type = 6 - Boulder Iffic (Quality_1.png)
    // it works!
    if (type == 6){
        int players_without_damage = count - 1;
        int i = 1;
        int num = get_num_of_player_in_circle(current_player, round);
        while (players_without_damage > 0){
            std::shared_ptr<player::Player> left_neighbour = round.get()->get_alive_players()[(count + num - i) % count];
            left_neighbour.get()->subtract_lives(i);
            i++;
            players_without_damage--;
        }
    }

    // type = 7 - helper function for Impatient card (Quality_7)
    // it works!
    if (type == 7){
        for (auto &player : round.get()->get_alive_players()){
            if (player.get()->get_name() != current_player.get()->get_name()){
                player.get()->subtract_lives(1);
            }
        }
    }

    // type = 8 - card Dr Rooty Bark's (Source_3.png)
    // it works!
    if (type == 8){
        current_player.get()->add_lives(3);
    }
}

void CardFunctions::copy_the_text_of_card(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round,
                                          int sum, int type,
                                          std::shared_ptr<player::Player> &chosen_foe){
    // type = 1 - card Disco-Mirrored (Quality_5.png)
    //
    if (type == 1){
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> roll(0, 1);
        int kind = roll(rng);
        // kind = 0 - copy text of Source card
        if (kind == 0){
            for (auto &card : current_player.get()->get_spell()){
                std::shared_ptr<card::Card> executable_card = card;
                if (executable_card.get()->get_card_component() == card::Card::type_of_spell_component::source){
                    do_card_effects(executable_card, current_player, round, sum, chosen_foe);
                }
            }
        }

        // kind = 1 - copy text of Delivery card
        else{
            for (auto &card : current_player.get()->get_spell()){
                std::shared_ptr<card::Card> executable_card = card;
                if (executable_card.get()->get_card_component() == card::Card::type_of_spell_component::delivery){
                    do_card_effects(executable_card, current_player, round, sum, chosen_foe);
                }
            }
        }
    }

    // type = 2 - card Beardo Blasty's (Source_1.png)
    //
    if (type == 2){
        for (auto &card : current_player.get()->get_spell()){
            std::shared_ptr<card::Card> executable_card = card;
            if (card->get_card_component() == card::Card::type_of_spell_component::source){
                do_card_effects(executable_card, current_player, round, sum, chosen_foe);
            }
        }
    }
}

void CardFunctions::change_spell(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round,
                                 [[maybe_unused]] int sum, int type,
                                 [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    int num = get_num_of_player_in_circle(current_player, round);
    int count = round.get()->get_alive_players().size();
    std::shared_ptr<player::Player> strongest_player = nullptr;
    int max_lives = 0;
    // type = 1 - card Festering (Quality_6.png)
    if (type == 1){
        for (int i = num + 1; i < count; i++){
            int foe_lives = round.get()->get_alive_players()[i].get()->get_lives();
            if (foe_lives > max_lives){
                max_lives = foe_lives;
                strongest_player = round.get()->get_alive_players()[i];
            }
        }
        int pos_in_spell = 0;
        for (auto &card : strongest_player.get()->get_spell()){
            if (card.get()->get_card_component() == card::Card::type_of_spell_component::quality){
                strongest_player.get()->get_spell().erase(strongest_player.get()->get_spell().begin() + pos_in_spell);
                break;
            }
            pos_in_spell++;
        }
    }

    // type = 2 - card Mighty-Gro (Quality_10.png)
    //
    if (type == 2){
        current_player.get()->add_lives(2);
        std::shared_ptr<player::Player> weakest_player = get_the_weakest_player(current_player, round);
        if (current_player.get()->get_name() == weakest_player.get()->get_name()){ // all players have different names
            int count_of_cards = current_player.get()->get_cards().size();
            std::random_device dev; // random card
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_cards - 1);
            int rand_card = roll(rng);
            current_player.get()->add_card_to_spell(current_player.get()->get_cards()[rand_card]);
        }
    }

}

void CardFunctions::change_order(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round,
                                 [[maybe_unused]]int sum, [[maybe_unused]] int type,
                                 [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    // card Impatient (Quality_7.png)
    //
    int num = get_num_of_player_in_circle(current_player, round);
    std::swap (round.get()->get_alive_players()[0], round.get()->get_alive_players()[num]);
    damage_without_parametrs(current_player, round, 0, 7, current_player);
}

/*void CardFunctions::interaction_with_the_deck(std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round,
                      [[maybe_unused]] int sum, int type,
                      [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
    // type = 1 - card Bleemax Brainiac's (Source_2.png)
    //
    if (type == 1){
        int size_of_deck = round.get()->get_main_deck().size();
        std::shared_ptr<card::Card> card_1 = round.get()->get_main_deck()[size_of_deck - 1];
        std::shared_ptr<card::Card> card_2 = round->get_main_deck()[size_of_deck - 2];
        if (card_1->get_card_type() == card::Card::type::ahcane){
            current_player.get()->add_card_to_spell(card_1);
        }
        round.get()->get_main_deck().pop_back();
        if (card_2.get()->get_card_type() == card::Card::type::ahcane){
          current_player->add_card_to_spell(card_2);
        }
        round.get()->get_main_deck().pop_back();

    }

    // type = 2 - card Pew and Pew's (Source_10.png)
    //
    if (type == 2){
        int size_of_deck = round.get()->get_main_deck().size();
        std::vector<std::shared_ptr<card::Card>> new_cards(4); // cards from deck
        for (int i = 0; i < 4; i++){
            new_cards[i] = round.get()->get_main_deck()[size_of_deck - i - 1];
        }
        for (auto &card : new_cards){
            if (card.get()->get_card_component() == card::Card::type_of_spell_component::source){
                current_player->add_card(card);
            }
        }
    }
}*/

void CardFunctions::do_card_effects(std::shared_ptr<card::Card> &executable_card, std::shared_ptr<player::Player> &current_player, std::shared_ptr<round_of_game::Round> &round, int sum,
                                    std::shared_ptr<player::Player> &chosen_foe){
    if (executable_card->get_card_component() == card::Card::type_of_spell_component::source) {
        if (executable_card->get_number() == 1) {
            copy_the_text_of_card(current_player, round, sum, 2, chosen_foe);
        }
        /*if (executable_card->get_number() == 2) {
            interaction_with_the_deck(current_player, round, sum, 1, chosen_foe);
        }*/
        if (executable_card->get_number() == 3) {
            damage_without_parametrs(current_player, round, 0, 8, chosen_foe);
        }
        if (executable_card->get_number() == 4) {
            damage_without_parametrs(current_player, round, 0, 1, chosen_foe);
        }
        if (executable_card->get_number() == 5) {
            damage_without_parametrs(current_player, round, 0, 2, chosen_foe);
        }
        if (executable_card->get_number() == 6) {
            damage_without_parametrs(current_player, round, sum, 3, chosen_foe);
        }
        if (executable_card->get_number() == 8){
            hp_to_current_player(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 9) {
            damage_for_several_foes(current_player, round, sum, 5, chosen_foe);
        }
        /*if (executable_card->get_number() == 10) {
            interaction_with_the_deck(current_player, round, sum, 2, chosen_foe);
        }*/
        if (executable_card->get_number() == 11) {
            type_of_cards_damage(current_player, round, sum, 6, chosen_foe);
        }
        if (executable_card->get_number() == 12) {
            damage_without_parametrs(current_player, round, sum, 4, chosen_foe);
        }
        if (executable_card->get_number() == 13) {
            damage_without_parametrs(current_player, round, sum, 5, chosen_foe);
        }
        if (executable_card->get_number() == 15) {
            type_of_cards_damage(current_player, round, sum, 1, chosen_foe);
        }

    } else if (executable_card->get_card_component() == card::Card::type_of_spell_component::quality) {
        if (executable_card->get_number() == 1) {
            damage_without_parametrs(current_player, round, sum, 6, chosen_foe);
        }
        if (executable_card->get_number() == 2) {
            type_of_cards_damage(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 3) {
            damage_to_chosen_foe(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 5) {
            copy_the_text_of_card(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 6) {
            change_spell(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 7) {
            change_order(current_player, round, sum, 0, chosen_foe);
        }
        if (executable_card->get_number() == 8) {
            type_of_cards_damage(current_player, round, sum, 3, chosen_foe);
        }
        if (executable_card->get_number() == 9) {
            type_of_cards_damage(current_player, round, sum, 4, chosen_foe);
        }
        if (executable_card->get_number() == 10) {
            change_spell(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 11) {
            damage_to_the_right_neighbour(current_player, round, sum, 3, chosen_foe);
        }
        if (executable_card->get_number() == 12) {
            damage_to_chosen_foe(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 13) {
            type_of_cards_damage(current_player, round, sum, 5, chosen_foe);
        }

    }
    else /*(type_of_the_spell_component == type_of_spell_component::delivery)*/ {
        if (executable_card->get_number() == 1) {
            damage_to_the_strongest_player(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 2) {
            damage_to_the_weakest_player(current_player, round, sum, 0, chosen_foe);
        }
        if (executable_card->get_number() == 3) {
            damage_for_several_foes(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 4) {
            damage_for_several_foes(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 5) {
            damage_to_the_strongest_player(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 6) {
            hp_to_current_player(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 7) {
            damage_to_the_left_neighbour(current_player, round, sum, 0, chosen_foe);
        }
        if (executable_card->get_number() == 8) {
            damage_for_several_foes(current_player, round, sum, 3, chosen_foe);
        }
        if (executable_card->get_number() == 9) {
            damage_to_the_right_neighbour(current_player, round, sum, 1, chosen_foe);
        }
        if (executable_card->get_number() == 10) {
            damage_to_the_strongest_player(current_player, round, sum, 3, chosen_foe);
        }
        if (executable_card->get_number() == 11) {
            damage_to_chosen_foe(current_player, round, sum, 3, chosen_foe);
        }
        if (executable_card->get_number() == 12) {
            damage_for_several_foes(current_player, round, sum, 4, chosen_foe);
        }
        if (executable_card->get_number() == 13) {
            damage_to_the_right_neighbour(current_player, round, sum, 2, chosen_foe);
        }
        if (executable_card->get_number() == 14) {
            damage_to_the_strongest_player(current_player, round, sum, 4, chosen_foe);
        }
    }
}
} //card_functions
