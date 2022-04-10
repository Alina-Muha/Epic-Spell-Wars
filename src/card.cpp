//
// Created by Nikita on 26.02.2022.
//

#include "../include/card.h"
namespace card{

    void Card::do_card_effects(int number_on_the_dice){
        for(auto i : effects){
            i(number_on_the_dice);
        }
    }

    int Card::get_priority_of_the_turn(){
        return priority_of_the_turn;
    }
}

