#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Score
{
 private:
  int playerScore = 0;

  std::string player;
  sf::Text ScoreTextPlayer;
  sf::RenderWindow& window;
  sf::Font font;

 public:
  explicit Score(sf::RenderWindow& game_window);
  ~Score() = default;
  void update();
  void render();
  void init();
  int getScorePlayer() const;
  void scoreUpdate(bool);
  void resetScore();
  void setPosition();
};