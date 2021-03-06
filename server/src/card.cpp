#include "card.h"
#include "player.h"
namespace card {

Card::type Card::get_card_type() { return type_of_the_card; }
Card::type_of_spell_component Card::get_card_component() {
  return type_of_the_spell_component;
}

int Card::get_priority_of_the_turn() { return priority_of_the_turn; }

Card::type Card::get_type_of_the_card() { return type_of_the_card; }

Card::type_of_spell_component Card::get_type_of_the_spell_component() {
  return type_of_the_spell_component;
}

int Card::get_number() { return number; }
std::string Card::convert_type_in_string(type_of_spell_component type_of_card) {
  if (type_of_card == type_of_spell_component::delivery) {
    return "Delivery";
  }
  if (type_of_card == type_of_spell_component::quality) {
    return "Quality";
  }
  if (type_of_card == type_of_spell_component::source) {
    return "Source";
  }
}
Card::type_of_spell_component
Card::convert_string_it_type(const std::string &type_of_card) {
  if (type_of_card == "Delivery") {
    return type_of_spell_component::delivery;
  }
  if (type_of_card == "Quality") {
    return type_of_spell_component::quality;
  }
  if (type_of_card == "Source") {
    return type_of_spell_component::source;
  }
}
bool Card::check_roll_power() {
  if (type_of_the_spell_component == type_of_spell_component::delivery) {
    if (number == 1) {
      return true;
    }
    if (number == 2) {
      return true;
    }
    if (number == 3) {
      return true;
    }
    if (number == 4) {
      return true;
    }
    if (number == 5) {
      return true;
    }
    if (number == 6) {
      return true;
    }
    if (number == 7) {
      return true;
    }
    if (number == 8) {
      return true;
    }
    if (number == 9) {
      return true;
    }
    if (number == 10) {
      return true;
    }
    if (number == 11) {
      return true;
    }
    if (number == 12) {
      return true;
    }
    if (number == 13) {
      return true;
    }
    if (number == 14) {
      return true;
    }
  }
  if (type_of_the_spell_component == type_of_spell_component::quality) {
    if (number == 3) {
      return true;
    }
    if (number == 11) {
      return true;
    }
    if (number == 12) {
      return true;
    }
  }
}
} // namespace card
