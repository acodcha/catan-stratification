#pragma once

#include "Player.hpp"

namespace CatanLeaderboardGenerator {

class Players {

public:

  Players(const Games& games) noexcept {
    std::set<PlayerName, PlayerName::sort> games_player_names;
    for (const Game& game : games) {
      const std::set<PlayerName, PlayerName::sort> game_player_names{game.player_names()};
      games_player_names.insert(game_player_names.cbegin(), game_player_names.cend());
    }
    uint_least64_t counter{0};
    for (const PlayerName& player_name : games_player_names) {
      data_.insert({player_name, games, color(counter), gnuplot_point_type(counter)});
      ++counter;
    }
    message(print());
  }

  const Player& find(const PlayerName& name) const {
    const std::set<Player, Player::sort>::const_iterator datum{data_.find({name})};
    if (datum != data_.cend()) {
      return *datum;
    } else {
      error(name.value() + " is not a player.");
    }
  }

  std::string print() const noexcept {
    std::stringstream stream;
    stream << "There are " << data_.size() << " players:";
    for (const Player& player : data_) {
      stream << std::endl << "- " << player.name().value();
    }
    stream << std::endl << print(GameCategory::AnyNumberOfPlayers);
    stream << std::endl << print(GameCategory::ThreeToFourPlayers);
    stream << std::endl << print(GameCategory::FiveToSixPlayers);
    stream << std::endl << print(GameCategory::SevenToEightPlayers);
    return stream.str();
  }

  struct const_iterator : public std::set<Player, Player::sort>::const_iterator {
    const_iterator(const std::set<Player, Player::sort>::const_iterator i) noexcept : std::set<Player, Player::sort>::const_iterator(i) {}
  };

  std::size_t size() const noexcept {
    return data_.size();
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(data_.cbegin());
  }

  const_iterator begin() const noexcept {
   return cbegin();
  }

  const_iterator cend() const noexcept {
   return const_iterator(data_.cend());
  }

  const_iterator end() const noexcept {
   return cend();
  }

protected:

  std::set<Player, Player::sort> data_;

  std::string print(const GameCategory game_category) const noexcept {
    std::stringstream stream;
    switch (game_category) {
      case GameCategory::AnyNumberOfPlayers:
        stream << "Results for all games:";
        break;
      case GameCategory::ThreeToFourPlayers:
        stream << "Results for 3-4 player games:";
        break;
      case GameCategory::FiveToSixPlayers:
        stream << "Results for 5-6 player games:";
        break;
      case GameCategory::SevenToEightPlayers:
        stream << "Results for 7-8 player games:";
        break;
    }
    for (const Player& datum : data_) {
      const std::string text{datum.print(game_category)};
      if (!text.empty()) {
        stream << std::endl << "- " << text;
      }
    }
    return stream.str();
  }

};

} // namespace CatanLeaderboardGenerator
