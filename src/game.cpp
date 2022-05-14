#include "game.h"
#include <random>
#include <algorithm>

namespace game{

    void Game::reload_deck(){
        std::random_device rd;
        auto rng = std::default_random_engine {rd()};
        std::shuffle(deck.begin(), deck.end(), rng);
        round::Round::load_cards(deck);
    }

    bool Game::increase_players_wins(player::Player* winner_of_the_round){
        if(winner_of_the_round==nullptr){
            return false;
        }
        for(auto i : players){
            if(i->get_name()==winner_of_the_round->get_name()){
                i->wins++;
                if(i->wins==2){
                    return true;
                }else{
                    return false;
                }
            }
        }
    }

    void Game::play_game() {
        bool signal_to_stop_game=false;
        while(!signal_to_stop_game) {
            round::Round::load_players(Game::players);
            reload_deck();
            signal_to_stop_game=increase_players_wins(round::Round::play_round());
            //не знаю надо ли как то выводить имя победителя
        }
    }

}