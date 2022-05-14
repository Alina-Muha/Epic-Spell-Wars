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
    Card::type Card::get_type_of_the_card() {
        return type_of_the_card;
    }
    Card::type_of_spell_component Card::get_type_of_spell_component() {
        return type_of_the_spell_component;
    }
}

