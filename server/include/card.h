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


    public:
        type get_card_type();
        type_of_spell_component get_card_component();
        int get_number();
        Card(int number_, type type_, type_of_spell_component type_of_spell_component_, int priority_of_the_turn_new): number(number_), type_of_the_card(type_),

                                                                                                      type_of_the_spell_component(type_of_spell_component_), priority_of_the_turn(priority_of_the_turn_new) /*effects(effects_),*/
                                                                                                  {}
        Card(int number_, type_of_spell_component type_of_spell_component_):number(number_), type_of_the_spell_component(type_of_spell_component_){
            if(type_of_the_spell_component==type_of_spell_component::source){
                priority_of_the_turn=0;
                if(number==1){
                     type_of_the_card=type::ahcane;
                }
                if(number==2){
                     type_of_the_card=type::ahcane;
                }
                if(number==3){
                     type_of_the_card=type::primal;
                }
                if(number==4){
                     type_of_the_card=type::primal;
                }
                if(number==5){
                     type_of_the_card=type::elemental;
                }
                if(number==6){
                     type_of_the_card=type::dark;
                }
                if(number==7){
                    type_of_the_card=type::primal;
                }
                if(number==8){
                    type_of_the_card=type::dark;
                }
                if(number==9){
                    type_of_the_card=type::illusion;
                }
                if(number==10){
                    type_of_the_card=type::illusion;
                }
                if(number==11){
                    type_of_the_card=type::primal;
                }
                if(number==12){
                    type_of_the_card=type::elemental;
                }
                if(number==13){
                    type_of_the_card=type::elemental;
                }
                if(number==14){
                    type_of_the_card=type::illusion;
                }
                if(number==15){
                    type_of_the_card=type::elemental;
                }
            }
            if(type_of_the_spell_component==type_of_spell_component::quality){
                priority_of_the_turn=0;
                if(number==1){
                     type_of_the_card=type::primal;
                }
                if(number==2){
                    type_of_the_card=type::elemental;
                }
                if(number==3){
                     type_of_the_card=type::dark;
                }
                if(number==4){
                    type_of_the_card=type::elemental;
                }
                if(number==5){
                     type_of_the_card=type::illusion;
                }
                if(number==6){
                    type_of_the_card=type::dark;
                }
                if(number==7){
                    type_of_the_card=type::ahcane;
                }
                if(number==8){
                    type_of_the_card=type::elemental;
                }
                if(number==9){
                    type_of_the_card=type::dark;
                }
                if(number==10){
                    type_of_the_card=type::primal;
                }
                if(number==11){
                    type_of_the_card=type::primal;
                }
                if(number==12){
                    type_of_the_card=type::dark;
                }
                if(number==13){
                    type_of_the_card=type::primal;
                }

            }
            if(type_of_the_spell_component==type_of_spell_component::delivery){
                if(number==1){
                    type_of_the_card=type::elemental;
                    priority_of_the_turn=10;
                }
                if(number==2){
                    type_of_the_card=type::dark;
                    priority_of_the_turn=5;
                }
                if(number==3){
                    type_of_the_card=type::elemental;
                    priority_of_the_turn=20;
                }
                if(number==4){
                    type_of_the_card=type::elemental;
                    priority_of_the_turn=9;
                }
                if(number==5){
                    type_of_the_card=type::primal;
                    priority_of_the_turn=2;
                }
                if(number==6){
                    type_of_the_card=type::primal;
                    priority_of_the_turn=12;
                }
                if(number==7){
                    type_of_the_card=type::primal;
                    priority_of_the_turn=14;
                }
                if(number==8){
                    type_of_the_card=type::dark;
                    priority_of_the_turn=11;
                }
                if(number==9){
                    type_of_the_card=type::dark;
                    priority_of_the_turn=8;
                }
                if(number==10){
                    type_of_the_card=type::elemental;
                    priority_of_the_turn=3;
                }
                if(number==11){
                    type_of_the_card=type::illusion;
                    priority_of_the_turn=19;
                }
                if(number==12){
                    type_of_the_card=type::primal;
                    priority_of_the_turn=1;
                }
                if(number==13){
                    type_of_the_card=type::illusion;
                    priority_of_the_turn=17;
                }
                if(number==14){
                    type_of_the_card=type::dark;
                    priority_of_the_turn=18;
                }
            }
        }
        int get_priority_of_the_turn();
        type get_type_of_the_card();
        type_of_spell_component get_type_of_the_spell_component();
        std::string get_card_image();
        //std::vector<std::function<void(int)>> get_effects();
        bool check_roll_power();
        std::string convert_type_in_string(type_of_spell_component type_of_card);
        static type_of_spell_component convert_string_it_type(const std::string& type_of_card);
    };
}

#endif
