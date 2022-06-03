#include "round.h"
#include "algorithm"
#include <QDebug>
#include <iostream>
namespace round_of_game {


    bool compare_two_players(std::shared_ptr<player::Player>a,std::shared_ptr<player::Player> b){
        if(a->get_cards().size()<b->get_cards().size()){
            return true;
        }
        if(a->get_cards().size()>b->get_cards().size()){

            return false;
        }
        int priority_of_the_turn_a=0;
        int priority_of_the_turn_b=0;

        for(auto i : a->get_spell()){
            priority_of_the_turn_a=std::max(i->get_priority_of_the_turn(), priority_of_the_turn_a);
            priority_of_the_turn_b=std::max(i->get_priority_of_the_turn(), priority_of_the_turn_b);
        }
        if(priority_of_the_turn_a>priority_of_the_turn_b){
            return true;
        }
        if(priority_of_the_turn_a<priority_of_the_turn_b){
            return false;
        }
    }

    void Round::sort_priority_of_the_turn() {
        std::sort(alive_players.begin(), alive_players.end(), compare_two_players);
    }

    void Round::distribute_cards() {
        bool flag_of_end_of_deck=false;
        for(auto i: alive_players){
            if(flag_of_end_of_deck){
                break;
            }
            while(i->get_cards().size()<number_of_cards_in_hand){
                if(main_deck.size()!=0) {
                    i->add_card(main_deck.back());

                    main_deck.pop_back();
                }else{
                    flag_of_end_of_deck=true;
                    break;
                }
            }
        }
    }


    int Round::count_the_number_of_dices(std::vector<std::shared_ptr<card::Card>>& cur_spell, std::shared_ptr<card::Card>& cur_card){
        int result=0;
        for(auto i : cur_spell){
            if(i->get_type_of_the_spell_component()==cur_card->get_type_of_the_spell_component()){
                result++;
            }
        }
        return result;
    }


    void Round::play_cards(std::shared_ptr<player::Player> gamer){
        for(auto i : gamer->get_spell()){
            int number_of_dices=0;
            if(i->check_roll_power()){
                number_of_dices= count_the_number_of_dices(gamer->get_spell(), i);
            }
            int dice_result= dice::roll_the_dice(number_of_dices);
            do_card_effects(i, gamer, dice_result, gamer);
             std::cout <<"done2";
        }
        std::cout <<"done1";
        gamer->get_spell().clear();
        std::cout <<"done";
    }

    void Round::play_circle() {
        for(auto it = alive_players.begin(); it!=alive_players.end();it++){
            auto b = *it;
            if(b->get_lives()<=0){
                alive_players.erase(it);
                b->get_spell().clear();
                continue;
            }
            Round::play_cards(b);
        }
    }

    std::shared_ptr<player::Player> Round::play_round() {

            //тут как то еще надо подождать чтобы все живые свои заклинания скинули
            sort_priority_of_the_turn();
            play_circle();

        if(alive_players.size()==1){
            return alive_players.back();
        }else{
            return nullptr;
        }
    }
    std::vector<std::shared_ptr<player::Player>> Round::get_alive_players(){
        return alive_players;
    }
    std::vector<std::shared_ptr<card::Card>> round_of_game::Round::get_main_deck(){
        return main_deck;
    }
    void Round::load_players(std::vector<std::shared_ptr<player::Player>>& players){
        alive_players=players;
    }
    void Round::load_cards(std::vector<std::shared_ptr<card::Card>> new_deck) {
        main_deck=new_deck;
    }
    std::vector<std::shared_ptr<player::Player>> &Round::get_players(){
        return alive_players;
    }

    // for card functions
    int Round::get_num_of_player_in_circle(std::shared_ptr<player::Player> &current_player){
        int num = 0; // the number of the player in the circle
        for (auto &player : alive_players){
            if (player.get()->get_name() == current_player.get()->get_name()){ // players have different names
                break;
            }
            num++;
        }
        return num;
    }

