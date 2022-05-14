#include "round.h"
#include "algorithm"
namespace round{

    bool compare_two_players(player::Player* a,player::Player* b){
        if(a->get_cards().size()<b->get_cards().size()){
            return true;
        }
        if(a->get_cards().size()>b->get_cards().size()){
            return false;
        }
        int priority_of_the_turn_a=0;
        int priority_of_the_turn_b=0;
        for(auto i : a->spell){
            priority_of_the_turn_a=std::max(i.first.get_priority_of_the_turn(), priority_of_the_turn_a);
            priority_of_the_turn_b=std::max(i.first.get_priority_of_the_turn(), priority_of_the_turn_b);
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

    void Round::play_cards(player::Player* gamer){
        for(auto i : gamer->spell){
            i.first.do_card_effects(i.second);
        }
        gamer->spell.clear();
    }

    void Round::play_circle() {
        for(auto it = alive_players.begin(); it!=alive_players.end();it++){
            auto b = *it;
            if(b->get_lives()<=0){
                alive_players.erase(it);
                b->spell.clear();
                continue;
            }
            Round::play_cards(b);
        }
    }

    player::Player* Round::play_round() {
        while(alive_players.size()!=1) {
            //тут как то еще надо подождать чтобы все живые свои заклинания скинули
            sort_priority_of_the_turn();
            play_circle();
        }
        if(alive_players.size()==1){
            return alive_players.back();
        }else{
            return nullptr;
        }
    }
    std::vector<player::Player *> Round::get_alive_players(){
        return alive_players;
    }
    std::vector<card::Card *> round::Round::get_main_deck(){
        return main_deck;
    }
    void Round::load_players(std::vector<player::Player *>& players){
        alive_players=players;
    }
    void Round::load_cards(std::vector<card::Card *> new_deck) {
        main_deck=new_deck;
    }
}
