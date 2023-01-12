#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Life
{
 private:
  int player_life = 0;

  std::string player_life_Text;
  sf::Text life_text_player;
  sf::RenderWindow& window;
  sf::Font font;

 public:
  explicit Life(sf::RenderWindow& window);
  ~Life() = default;

  void update();
  void render();
  void init();
  int getLifePlayer() const;
  void lifeUpdate(bool);
  void resetLife();
  void setPosition();
};