    std::shared_ptr<player::Player> Round::get_the_strongest_player(std::shared_ptr<player::Player> &current_player){
        int life = 0;
        std::shared_ptr<player::Player>strongest_player = nullptr;
        for (auto &player : alive_players){
            if (player.get()->get_lives() > life && current_player.get() != player.get()){
               strongest_player = player;
               life = player.get()->get_lives();
            }
        }
        return strongest_player;
    }

    std::shared_ptr<player::Player> Round::get_the_weakest_player(std::shared_ptr<player::Player> &current_player){
        int life = 200;
        std::shared_ptr<player::Player>weakest_player = nullptr;
        for (auto &player : alive_players){
            if (player.get()->get_lives() < life && player.get() != current_player.get()){
                weakest_player = player;
                life = player.get()->get_lives();
            }
        }
        return weakest_player;
    }

    std::shared_ptr<player::Player> Round::get_the_weakest_player_in_round(){
        int life = 200;
        std::shared_ptr<player::Player>weakest_player = nullptr;
        for (auto &player : alive_players){
            if (player.get()->get_lives() < life){
                weakest_player = player;
                life = player.get()->get_lives();
            }
        }
        return weakest_player;
    }

    // card_functions:

    void Round::damage_to_the_strongest_player(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                                       [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player);
        int num = get_num_of_player_in_circle(strongest_player);
        std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players];
        std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players + num - 1) % count_of_alive_players];

        //type = 1 - card Nuke-U-Lur Meltdown (Delivery_1.png)
        if (type == 1){
            if (sum >= 1 && sum <= 4){
               strongest_player.get()->subtract_lives(1);
            }
            else{
                right_neighbour.get()->subtract_lives(1);
                if (count_of_alive_players > 2){
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

        // type = 3 - card Chicken (Delivery_10.png)
        if (type == 3){
            if (sum < 10){
                strongest_player.get()->subtract_lives(1);
            }
            else{
                strongest_player.get()->subtract_lives(7);
            }
        }

        // type = 4 - card Pact With Devil (Delivery_14.png)
        if (type == 4){
            if (sum >= 1 && sum <= 4){
                strongest_player.get()->subtract_lives(1);
            }
            else{
                strongest_player.get()->subtract_lives(2);
                if (sum >= 10){
                    int delivery_num = strongest_player->get_delivery_card_in_spell();
                    int current_player_num = get_num_of_player_in_circle(current_player);
                    if (delivery_num != -1 && num > current_player_num){
                        std::shared_ptr<card::Card> delivery_card = strongest_player.get()->get_spell()[delivery_num];
                        strongest_player.get()->delete_card_from_spell(delivery_num);
                        current_player.get()->add_card_to_spell(delivery_card);
                    }
                }
            }
        }
    }

    void Round::damage_to_the_weakest_player(std::shared_ptr<player::Player> &current_player, int sum,
                                                     [[maybe_unused]] int type,
                                                     [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        // card Mercy Killing (Delivery_2.png)
        std::shared_ptr<player::Player> weakest_player = get_the_weakest_player(current_player);
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

    void Round::damage_to_the_left_neighbour(std::shared_ptr<player::Player> &current_player, int sum,
                                                     [[maybe_unused]] int type,
                                                     [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        // card Fist O'Nature (Delivery_7.png)
        int num = get_num_of_player_in_circle(current_player); // num of current player in cicle
        std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players + num - 1) % count_of_alive_players];
        if (sum >= 1 && sum <= 4){
            left_neighbour.get()->subtract_lives(1);
        }
        if (sum >= 5 && sum <= 9){
            left_neighbour.get()->subtract_lives(2);
        }
        if (sum >= 10){
            left_neighbour.get()->subtract_lives(4);
        }
    }

    void Round::damage_to_the_right_neighbour(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                                      [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        int num = get_num_of_player_in_circle(current_player);
        std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players];

        // type = 1 - card Death-Wish (Delivery_9.png)
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
    void Round::damage_to_chosen_foe(std::shared_ptr<player::Player> &current_player,  int sum, int type,
                                             std::shared_ptr<player::Player> &chosen_foe){
        // type = 1 - card Deulicious (Quality_3.png)
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
        if (type == 3){
            if (sum >= 1 && sum <= 4){
                chosen_foe.get()->subtract_lives(1);
            }
            else{
                chosen_foe.get()->subtract_lives(1);
                if (sum >= 5 && sum <= 9){
                    int count_of_cards = current_player->get_num_of_cards();
                    std::random_device dev; // random card
                    std::mt19937 rng(dev());
                    std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_cards - 1);
                    int num_of_card = roll(rng);
                    current_player.get()->add_card_to_spell(current_player.get()->get_cards()[num_of_card]);
                    current_player.get()->delete_card(num_of_card);
                }
            }
        }

        // type = 4 - card The Death Fairy's
        if (type == 4){
            chosen_foe.get()->subtract_lives(2);
        }
    }

    void Round::damage_to_random_foe(std::shared_ptr<player::Player> &current_player, [[maybe_unused]] int sum, int type,
                                             [[maybe_unused]]std::shared_ptr<player::Player> &chosen_foe){
        // card Professor Presto's (Source_2.png) and card Mind-Altering (Quality_4.png)
        std::vector<std::shared_ptr<player::Player>> foes;
        for (auto &player : alive_players){
            if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                foes.push_back(player);
            }
        }
        int count = foes.size();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> roll(0, count - 1);
        int rand_player_num = roll(rng);
        foes[rand_player_num].get()->subtract_lives(3);
    }

    void Round::hp_to_current_player(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                             [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        // type = 1 - card Fountain of Youth (Delivery_6.png)
        if (type == 1){
            if (sum >= 5 && sum <= 9){
                current_player.get()->add_lives(2);
            }
            if (sum >= 10){
                current_player.get()->add_lives(4);
            }
        }

        // type = 2 - card Old Scratch's (Source_8.png)
        if (type == 2){
            if (sum >= 1 && sum <= 3){
                current_player.get()->subtract_lives(sum);
            }
            if (sum >= 4 && sum <= 6){
                current_player.get()->add_lives(sum);
            }
        }
    }

    void Round::damage_for_several_foes(std::shared_ptr<player::Player> &current_player, int sum, int type,
                                                [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        int cur_lives = current_player.get()->get_lives();

        // type = 1 - card Meatier Swarm (Delivery_3.png)
        if (type == 1){
            for (auto &player : alive_players){
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
        if (type == 2){
            int num = get_num_of_player_in_circle(current_player);
            std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players + num - 1) % count_of_alive_players];
            std::shared_ptr<player::Player> left_left_neighbour = alive_players[(count_of_alive_players + num - 2) % count_of_alive_players];
            if (sum >= 1 && sum <= 4){
                left_neighbour.get()->subtract_lives(1);
                if (count_of_alive_players > 2){
                    left_left_neighbour.get()->subtract_lives(1);
                }
            }
            if (sum >= 5 && sum <= 9){
                left_neighbour.get()->subtract_lives(2);
                if (count_of_alive_players > 2){
                    left_left_neighbour.get()->subtract_lives(2);
                }
            }
            if (sum >= 10){
                left_neighbour.get()->subtract_lives(4);
                if (count_of_alive_players > 2){
                    left_left_neighbour.get()->subtract_lives(4);
                }
            }
        }

        // type = 3 - card Exorcism (Delivery_8.png)
        if (type == 3){
            if (sum >= 1 && sum <= 4){
                current_player.get()->subtract_lives(1);
            }
            for (auto &player : alive_players){
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
        if (type == 4){
            int num = get_num_of_player_in_circle(current_player);
            std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players];
            std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players + num - 1) % count_of_alive_players];
            if (sum >= 1 && sum <= 4){
                right_neighbour.get()->subtract_lives(1);
                if (count_of_alive_players > 2){
                    left_neighbour.get()->subtract_lives(1);
                }
            }
            if (sum >= 5 && sum <= 9){
                right_neighbour.get()->subtract_lives(2);
                if (count_of_alive_players > 2){
                    left_neighbour.get()->subtract_lives(2);
                }
            }
            if (sum >= 10){
                int primal = current_player->get_primal_num_in_spell();
                right_neighbour.get()->subtract_lives(2 * primal);
                if (count_of_alive_players > 2){
                    left_neighbour.get()->subtract_lives(2 * primal);
                }
            }
        }

        // type = 5 - card Pam and Hecuba's (Source_9.png)
        if (type == 5){
            int primal = current_player->get_primal_num_in_spell();
            int num = current_player->get_delivery_card_in_spell();
            if (num != -1){
                std::shared_ptr<card::Card> delivery_card = current_player.get()->get_spell()[num];
                current_player->delete_card_from_spell(num);
                for (auto &player : alive_players){
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
                                int count_of_cards = current_player.get()->get_num_of_cards();
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
                        if (delivery_card.get()->get_number() == 8){
                            do_card_effects(delivery_card, current_player, sum, current_player);
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

    void Round::type_of_cards_damage(std::shared_ptr<player::Player> &current_player, [[maybe_unused]] int sum, int type,
                                             [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        int unique = current_player->unique_types_in_spell();

        // type = 1 - card Wyrmtor's (Source_15.png)
        if (type == 1){
            for (auto &player : alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                    player->subtract_lives(unique);
                }
            }
        }

        // type = 2 - card Delicious (Quality_2.png)
        if (type == 2){
            for (auto &player : alive_players){
                int foe_lives = player.get()->get_lives();
                if (player.get()->get_name() != current_player.get()->get_name() && foe_lives % 2 != 0){ // all players have different names
                    player.get()->subtract_lives(unique);
                }
            }
        }

        // type = 3 - card Inferno Tastic (Quality_8.png)
        if (type == 3){
            int elemental = current_player->get_elemental_num_in_spell();
            for (auto &player :  alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                    player.get()->subtract_lives(elemental);
                }
            }
        }

        // type = 4 - card  Maggoty (Quality_9.png)
        if (type == 4){
            int dark = current_player->get_dark_num_in_spell();
            std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player);
            strongest_player.get()->subtract_lives(2 * dark);
        }

        // type = 5 - card Thundering (Quality_13.png)
        if (type == 5){
            std::vector<std::shared_ptr<player::Player>> foes;
            for (auto &player : alive_players){
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
        if (type == 6){
            current_player.get()->add_lives(unique);
        }
    }

    void Round::damage_without_parametrs(std::shared_ptr<player::Player> &current_player, [[maybe_unused]]int sum, int type,
                                                 [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player);

        // type = 1 - card King Oberon's(Source_4.png)
        if (type == 1){
            current_player.get()->add_lives(2);
        }

        // type = 2 - card Magma Gog's (Source_5.png)
        if (type == 2){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> roll(0, 1);
            int kind = roll(rng);
            if (kind == 0){ // if kind = 0 - player chose left neighbour
                int num = get_num_of_player_in_circle(current_player);
                std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players + num - 1) % count_of_alive_players];
                left_neighbour.get()->subtract_lives(3);
            }
            else{ // if kind = 1 - player chose each foe
                for (auto &player : alive_players){
                    if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                        player.get()->subtract_lives(1);
                    }
                }
            }
        }

        // type = 3 - card Midnight Merlin's (Source_6.png)
        if (type == 3){
            strongest_player.get()->subtract_lives(count_of_alive_players);
        }

        // type = 4 - card Scorchis's (Source_12.png)
        if (type == 4){
            strongest_player.get()->subtract_lives(3);
        }

        // type = 5 - card Thai-Foon's (Source_13.png)
        if (type == 5){
            int num = get_num_of_player_in_circle(current_player);
            for (int i = 0; i < num; i++){
                if (alive_players[i].get()->get_name() != current_player.get()->get_name()){
                    alive_players[i].get()->subtract_lives(3);
                }
            }
        }

        // type = 6 - Boulder Iffic (Quality_1.png)
        if (type == 6){
            int players_without_damage = count_of_alive_players - 1;
            int i = 1;
            int num = get_num_of_player_in_circle(current_player);
            while (players_without_damage > 0){
                std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players + num - i) % count_of_alive_players];
                left_neighbour.get()->subtract_lives(i);
                i++;
                players_without_damage--;
            }
        }

        // type = 7 - helper function for Impatient card (Quality_7)
        if (type == 7){
            for (auto &player : alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){
                    player.get()->subtract_lives(1);
                }
            }
        }

        // type = 8 - card Dr Rooty Bark's (Source_3.png)
        if (type == 8){
            current_player.get()->add_lives(3);
        }
    }

    void Round::copy_the_text_of_card(std::shared_ptr<player::Player> &current_player,
                                              int sum, int type,
                                              std::shared_ptr<player::Player> &chosen_foe){
        // type = 1 - card Disco-Mirrored (Quality_5.png)
        if (type == 1){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> roll(0, 1);
            int kind = roll(rng);
            if (kind == 0){
                int num_of_source = current_player->get_num_of_cards();
                if (num_of_source != -1){
                    std::shared_ptr<card::Card> executable_card = current_player.get()->get_cards()[num_of_source];
                    do_card_effects(executable_card, current_player, sum, chosen_foe);
                }
            }

            // kind = 1 - copy text of Delivery card
            else{
                int num_of_delivery = current_player->get_delivery_card_in_spell();
                if (num_of_delivery != -1){
                    std::shared_ptr<card::Card> executable_card = current_player.get()->get_cards()[num_of_delivery];
                    do_card_effects(executable_card, current_player, sum, chosen_foe);
                }
            }
        }

        // type = 2 - card Beardo Blasty's (Source_1.png)
        if (type == 2){
            int delivery_num = current_player->get_delivery_card_in_spell();
            if (delivery_num != -1){
                std::shared_ptr<card::Card> delivery_card = current_player.get()->get_spell()[delivery_num];
                do_card_effects(delivery_card, current_player, sum, chosen_foe);
            }
        }
    }

    void Round::change_spell(std::shared_ptr<player::Player> &current_player,
                                     [[maybe_unused]] int sum, int type,
                                     [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        int num = get_num_of_player_in_circle(current_player);
        std::shared_ptr<player::Player> strongest_player = nullptr;
        int max_lives = 0;
        // type = 1 - card Festering (Quality_6.png)
        if (type == 1){
            for (int i = num + 1; i < count_of_alive_players; i++){
                int foe_lives = alive_players[i].get()->get_lives();
                if (foe_lives > max_lives){
                    max_lives = foe_lives;
                    strongest_player = alive_players[i];
                }
            }
            int pos_in_spell = 0;
            for (auto &card : strongest_player.get()->get_spell()){
                if (card.get()->get_card_component() == card::Card::type_of_spell_component::quality){
                    strongest_player->delete_card_from_spell(pos_in_spell);
                    break;
                }
                pos_in_spell++;
            }
        }

        // type = 2 - card Mighty-Gro (Quality_10.png)
        if (type == 2){
            current_player.get()->add_lives(2);
            std::shared_ptr<player::Player> weakest_player = get_the_weakest_player_in_round();
            if (current_player.get()->get_name() == weakest_player.get()->get_name()){
                int count_of_cards = current_player.get()->get_cards().size();
                std::random_device dev; // random card
                std::mt19937 rng(dev());
                std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_cards - 1);
                int rand_card = roll(rng);
                current_player.get()->add_card_to_spell(current_player.get()->get_cards()[rand_card]);
                current_player.get()->get_cards().erase(current_player.get()->get_cards().begin() + rand_card);
            }
        }

    }

    void Round::change_order(std::shared_ptr<player::Player> &current_player,
                                     [[maybe_unused]]int sum, [[maybe_unused]] int type,
                                     [[maybe_unused]] std::shared_ptr<player::Player> &chosen_foe){
        // card Impatient (Quality_7.png)
        // TODO: check, that player first in round
        int num = get_num_of_player_in_circle(current_player);
        //std::swap (alive_players[0], alive_players[num]);
        damage_without_parametrs(current_player, 0, 7, current_player);
    }
    void Round::do_card_effects(std::shared_ptr<card::Card> &executable_card, std::shared_ptr<player::Player> &current_player, int sum,
                                        std::shared_ptr<player::Player> &chosen_foe){
        if (executable_card->get_card_component() == card::Card::type_of_spell_component::source) {
            if (executable_card->get_number() == 1) {
                copy_the_text_of_card(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 2) {
                damage_to_random_foe(current_player, sum, 0, chosen_foe);
            }
            if (executable_card->get_number() == 3) {
                damage_without_parametrs(current_player, 0, 8, chosen_foe);
            }
            if (executable_card->get_number() == 4) {
                damage_without_parametrs(current_player, 0, 1, chosen_foe);
            }
            if (executable_card->get_number() == 5) {
                damage_without_parametrs(current_player, 0, 2, chosen_foe);
            }
            if (executable_card->get_number() == 6) {
                damage_without_parametrs(current_player, sum, 3, chosen_foe);
            }
            if (executable_card->get_number() == 8){
                hp_to_current_player(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 9) {
                damage_for_several_foes(current_player, sum, 5, chosen_foe);
            }
            if (executable_card->get_number() == 10) {
                damage_to_chosen_foe(current_player, sum, 4, chosen_foe);
            }
            if (executable_card->get_number() == 11) {
                type_of_cards_damage(current_player, sum, 6, chosen_foe);
            }
            if (executable_card->get_number() == 12) {
                damage_without_parametrs(current_player, sum, 4, chosen_foe);
            }
            if (executable_card->get_number() == 13) {
                damage_without_parametrs(current_player, sum, 5, chosen_foe);
            }
            if (executable_card->get_number() == 15) {
                type_of_cards_damage(current_player, sum, 1, chosen_foe);
            }

        } else if (executable_card->get_card_component() == card::Card::type_of_spell_component::quality) {
            if (executable_card->get_number() == 1) {
                damage_without_parametrs(current_player, sum, 6, chosen_foe);
            }
            if (executable_card->get_number() == 2) {
                type_of_cards_damage(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 3) {
                damage_to_chosen_foe(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 4){
                damage_to_random_foe(current_player, sum, 0, chosen_foe);
            }
            if (executable_card->get_number() == 5) {
                copy_the_text_of_card(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 6) {
                change_spell(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 7) {
                change_order(current_player, sum, 0, chosen_foe);
            }
            if (executable_card->get_number() == 8) {
                type_of_cards_damage(current_player, sum, 3, chosen_foe);
            }
            if (executable_card->get_number() == 9) {
                type_of_cards_damage(current_player, sum, 4, chosen_foe);
            }
            if (executable_card->get_number() == 10) {
                change_spell(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 11) {
                damage_to_the_right_neighbour(current_player, sum, 3, chosen_foe);
            }
            if (executable_card->get_number() == 12) {
                damage_to_chosen_foe(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 13) {
                type_of_cards_damage(current_player, sum, 5, chosen_foe);
            }

        }
        else /*(type_of_the_spell_component == type_of_spell_component::delivery)*/ {
            if (executable_card->get_number() == 1) {
                damage_to_the_strongest_player(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 2) {
                damage_to_the_weakest_player(current_player, sum, 0, chosen_foe);
            }
            if (executable_card->get_number() == 3) {
                damage_for_several_foes(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 4) {
                damage_for_several_foes(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 5) {
                damage_to_the_strongest_player(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 6) {
                hp_to_current_player(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 7) {
                damage_to_the_left_neighbour(current_player, sum, 0, chosen_foe);
            }
            if (executable_card->get_number() == 8) {
                damage_for_several_foes(current_player, sum, 3, chosen_foe);
            }

            if (executable_card->get_number() == 9) {
                damage_to_the_right_neighbour(current_player, sum, 1, chosen_foe);
            }
            if (executable_card->get_number() == 10) {
                damage_to_the_strongest_player(current_player, sum, 3, chosen_foe);
            }
            if (executable_card->get_number() == 11) {
                damage_to_chosen_foe(current_player, sum, 3, chosen_foe);
            }
            if (executable_card->get_number() == 12) {
                damage_for_several_foes(current_player, sum, 4, chosen_foe);
            }
            if (executable_card->get_number() == 13) {
                damage_to_the_right_neighbour(current_player, sum, 2, chosen_foe);
            }
            if (executable_card->get_number() == 14) {
                damage_to_the_strongest_player(current_player, sum, 4, chosen_foe);
            }
        }
    }
}
