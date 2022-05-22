#include "card.h"
#include "cards_functions.h"
namespace card{
Card::type Card::get_card_type(){
    return type_of_the_card;
}
Card::type_of_spell_component Card::get_card_component(){
    return type_of_the_spell_component;
}


    int Card::get_priority_of_the_turn(){
        return priority_of_the_turn;
    }

    Card::type Card::get_type_of_the_card(){
        return type_of_the_card;
    }

    Card::type_of_spell_component Card::get_type_of_the_spell_component(){
        return type_of_the_spell_component;
    }

    std::string Card::get_card_image() {
        return card_image;
    }

    /*std::vector<std::function<void(int)>> Card::get_effects(){
        return effects;
    }*/

    void Card::do_card_effects(int number_on_the_dice){
        /*for(auto i : effects){
            i(number_on_the_dice);
        }*/
        card_functions::CardFunctions card_function;

        if (type_of_the_spell_component == type_of_spell_component::source) {
            if (number == 1) {
                card_function.copy_the_text_of_card(2, *current_player);
            }
            if (number == 2) {
                card_function.interaction_with_the_deck(1, *current_player);
            }
            if (number == 3) {
                card_function.rolling_the_dice(2, sum_1, *current_player, points_of_foes, int sum_2);
            }
            if (number == 4) {
                card_function.damage_without_parametrs(1, *current_player, chosen);
            }
            if (number == 5) {
                card_function.damage_without_parametrs(2, *current_player, chosen);
            }
            if (number == 6) {
                card_function.damage_without_parametrs(3, *current_player, chosen);
            }
            if (number == 7) {
                card_function.change_order(2, *current_player);
            }
            if (number == 8) {
                card_function.rolling_the_dice(3, sum_1, *current_player, points_of_foes, sum_2);
            }
            if (number == 9) {
                card_function.change_spell(3, *current_player);
            }
            if (number == 10) {
                card_function.interaction_with_the_deck(2, *current_player);
            }
            if (number == 11) {
                card_function.type_of_cards_damage(6, *current_player);
            }
            if (number == 12) {
                card_function.damage_without_parametrs(4, *current_player, chosen);
            }
            if (number == 13) {
                card_function.damage_without_parametrs(5, *current_player, chosen);
            }
            if (number == 14) {
                card_function.rolling_the_dice(4, sum_1, *current_player, points_of_foes, sum_2);
            }
            if (number == 15) {
                card_function.type_of_cards_damage(1, *current_player);
            }

        } else if (type_of_the_spell_component == type_of_spell_component::quality) {
            if (number == 1) {
                card_function.damage_without_parametrs(6, *current_player, chosen);
            }
            if (number == 2) {
                card_function.type_of_cards_damage(2, *current_player)
            }
            if (number == 3) {
                card_function.damage_to_chosen_foe(1, int sum, *current_player, *chosen_foe, *card);
            }
            if (number == 4) {
                card_function.rolling_the_dice(1, sum_1, *current_player, points_of_foes, sum_2);
            }
            if (number == 5) {
                //TODO
            }
            if (number == 6) {
                card_function.change_spell(1, *current_player);
            }
            if (number == 7) {
                card_function.change_order(1, *current_player);
            }
            if (number == 8) {
                card_function.type_of_cards_damage(3, *current_player);
            }
            if (number == 9) {
                card_function.type_of_cards_damage(4, *current_player);
            }
            if (number == 10) {
                card_function.change_spell(2, *current_player);
            }
            if (number == 11) {
                card_function.damage_to_the_right_neighbour(3, sum, *current_player);
            }
            if (number == 12) {
                card_function.damage_to_chosen_foe(2, sum, *current_player, *chosen_foe, *card);
            }
            if (number == 13) {
                card_function.type_of_cards_damage(5, *current_player);
            }

        } else /*(type_of_the_spell_component == type_of_spell_component::delivery)*/ {
            if (number == 1) {
                card_function.damage_to_the_strongest_player(1, sum, *current_player);
            }
            if (number == 2) {
                card_function.damage_to_the_weakest_player(sum);
            }
            if (number == 3) {
                card_function.damage_for_several_foes(1, sum, *current_player);
            }
            if (number == 4) {
                card_function.damage_for_several_foes(2, sum, *current_player);
            }
            if (number == 5) {
                card_function.damage_to_the_strongest_player(2, sum, *current_player);
            }
            if (number == 6) {
                card_function.hp_to_current_player(6, *current_player);
            }
            if (number == 7) {
                card_function.damage_to_the_left_neighbour(sum, *current_player);
            }
            if (number == 8) {
                card_function.damage_for_several_foes(3, sum, *current_player);
            }
            if (number == 9) {
                card_function.damage_to_the_right_neighbour(1, sum, *current_player);
            }
            if (number == 10) {
                card_function.damage_to_the_strongest_player(3, sum, *current_player);
            }
            if (number == 11) {
                card_function.damage_to_chosen_foe(3, sum, *current_player, *chosen_foe, *card);
            }
            if (number == 12) {
                card_function.damage_for_several_foes(4, sum, *current_player);
            }
            if (number == 13) {
                card_function.damage_to_the_right_neighbour(2, sum, *current_player);
            }
            if (number == 14) {
                card_function.damage_to_the_strongest_player(4, sum, *current_player);
            }
        }
    }

}
