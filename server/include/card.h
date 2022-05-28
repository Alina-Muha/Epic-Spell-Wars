#ifndef CARD_H
#define CARD_H
#include <vector>
#include <functional>
#include <string>
namespace card {

    class Card {
    public:
        enum class type_of_spell_component {
            source, quality, delivery
        };
        enum class type {
            ahcane, dark, elemental, illusion, primal
        }; // I need to access the fields


    private:

        int number;
        type type_of_the_card;
        type_of_spell_component type_of_the_spell_component;
        int priority_of_the_turn = 0;
        //std::vector<std::function<void(int)>> effects;
        std::string card_image;


    public:
        type get_card_type();
        type_of_spell_component get_card_component();
        int get_number();
        Card(int number_, type type_, type_of_spell_component type_of_spell_component_, int priority_of_the_turn_new,
                /*std::vector<std::function<void(int)>>& effects_,*/ const std::string& card_image_): number(number_), type_of_the_card(type_),

                                                                                                      type_of_the_spell_component(type_of_spell_component_), priority_of_the_turn(priority_of_the_turn_new), /*effects(effects_),*/
                                                                                                      card_image(card_image_){}

        int get_priority_of_the_turn();
        type get_type_of_the_card();
        type_of_spell_component get_type_of_the_spell_component();
        std::string get_card_image();
        //std::vector<std::function<void(int)>> get_effects();


    };
}

#endif
