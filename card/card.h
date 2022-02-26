#ifndef EPIC_SPELL_WARS_CARD_H
#define EPIC_SPELL_WARS_CARD_H
#include <vector>
#include <functional>

class card{
private:
    enum class type{ahcane, dark, elemental, illusion, primal};
    enum class type_of_spell_component{source, quality, delivery};
    int priority_of_the_turn=0;
    std::vector<std::function<void(int)>> effects;
    //card_image = ...
};


#endif //EPIC_SPELL_WARS_CARD_H
