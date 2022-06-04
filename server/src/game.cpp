#include "game.h"
#include <random>
#include <algorithm>

namespace game{

    void Game::reload_deck(){
        std::random_device rd;
        auto rng = std::default_random_engine {rd()};
        std::shuffle(deck.begin(), deck.end(), rng);
        round.load_cards(deck);
    }

    bool Game::increase_players_wins(std::shared_ptr<player::Player> winner_of_the_round){
        if(winner_of_the_round==nullptr){
            return false;
        }
        for(auto i : players){
            if(i->get_name()==winner_of_the_round->get_name()){
                //i->wins++;
//                if(i->wins==2){
//                    return true;
//                }else{
//                    return false;
//                }
            }
        }
    }

    void Game::play_game() {

            round.load_players(Game::players);
            reload_deck();
            round.distribute_cards();
    }
   std::shared_ptr<player::Player> Game::find_player(const std::string & name){
        for(auto i : players){
            if(i->get_name()==name){
                return i;
            }
        }
        return nullptr;
    }

   round_of_game::Round& Game::get_round() {
       return round;
   }

   void Game::add_player(std::shared_ptr<player::Player> gamer){
       players.push_back(gamer);
   }

   void Game::set_send_logs_func(std::function<void(QString, QList<QString>, int, QString, int number_)> func) {
       round.send_logs_func = func;
   }

}
