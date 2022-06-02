
#include "round.h"
#include "algorithm"
#include <QDebug>

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
            //do_card_effects(i.first);
        }
        gamer->get_spell().clear();
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
}
