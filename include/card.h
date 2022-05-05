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

        type type_of_the_card;



        type_of_spell_component type_of_the_spell_component;
        int priority_of_the_turn = 0;
        std::vector<std::function<void(int)>> effects;
        std::string card_image;


    public:
        type get_card_type();
        type_of_spell_component get_card_component();

        Card(type type_, type_of_spell_component type_of_spell_component_, int priority_of_the_turn_new,
             std::vector<std::function<void(int)>>& effects_, const std::string& card_image_): type_of_the_card(type_),
             type_of_the_spell_component(type_of_spell_component_), priority_of_the_turn(priority_of_the_turn_new), effects(effects_),
             card_image(card_image_){}

        void do_card_effects(int number_on_the_dice);

        int get_priority_of_the_turn();


    };
}

#endif
