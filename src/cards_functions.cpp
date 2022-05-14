#include <iostream>
#include <vector>
#include <map>
#include "cards_functions.h"
namespace card_functions{
int CardFunctions::get_num_of_player_in_circle(player::Player *current_player){
    int num = 0; // the number of the player in the circle
    for (auto player : round.get_players()){
        if (player == current_player){
            break;
        }
        num++;
    }
    return num;
}
player::Player* CardFunctions::get_the_strongest_player(){
    int life = 0;
    player::Player *strongest_player = nullptr;
    for (auto player : round.get_players()){
        if (player->get_lives() > life){
            strongest_player = player;
        }
    }
    return strongest_player;
}
void CardFunctions::damage_to_the_strongest_player(int type, int sum, player::Player *current_player){
    player::Player* strongest_player = get_the_strongest_player();
    int num = get_num_of_player_in_circle(strongest_player);
    int cur_lives = strongest_player->get_lives(); // maybe need getter??
    int count = round.get_players().size();
    player::Player* right_neighbour = round.get_players()[(num + 1) % count];
    player::Player* left_neighbour = round.get_players()[(count + num - 1) % count];
    //type = 1 - card Nuke-U-Lur Meltdown (Delivery)
    if (type == 1){
        if (sum >= 1 && sum <= 4){
           strongest_player->change_lives(cur_lives - 1);
        }
        else{
            int lives_of_left = left_neighbour->get_lives();
            int lives_of_right = right_neighbour->get_lives();
            left_neighbour->change_lives(lives_of_left - 1);
            right_neighbour->change_lives(lives_of_right - 1);
            if (sum >= 5 && sum <= 9){
                strongest_player->change_lives(cur_lives - 3);
            }
            if (sum >= 10){
                strongest_player->change_lives(cur_lives - 5);
            }
        }
    }
    // type = 2 - card Gore-Nado (Delivery)
    if (type == 2){
        if (sum >= 1 && sum <= 4){
            strongest_player->change_lives(cur_lives - 2);
        }
        if (sum >= 5 && sum <= 9){
            strongest_player->change_lives(cur_lives - 3);
        }
        if (sum >= 10){
            strongest_player->change_lives(cur_lives - 6);
        }
    }
    // type = 3 - card Chicken (Delivery)
    if (type == 3){
        if (sum < 10){
            strongest_player->change_lives(cur_lives - 1);
        }
        else{
            strongest_player->change_lives(cur_lives - 7);
        }
    }
    // type = 4 - card Pact With Devil (Delivery)
    if (type == 4){
        if (sum >= 1 && sum <= 4){
            strongest_player->change_lives(cur_lives - 1);
        }
        else{
            strongest_player->change_lives(cur_lives - 2);
            if (sum >= 10){
                card::Card *delivery_card = nullptr;
                int i = 0;
                int num = 0;
                for (auto card: strongest_player->get_spell()){
                    i++;
                    if (card.first->get_card_component() == card::Card::type_of_spell_component::delivery){
                        delivery_card = card.first;
                        num = i;
                        break;
                    }
                }
                strongest_player->get_spell().erase(strongest_player->get_spell().begin() + num);
                //current_player->spell.emplace_back(delivery_card);  //what happens with int? what happens with current spell??
            }
        }
    }
}
void CardFunctions::damage_to_the_weakest_player(int sum){
    // card Mercy Killing (Delivery)
    int life = 0;
    player::Player* weakest_player = nullptr;
    for (auto player : round.get_players()){
        if (player->get_lives() > life){
            life = player->get_lives();
            weakest_player = player;
        }
    }
    int cur_lives = weakest_player->get_lives();
    if (sum >= 1 && sum <= 4){
        weakest_player->change_lives(cur_lives - 2);
    }
    if (sum >= 5 && sum <= 9){
        weakest_player->change_lives(cur_lives - 3);
    }
    if (sum >= 10){
        weakest_player->change_lives(cur_lives - 4);
    }
}
void CardFunctions::damage_to_the_left_neighbour(int sum, player::Player *current_player){
    // card Fist O'Nature (Delivery)
    int num = get_num_of_player_in_circle(current_player);
    int count = round.get_players().size();
    player::Player *left_neighbour = round.get_players()[(count + num - 1) % count];
    int lives_of_left = left_neighbour->get_lives();
    if (sum >= 1 && sum <= 4){
        left_neighbour->change_lives(lives_of_left - 1);
    }
    if (sum >= 5 && sum <= 9){
        left_neighbour->change_lives(lives_of_left - 2);
    }
    if (sum >= 10){
        left_neighbour->change_lives(lives_of_left - 4);
    }
};
void CardFunctions::damage_to_the_right_neighbour(int type, int sum, player::Player *current_player){
    int num = get_num_of_player_in_circle(current_player);
    int count = round.get_players().size();
    player::Player *right_neighbour = round.get_players()[num + 1 % count];
    int cur_lives = current_player->get_lives();
    int lives_of_right = right_neighbour->get_lives();
    // type = 1 - card Death-Wish (Delivery)
    if (type == 1){
        current_player->change_lives(cur_lives - 1);
        if (sum >= 1 && sum <= 4){
            right_neighbour->change_lives(lives_of_right - 2);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour->change_lives(lives_of_right - 3);
        }
        if (sum >= 10){
            right_neighbour->change_lives(lives_of_right - 5);
        }
    }
    // type = 2 - card Phantasmagoons (Delivery)
    if (type == 2){
        if (sum >= 1 && sum <= 4){
            right_neighbour->change_lives(lives_of_right - 1);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour->change_lives(lives_of_right - 3);
        }
        if (sum >= 10){
            right_neighbour->change_lives(lives_of_right - 4);
        }
    }
    // type = 3 - card Prickly (Quality)
    if (type == 3){
        if (sum >= 1 && sum <= 4){
            right_neighbour->change_lives(lives_of_right - 1);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour->change_lives(lives_of_right - 1);
            current_player -> change_lives(cur_lives + 1);
        }
        if (sum >= 10){
            right_neighbour->change_lives(lives_of_right - 3);
            current_player -> change_lives(cur_lives + 3);
        }
    }
}
// for this void it needs to to understand how to get information about the chosen foe, we need client-server
void CardFunctions::damage_to_chosen_foe(int type, int sum, player::Player *current_player, player::Player *chosen_foe, card::Card *card){
    int cur_lives = current_player->get_lives();
    int foe_lives = chosen_foe->get_lives();
   // type = 1 - card Deulicious (Quality)
    if (type == 1){
        if (sum >= 1 && sum <= 4){
            chosen_foe->change_lives(foe_lives - 2);
        }
        if (sum >= 5 && sum <= 9){
            chosen_foe->change_lives(foe_lives - 4);
            current_player->change_lives(cur_lives - 1);
        }
        if (sum >= 10){
            chosen_foe->change_lives(foe_lives - 5);
            current_player->change_lives(cur_lives - 2);
        }
    }
    // type = 2 - card Ritualistic (Quality)
    if (type == 2){
        if (sum >= 1 && sum <= 4){
            current_player->change_lives(cur_lives - 3);
        }
        if (sum >= 5 && sum <= 9){
            chosen_foe->change_lives(foe_lives - 3);
        }
        if (sum >= 10){
            chosen_foe->change_lives(foe_lives - 5);
        }
    }
    // type = 3 - card Bedazzlement (Delivery)
    if (type == 3){
        if (sum >= 1 && sum <= 4){
            chosen_foe->change_lives(foe_lives - 1);
        }
        else{
            chosen_foe->change_lives(foe_lives - 1);
            if (sum >= 5 && sum <= 9){
                int count_of_cards = chosen_foe->get_cards().size();
                int num_of_card = rand() % count_of_cards;
                //current_player->spell.emplace_back(current_player->get_cards()[num_of_card]);
            }
            if (sum >= 10){
                //current_player->spell.emplace_back(card); // here it needs to think about how the chosen card will be given, client-server??
            }
        }
    }
}
void CardFunctions::hp_to_current_player(int sum, player::Player *current_player){
    // card Fountain Of Youth
    int cur_lives = current_player->get_lives();
    if (sum >= 5 && sum <= 9){
        current_player->change_lives(cur_lives + 2);
    }
    if (sum >= 10){
        current_player->change_lives(cur_lives + 4);
    }
}
void CardFunctions::damage_for_several_foes(int type, int sum, player::Player *current_player){
    int cur_lives = current_player->get_lives();
    // type = 1 - card Meatier Swarm (Delivery)
    if (type == 1){
        for (auto player : round.get_players()){
            int foe_lives = player->get_lives();
            if (foe_lives > cur_lives){
                if (sum >= 1 && sum <= 4){
                    player->change_lives(foe_lives - 1);
                }
                if (sum >= 5 && sum <= 9){
                    player->change_lives(foe_lives - 3);
                }
                if (sum >= 10){
                    player->change_lives(foe_lives - 4);
                }
            }
        }
    }
    // type = 2 - card Lightning-Bolt (Delivery)
    if (type == 2){
        int num = get_num_of_player_in_circle(current_player);
        int count = round.get_players().size();
        player::Player *left_neighbour = round.get_players()[(count + num - 1) % count];
        player::Player *left_left_neighbour = round.get_players()[(count + num - 2) % count];
        int lives_of_left = left_neighbour->get_lives();
        int lives_of_left_left = left_left_neighbour->get_lives();
        if (sum >= 1 && sum <= 4){
            left_neighbour->change_lives(lives_of_left - 1);
            left_left_neighbour->change_lives(lives_of_left_left - 1);
        }
        if (sum >= 5 && sum <= 9){
            left_neighbour->change_lives(lives_of_left - 2);
            left_left_neighbour->change_lives(lives_of_left_left - 2);
        }
        if (sum >= 10){
            left_neighbour->change_lives(lives_of_left - 4);
            left_left_neighbour->change_lives(lives_of_left_left - 4);
        }
    }
    // type = 3 - card Exorcism (Delivery)
    // here smth strange with Last Wizard Standing token, what is it??
    if (type == 3){
        for (auto player : round.get_players()){
            int foe_lives = player->get_lives();
            if (player != current_player){
                if (sum >= 1 && sum <= 4){
                    player->change_lives(foe_lives - 1);
                }
                if (sum >= 5 && sum <= 9){
                    player->change_lives(foe_lives - 2);
                }
                if (sum >= 10){
                    player->change_lives(foe_lives - 4);
                }
            }
        }
    }
    // type = 4 - card Snakedance (Delivery)
    if (type == 4){
        int num = get_num_of_player_in_circle(current_player);
        int count = round.get_players().size();
        player::Player *right_neighbour = round.get_players()[(num + 1) % count];
        player::Player *left_neighbour = round.get_players()[(count + num - 1) % count];
        int lives_of_right = right_neighbour->get_lives();
        int lives_of_left = left_neighbour->get_lives();
        if (sum >= 1 && sum <= 4){
            right_neighbour->change_lives(lives_of_right - 1);
            left_neighbour->change_lives(lives_of_left - 1);
        }
        if (sum >= 5 && sum <= 9){
            right_neighbour->change_lives(lives_of_right - 2);
            left_neighbour->change_lives(lives_of_left - 2);
        }
        if (sum >= 10){
            int primal = 0;
            for (auto card : current_player->get_spell()){
                if (card.first->get_card_type() == card::Card::type::primal){
                    primal++;
                }
                right_neighbour->change_lives(lives_of_right - 2 * primal);
                left_neighbour->change_lives(lives_of_left - 2 * primal);
            }
        }
    }
}
void CardFunctions::type_of_cards_damage(int type, player::Player *current_player){
    std::map<card::Card::type, int> types_of_spell_cards; // for different types in spell
    types_of_spell_cards[card::Card::type::ahcane] = 0;
    types_of_spell_cards[card::Card::type::dark] = 0;
    types_of_spell_cards[card::Card::type::elemental] = 0;
    types_of_spell_cards[card::Card::type::illusion] = 0;
    types_of_spell_cards[card::Card::type::primal] = 0;
    for (auto &card : current_player->get_spell()){
        types_of_spell_cards[card.first->get_card_type()]++;
    }
    // type = 1 - card Wyrmtor's (Source)
    int unique = 0;
    for (auto el : types_of_spell_cards){
        if (el.second != 0){
            unique++;
        }
    }
    if (type == 1){
        for (auto player : round.get_players()){
            int foe_lives = player->get_lives();
            if (player != current_player){
                player->change_lives(foe_lives - unique);
            }
        }
    }
    // type = 2 - card Delicious (Quality)
    if (type == 2){
        for (auto player : round.get_players()){
            int foe_lives = player->get_lives();
            if (player != current_player && foe_lives % 2 != 0){
                player->change_lives(foe_lives - unique);
            }
        }
    }
    // type = 3 - card Inferno Tastic (Quality)
    if (type == 3){
        int elemental = types_of_spell_cards[card::Card::type::elemental];
        for (auto player : round.get_players()){
            int foe_lives = player->get_lives();
            if (player != current_player){
                player->change_lives(foe_lives - elemental);
            }
        }
    }
    // type = 4 - card  Maggoty (Quality)
    if (type == 4){
        int dark = types_of_spell_cards[card::Card::type::dark];
        player::Player *strongest_player = get_the_strongest_player();
        int foe_lives = strongest_player->get_lives();
        strongest_player->change_lives(foe_lives - 2 * dark);
    }
    // type = 5 - card Thundering (Quality)
    if (type == 5){
        int count = round.get_players().size();
        int num = rand() % count;
        player::Player *random_player = round.get_players()[num];
        int foe_lives = random_player->get_lives();
        random_player->change_lives(foe_lives - 2 * unique);
    }
    // type = 6 - card Rose Bottom's (Source)
    if (type == 6){
        int cur_lives = current_player->get_lives();
        current_player->change_lives(cur_lives + unique);
    }
}
void CardFunctions::damage_without_parametrs(int type, player::Player *current_player, int chosen){
    int count = round.get_players().size();
    player::Player *strongest_player = get_the_strongest_player();
    int foe_lives = strongest_player->get_lives();
    // type = 1 - card King Oberon's(Source)
    if (type == 1){
        int cur_lives = current_player->get_lives();
        current_player->change_lives(cur_lives + 2);
    }
    // type = 2 - card Magma Gog's (Source)
    if (type == 2){
        if (chosen == 1){
            int num = get_num_of_player_in_circle(current_player);
            int count = round.get_players().size();
            player::Player *left_neighbour = round.get_players()[(count + num - 1) % count];
            int lives_of_left = left_neighbour->get_lives();
            left_neighbour->change_lives(lives_of_left - 2);
        }
        else{
            for (auto player : round.get_players()){
                if (player != current_player){
                    int foe_lives = player->get_lives();
                    player->change_lives(foe_lives - 1);
                }
            }
        }
    }
    // type = 3 - card Midnight Merlin's (Source)
    if (type == 3){
        strongest_player->change_lives(foe_lives - count);
    }
    // type = 4 - card Scorchis's (Source)
    if (type == 4){
        strongest_player->change_lives(foe_lives - 3);
    }
    // type = 5 - card Thai-Foon's (Source)
    if (type == 5){
        int num = get_num_of_player_in_circle(current_player);
        for (int i = 0; i < num; i++){
            int foe_lives = round.get_players()[i]->get_lives();
            round.get_players()[i]->change_lives(foe_lives - 3);
        }
    }
    // type = 6 - Boulder Iffic (Quality)
    if (type == 6){
        int players_without_damage = count - 1;
        int i = 1;
        int num = get_num_of_player_in_circle(current_player);
        while (players_without_damage > 0){
            player::Player *left_neghbour = round.get_players()[(count + num - 1) % count];
            int lives_of_left = left_neghbour->get_lives();
            left_neghbour->change_lives(lives_of_left - i);
            i++;
            players_without_damage--;
        }
    }
}
void CardFunctions::rolling_the_dice(int type, int sum_1, player::Player *current_player, std::vector<int> points_of_foes, int sum_2){
    // type = 1 - card Dicey
    // maybe it too hard, we need client-server, now I don't know
    int count = round.get_players().size() - 1;
    if (type == 1){
        int num = get_num_of_player_in_circle(current_player);
        int foes_without_damage = count;
        int i = 1;
        int pos_in_vec = 0;
        while (foes_without_damage > 0){
            player::Player *new_player = round.get_players()[(num + i) % count];
            int new_player_lives = new_player->get_lives();
            if (points_of_foes[pos_in_vec] == sum_1){
                new_player->change_lives(new_player_lives - sum_1);
            }

            else{
                if (points_of_foes[pos_in_vec] == sum_2){
                new_player->change_lives(new_player_lives - sum_1);
                }
                else {
                    if (points_of_foes[pos_in_vec] == sum_2 + sum_1){
                        new_player->change_lives(new_player_lives - sum_1 - sum_2);
                    }
                }
            }
            i++;
            pos_in_vec++;
        }
    }

}
} //card_functions
