#include "game.h"

namespace game {

void Game::reload_deck() {
  std::random_device rd;
  auto rng = std::default_random_engine{rd()};
  std::shuffle(deck.begin(), deck.end(), rng);
  round.load_cards(deck);
}

void Game::play_game() {

  round.load_players(Game::players);

  if (round.get_main_deck().size() < 3 * round.get_players().size()) {
    reload_deck();
  }
  round.distribute_cards();
}
std::shared_ptr<player::Player> Game::find_player(const std::string &name) {
  for (auto i : players) {
    if (i->get_name() == name) {
      return i;
    }
  }
  return nullptr;
}

round_of_game::Round &Game::get_round() { return round; }

void Game::add_player(std::shared_ptr<player::Player> gamer) {
  players.push_back(gamer);
}

void Game::set_send_logs_func(
    std::function<void(QString, QList<QString>, int, QString, int number_)>
        func) {
  round.send_logs_func = func;
}

} // namespace game
