#include "round.h"
#include <algorithm>
//#include <iostream>
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

    int Round::count_of_alive_players(){
        return alive_players.size();
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
                std::cout << "aboba";
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
            auto to = do_card_effects(i, gamer, dice_result);
            send_logs_func(QString::fromStdString(gamer->get_name()), to, dice_result, QString::fromStdString(i->convert_type_in_string(i->get_type_of_the_spell_component())), i->get_number());
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

            sort_priority_of_the_turn();
            play_circle();
            distribute_cards();
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
        std::shared_ptr<player::Player>strongest_player = current_player;
        for (auto &player : alive_players){
            if (player.get()->get_lives() > life && current_player.get() != player.get()){
               strongest_player = player;
               life = player.get()->get_lives();
            }
        }
        qDebug() << "strongest_player "<<QString::fromStdString(strongest_player->get_name());
        return strongest_player;
    }

    std::shared_ptr<player::Player> Round::get_the_weakest_player(std::shared_ptr<player::Player> &current_player){
        int life = 200;
        std::shared_ptr<player::Player>weakest_player = current_player;
        for (auto &player : alive_players){
            if (player.get()->get_lives() < life /*&& player.get() != current_player.get()*/){
                weakest_player = player;
                life = player.get()->get_lives();
            }
        }
        qDebug() << "weakest_player "<<QString::fromStdString(weakest_player->get_name());
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

    QList<QString> Round::damage_to_the_strongest_player(std::shared_ptr<player::Player> &current_player, int sum, int type){
        QList<QString> players_with_damage;
        std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player);
        int num = get_num_of_player_in_circle(strongest_player);
      
        std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players()];
        std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - 1) % count_of_alive_players()];


        //type = 1 - card Nuke-U-Lur Meltdown (Delivery_1.png)
        if (type == 1){
            if (sum >= 1 && sum <= 4){
               qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
               strongest_player.get()->subtract_lives(1);
            }
            else{
                qDebug() <<"right_player: " << QString::fromStdString(right_neighbour.get()->get_name());
                right_neighbour.get()->subtract_lives(1);
                if (count_of_alive_players() > 2){

                    left_neighbour.get()->subtract_lives(1);

                }
                if (sum >= 5 && sum <= 9){
                    qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                    strongest_player->subtract_lives(3);
                }
                if (sum >= 10){
                    qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                    strongest_player->subtract_lives(5);
                }
            }
        }

        // type = 2 - card Gore-Nado (Delivery_5.png)
        if (type == 2){
            if (sum >= 1 && sum <= 4){
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(2);
            }
            if (sum >= 5 && sum <= 9){
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(3);
            }
            if (sum >= 10){
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(6);
            }
        }

        // type = 3 - card Chicken (Delivery_10.png)
        if (type == 3){
            if (sum < 10){
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(1);
            }
            else{
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(7);
            }
        }

        // type = 4 - card Pact With Devil (Delivery_14.png)
        if (type == 4){
            if (sum >= 1 && sum <= 4){
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(1);
            }
            else{
                qDebug() <<"strongest_player: " << QString::fromStdString(strongest_player.get()->get_name());
                strongest_player->subtract_lives(2);
                if (sum >= 10){
                    int delivery_num = strongest_player->get_delivery_card_in_spell();
                    int current_player_num = get_num_of_player_in_circle(current_player);
                    if (delivery_num != -1 && num > current_player_num){
                        std::shared_ptr<card::Card> delivery_card = strongest_player.get()->get_spell()[delivery_num];
                        strongest_player->delete_card_from_spell(delivery_num);
                        current_player->add_card_to_spell(delivery_card);
                    }
                }
            }
        }
        players_with_damage.append(QString::fromStdString(strongest_player.get()->get_name()));
        return players_with_damage;
    }

    QList<QString> Round::damage_to_the_weakest_player(std::shared_ptr<player::Player> &current_player, int sum,
                                                     [[maybe_unused]] int type){
        QList<QString> players_with_damage;
        // card Mercy Killing (Delivery_2.png)
        std::shared_ptr<player::Player> weakest_player = get_the_weakest_player(current_player);
        if (sum >= 1 && sum <= 4){
            weakest_player->subtract_lives(2);
        }
        if (sum >= 5 && sum <= 9){
            weakest_player->subtract_lives(3);
        }
        if (sum >= 10){
            weakest_player->subtract_lives(4);
        }
        players_with_damage.append(QString::fromStdString(weakest_player.get()->get_name()));
        return players_with_damage;
    }

    QList<QString> Round::damage_to_the_left_neighbour(std::shared_ptr<player::Player> &current_player, int sum,
                                                     [[maybe_unused]] int type){
        QList<QString> players_with_damage;
        // card Fist O'Nature (Delivery_7.png)

        int num = get_num_of_player_in_circle(current_player); // num of current player in circle

        std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - 1) % count_of_alive_players()];
        if (sum >= 1 && sum <= 4){
            left_neighbour.get()->subtract_lives(1);
        }
        if (sum >= 5 && sum <= 9){
            left_neighbour.get()->subtract_lives(2);
        }
        if (sum >= 10){
            left_neighbour.get()->subtract_lives(4);
        }
        players_with_damage.append(QString::fromStdString(left_neighbour.get()->get_name()));
        return players_with_damage;
    }

    QList<QString> Round::damage_to_the_right_neighbour(std::shared_ptr<player::Player> &current_player, int sum, int type){
        QList<QString> players_with_damage;
        int num = get_num_of_player_in_circle(current_player);
        std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players()];

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
        players_with_damage.append(QString::fromStdString(right_neighbour.get()->get_name()));
        return players_with_damage;
    }

    QList<QString> Round::damage_to_random_foe(std::shared_ptr<player::Player> &current_player, [[maybe_unused]] int sum, int type){

        QList<QString> players_with_damage;
        std::vector<std::shared_ptr<player::Player>> foes;
        for (auto &player : alive_players){
            if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                if (type == 2){
                    if (player.get()->get_lives() % 2 != 0){
                        foes.push_back(player);
                    }
                }
                else{
                    foes.push_back(player);
                }
            }
        }
        int count = foes.size();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> roll(0, count - 1);
        int rand_player_num = roll(rng);
        std::shared_ptr<player::Player> random_foe = foes[rand_player_num];

        // type = 1 - card Professor Presto's (Source_2.png) and card Mind-Altering (Quality_4.png)
        if (type == 1){
            random_foe.get()->subtract_lives(3);
        }

        // type = 2 - card Deulicious (Quality_3.png)
        if (type == 2){
            if (sum >= 1 && sum <= 4){
                random_foe.get()->subtract_lives(2);
            }
            if (sum >= 5 && sum <= 9){
                random_foe.get()->subtract_lives(4);
                current_player.get()->subtract_lives(1);
            }
            if (sum >= 10){
                random_foe.get()->subtract_lives(5);
                 current_player.get()->subtract_lives(2);
            }
        }
        players_with_damage.append(QString::fromStdString(random_foe.get()->get_name()));
        return players_with_damage;
    }

    QList<QString> Round::hp_to_current_player(std::shared_ptr<player::Player> &current_player, int sum, int type){
        QList<QString> players_with_damage;
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
        return players_with_damage;
    }

    QList<QString> Round::damage_for_several_foes(std::shared_ptr<player::Player> &current_player, int sum, int type){
        QList<QString> players_with_damage;
        int cur_lives = current_player.get()->get_lives();

        int num = get_num_of_player_in_circle(current_player);
        std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players()];
        std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - 1) % count_of_alive_players()];

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
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                }
            }
        }

        // type = 2 - card Lightning-Bolt (Delivery_4.png)
        if (type == 2){
            std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - 1) % count_of_alive_players()];
            std::shared_ptr<player::Player> left_left_neighbour = alive_players[(count_of_alive_players() + num - 2) % count_of_alive_players()];
            players_with_damage.append(QString::fromStdString(left_neighbour.get()->get_name()));
            if (count_of_alive_players() > 2){
                players_with_damage.append(QString::fromStdString(left_left_neighbour.get()->get_name()));
            }
            if (sum >= 1 && sum <= 4){
                left_neighbour.get()->subtract_lives(1);
                if (count_of_alive_players() > 2){
                    left_left_neighbour.get()->subtract_lives(1);
                }
            }
            if (sum >= 5 && sum <= 9){
                left_neighbour.get()->subtract_lives(2);
                if (count_of_alive_players() > 2){
                    left_left_neighbour.get()->subtract_lives(2);
                }
            }
            if (sum >= 10){
                left_neighbour.get()->subtract_lives(4);
                if (count_of_alive_players() > 2){
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
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                    if (sum >= 5 && sum <= 9){
                        player.get()->subtract_lives(2);
                    }
                    if (sum >= 10){
                        player->subtract_lives(4);
                    }
                }
            }
        }

        // type = 4 - card Snakedance (Delivery_12.png), type = 6 - card Cone of Acid (Delivery_11.png)
        if (type == 4 || type == 6){
            players_with_damage.append(QString::fromStdString(right_neighbour.get()->get_name()));
            if (count_of_alive_players() > 2){
                players_with_damage.append(QString::fromStdString(left_neighbour.get()->get_name()));
            }
            if (sum >= 1 && sum <= 4){
                right_neighbour.get()->subtract_lives(1);
                if (count_of_alive_players() > 2){
                    left_neighbour.get()->subtract_lives(1);
                }
            }
            if (sum >= 5 && sum <= 9){
                right_neighbour.get()->subtract_lives(2);
                if (count_of_alive_players() > 2){
                    left_neighbour.get()->subtract_lives(2);
                }
            }
            else{
                if (type == 4){
                    int primal = current_player->get_primal_num_in_spell();
                    right_neighbour.get()->subtract_lives(2 * primal);
                    if (count_of_alive_players() > 2){
                        left_neighbour.get()->subtract_lives(2 * primal);
                    }
                }
                else{
                    right_neighbour.get()->subtract_lives(4);
                    if (count_of_alive_players() > 2){
                        left_neighbour.get()->subtract_lives(4);
                    }
                }
            }
        }

        // type = 5 - card Pam and Hecuba's (Source_9.png)
        if (type == 5){
            int primal = current_player->get_primal_num_in_spell();
            int delivery_num = current_player->get_delivery_card_in_spell();
            if (delivery_num != -1){
                std::shared_ptr<card::Card> delivery_card = current_player.get()->get_spell()[delivery_num];
                current_player->delete_card_from_spell(delivery_num);
                for (auto &player : alive_players){
                    int num = get_num_of_player_in_circle(player);
                    std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - 1) % count_of_alive_players()];
                    std::shared_ptr<player::Player> right_neighbour = alive_players[(num + 1) % count_of_alive_players()];
                    if (player.get()->get_name() != current_player.get()->get_name()){
                        if (delivery_card.get()->get_number() == 1){
                            if (sum >= 1 && sum <= 4){
                                player.get()->subtract_lives(1);
                            }
                            else{
                                left_neighbour.get()->subtract_lives(1);
                                if (count_of_alive_players() > 2){
                                    right_neighbour.get()->subtract_lives(1);
                                }
                                if (sum >=5 && sum <= 9){
                                    player.get()->subtract_lives(3);
                                }
                                if (sum >= 10){
                                    player.get()->subtract_lives(5);
                                }
                            }
                        }
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
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                }
                if (delivery_card.get()->get_number() == 9){
                    current_player.get()->subtract_lives(1);
                }
                if (delivery_card.get()->get_number() == 11 && (sum >= 5 && sum <= 9)){
                    int count_of_cards = current_player.get()->get_num_of_cards();
                    std::random_device dev; // random card
                    std::mt19937 rng(dev());
                    std::uniform_int_distribution<std::mt19937::result_type> roll(0, count_of_cards - 1);
                    int num_of_card = roll(rng);
                    current_player.get()->add_card_to_spell(current_player.get()->get_cards()[num_of_card]);
                }
                if (delivery_card.get()->get_number() == 8){
                    return do_card_effects(delivery_card, current_player, sum);
                }
            }
        }
        return players_with_damage;
    }

    QList<QString> Round::type_of_cards_damage(std::shared_ptr<player::Player> &current_player, [[maybe_unused]] int sum, int type){
        QList<QString> players_with_damage;
        int unique = current_player->unique_types_in_spell();

        // type = 1 - card Wyrmtor's (Source_15.png)
        if (type == 1){
            for (auto &player : alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                    player->subtract_lives(unique);
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                }
            }
        }

        // type = 2 - card Delicious (Quality_2.png)
        if (type == 2){
            for (auto &player : alive_players){
                int foe_lives = player.get()->get_lives();
                if (player.get()->get_name() != current_player.get()->get_name() && foe_lives % 2 != 0){ // all players have different names
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                    player.get()->subtract_lives(unique);
                }
            }
        }

        // type = 3 - card Inferno Tastic (Quality_8.png)
        if (type == 3){
            int elemental = current_player->get_elemental_num_in_spell();
            for (auto &player :  alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                    player.get()->subtract_lives(elemental);
                }
            }
        }

        // type = 4 - card  Maggoty (Quality_9.png)
        if (type == 4){
            int dark = current_player->get_dark_num_in_spell();
            std::shared_ptr<player::Player> strongest_player = get_the_strongest_player(current_player);
            players_with_damage.append(QString::fromStdString(strongest_player.get()->get_name()));
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
                players_with_damage.append(QString::fromStdString(random_player.get()->get_name()));
            }
        }

        // type = 6 - card Rose Bottom's (Source_11.png)
        if (type == 6){
            current_player.get()->add_lives(unique);
        }
        return players_with_damage;
    }

    QList<QString> Round::damage_without_parametrs(std::shared_ptr<player::Player> &current_player, [[maybe_unused]]int sum, int type){
        QList<QString> players_with_damage;
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
                std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - 1) % count_of_alive_players()];
                left_neighbour.get()->subtract_lives(3);
                players_with_damage.append(QString::fromStdString(left_neighbour.get()->get_name()));
            }
            else{ // if kind = 1 - player chose each foe
                for (auto &player : alive_players){
                    if (player.get()->get_name() != current_player.get()->get_name()){ // all players have different names
                        player.get()->subtract_lives(1);
                        players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                    }
                }
            }
        }

        // type = 3 - card Midnight Merlin's (Source_6.png)
        if (type == 3){
            strongest_player.get()->subtract_lives(count_of_alive_players());
            players_with_damage.append(QString::fromStdString(strongest_player.get()->get_name()));
        }

        // type = 4 - card Scorchis's (Source_12.png)
        if (type == 4){
            strongest_player.get()->subtract_lives(3);
            players_with_damage.append(QString::fromStdString(strongest_player.get()->get_name()));
        }

        // type = 5 - card Thai-Foon's (Source_13.png)
        if (type == 5){
            int num = get_num_of_player_in_circle(current_player);
            for (int i = 0; i < num; i++){
                if (alive_players[i].get()->get_name() != current_player.get()->get_name()){
                    alive_players[i].get()->subtract_lives(3);
                    players_with_damage.append(QString::fromStdString(alive_players[i].get()->get_name()));
                }
            }
        }

        // type = 6 - Boulder Iffic (Quality_1.png)
        if (type == 6){
            int players_without_damage = count_of_alive_players() - 1;
            int i = 1;
            int num = get_num_of_player_in_circle(current_player);
            while (players_without_damage > 0){
                std::shared_ptr<player::Player> left_neighbour = alive_players[(count_of_alive_players() + num - i) % count_of_alive_players()];
                left_neighbour.get()->subtract_lives(i);
                players_with_damage.append(QString::fromStdString(left_neighbour.get()->get_name()));
                i++;
                players_without_damage--;
            }
        }

        // type = 7 - helper function for Impatient card (Quality_7)
        if (type == 7){
            for (auto &player : alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){
                    player.get()->subtract_lives(1);
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                }
            }
        }

        // type = 8 - card Dr Rooty Bark's (Source_3.png)
        if (type == 8){
            current_player.get()->add_lives(3);
        }

        // type = 9 - card The Death Fairy's (Source_10.png)
        if (type == 9){
            for (auto &player: alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){
                    player.get()->subtract_lives(2);
                    players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                }
            }
        }

        // type = 10 - card Dragon hoard (Quality_12.png)
        if (type == 10){
            for (auto & player : alive_players){
                if (player.get()->get_name() != current_player.get()->get_name()){
                    if (player.get()->get_delivery_card_in_spell() > 0){
                        if (sum >=1 && sum <= 4){
                            player.get()->subtract_lives(1);
                        }
                        if (sum >= 5 && sum <= 9){
                            player.get()->subtract_lives(2);
                        }
                        if (sum >= 10){
                            player.get()->subtract_lives(3);
                        }
                        players_with_damage.append(QString::fromStdString(player.get()->get_name()));
                    }
                }
            }
        }
        return players_with_damage;
    }

    QList<QString> Round::copy_the_text_of_card(std::shared_ptr<player::Player> &current_player,
                                              int sum, int type){
        QList<QString> players_with_damage;
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
                    return do_card_effects(executable_card, current_player, sum);
                }
            }

            // kind = 1 - copy text of Delivery card
            else{
                int num_of_delivery = current_player->get_delivery_card_in_spell();
                if (num_of_delivery != -1){
                    std::shared_ptr<card::Card> executable_card = current_player.get()->get_cards()[num_of_delivery];
                    return do_card_effects(executable_card, current_player, sum);
                }
            }
        }

        // type = 2 - card Beardo Blasty's (Source_1.png)
        if (type == 2){
            int delivery_num = current_player->get_delivery_card_in_spell();
            if (delivery_num != -1){
                std::shared_ptr<card::Card> delivery_card = current_player.get()->get_spell()[delivery_num];
                return do_card_effects(delivery_card, current_player, sum);
            }
        }
        return players_with_damage;
    }

    QList<QString> Round::change_spell(std::shared_ptr<player::Player> &current_player,
                                     [[maybe_unused]] int sum, int type){
        QList<QString> players_with_damage;
        int num = get_num_of_player_in_circle(current_player);
        std::shared_ptr<player::Player> strongest_player = current_player;
        int max_lives = 0;
        // type = 1 - card Festering (Quality_6.png)
        if (type == 1){
            for (int i = num + 1; i < count_of_alive_players(); i++){
                int foe_lives = alive_players[i].get()->get_lives();
                if (foe_lives > max_lives){
                    max_lives = foe_lives;
                    strongest_player = alive_players[i];
                }
            }
            if (current_player.get()->get_name() != strongest_player.get()->get_name()){ // we are not last in circle
                int quality_num = strongest_player.get()->get_quality_card_in_spell();
                if (quality_num != -1){
                    strongest_player.get()->delete_card_from_spell(quality_num);
                }
            players_with_damage.append(QString::fromStdString(strongest_player.get()->get_name()));
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
        return players_with_damage;

    }

    QList<QString> Round::change_order(std::shared_ptr<player::Player> &current_player,
                                     [[maybe_unused]]int sum, [[maybe_unused]] int type){
        // card Impatient (Quality_7.png)
        return damage_without_parametrs(current_player, 0, 7);
    }
    QList<QString> Round::do_card_effects(std::shared_ptr<card::Card> &executable_card, std::shared_ptr<player::Player> &current_player, int sum){
        QList<QString> players_with_damage;
        if (executable_card->get_card_component() == card::Card::type_of_spell_component::source) {
            if (executable_card->get_number() == 1) {
                return copy_the_text_of_card(current_player, sum, 2);
            }
            if (executable_card->get_number() == 2) {
                return damage_to_random_foe(current_player, sum, 1);
            }
            if (executable_card->get_number() == 3) {
                return damage_without_parametrs(current_player, 0, 8);
            }
            if (executable_card->get_number() == 4) {
                return damage_without_parametrs(current_player, 0, 1);
            }
            if (executable_card->get_number() == 5) {
                return damage_without_parametrs(current_player, 0, 2);
            }
            if (executable_card->get_number() == 6) {
                return damage_without_parametrs(current_player, sum, 3);
            }
            if (executable_card->get_number() == 8){
                return hp_to_current_player(current_player, sum, 2);
            }
            if (executable_card->get_number() == 9) {
                return damage_for_several_foes(current_player, sum, 5);
            }
            if (executable_card->get_number() == 10) {
                return damage_without_parametrs(current_player, sum, 9);
            }
            if (executable_card->get_number() == 11) {
                return type_of_cards_damage(current_player, sum, 6);
            }
            if (executable_card->get_number() == 12) {
                return damage_without_parametrs(current_player, sum, 4);
            }
            if (executable_card->get_number() == 13) {
                return damage_without_parametrs(current_player, sum, 5);
            }
            if (executable_card->get_number() == 15) {
                return type_of_cards_damage(current_player, sum, 1);
            }

        } else if (executable_card->get_card_component() == card::Card::type_of_spell_component::quality) {
            if (executable_card->get_number() == 1) {
                return damage_without_parametrs(current_player, sum, 6);
            }
            if (executable_card->get_number() == 2) {
                return type_of_cards_damage(current_player, sum, 2);
            }
            if (executable_card->get_number() == 3) {
                return damage_to_random_foe(current_player, sum, 2);
            }
            if (executable_card->get_number() == 4){
                return damage_to_random_foe(current_player, sum, 1);
            }
            if (executable_card->get_number() == 5) {
                return copy_the_text_of_card(current_player, sum, 1);
            }
            if (executable_card->get_number() == 6) {
                return change_spell(current_player, sum, 1);
            }
            if (executable_card->get_number() == 7) {
                return change_order(current_player, sum, 0);
            }
            if (executable_card->get_number() == 8) {
                return type_of_cards_damage(current_player, sum, 3);
            }
            if (executable_card->get_number() == 9) {
                return type_of_cards_damage(current_player, sum, 4);
            }
            if (executable_card->get_number() == 10) {
                return change_spell(current_player, sum, 2);
            }
            if (executable_card->get_number() == 11) {
                return damage_to_the_right_neighbour(current_player, sum, 3);
            }
            if (executable_card->get_number() == 12) {
                return damage_without_parametrs(current_player, sum, 10);
            }
            if (executable_card->get_number() == 13) {
                return type_of_cards_damage(current_player, sum, 5);
            }

        }
        else /*(type_of_the_spell_component == type_of_spell_component::delivery)*/ {
            if (executable_card->get_number() == 1) {
                return damage_to_the_strongest_player(current_player, sum, 1);
            }
            if (executable_card->get_number() == 2) {
                return damage_to_the_weakest_player(current_player, sum, 0);
            }
            if (executable_card->get_number() == 3) {
                return damage_for_several_foes(current_player, sum, 1);
            }
            if (executable_card->get_number() == 4) {
                return damage_for_several_foes(current_player, sum, 2);
            }
            if (executable_card->get_number() == 5) {
                return damage_to_the_strongest_player(current_player, sum, 2);
            }
            if (executable_card->get_number() == 6) {
                return hp_to_current_player(current_player, sum, 1);
            }
            if (executable_card->get_number() == 7) {
                return damage_to_the_left_neighbour(current_player, sum, 0);
            }
            if (executable_card->get_number() == 8) {
                return damage_for_several_foes(current_player, sum, 3);
            }

            if (executable_card->get_number() == 9) {
                return damage_to_the_right_neighbour(current_player, sum, 1);
            }
            if (executable_card->get_number() == 10) {
                return damage_to_the_strongest_player(current_player, sum, 3);
            }
            if (executable_card->get_number() == 11) {
                return damage_for_several_foes(current_player, sum, 6);
            }
            if (executable_card->get_number() == 12) {
                return damage_for_several_foes(current_player, sum, 4);
            }
            if (executable_card->get_number() == 13) {
                return damage_to_the_right_neighbour(current_player, sum, 2);
            }
            if (executable_card->get_number() == 14) {
                return damage_to_the_strongest_player(current_player, sum, 4);
            }
        }
        return players_with_damage;
    }
}
