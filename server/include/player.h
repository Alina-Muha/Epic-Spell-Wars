#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "card.h"
#include "dice.h"

namespace player {
    class Player {
    private:
        std::string name;
        int lives;


        std::vector<std::shared_ptr<card::Card>> cards;

        std::vector<std::shared_ptr<card::Card>> spell;

    public:

        explicit Player(std::string &name_);

        ~Player() = default;

        void set_name(std::string name_);

        int get_num_of_cards();

        [[nodiscard]] std::string& get_name();

        [[nodiscard]] std::vector<std::shared_ptr<card::Card>> &get_spell();

        [[nodiscard]] int get_lives() const;

        [[nodiscard]] std::vector<std::shared_ptr<card::Card>> &get_cards();

        void add_lives(int lives_to_add);

        void subtract_lives(int lives_to_subtract);

        void change_lives(int new_lives);

        void add_card(std::shared_ptr<card::Card> new_card);

        void select_card(int index);

        void sort_cards_in_spell();

        bool is_move_correct();

        void add_card_to_spell(std::shared_ptr<card::Card> new_card);

        // for card_functions
        int get_achane_num_in_spell();
        int get_dark_num_in_spell();
        int get_illusion_num_in_spell();
        int get_primal_num_in_spell();
        int get_elemental_num_in_spell();

        int unique_types_in_spell ();

        int get_delivery_card_in_spell();
        int get_source_card_in_spell();

        void delete_card_from_spell(int num_of_card);
        void delete_card(int num_of_card);
    };
}  // namespace player
#endif // PLAYER_H
