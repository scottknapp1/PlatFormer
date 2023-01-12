#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Platform
{
 private:
  sf::Sprite sprite;
  sf::Texture sprite_Texture;
  bool visibility = true;
  sf::RenderWindow& window;

 public:
  explicit Platform(sf::RenderWindow& game_window);
  ~Platform() = default;
  void render();
  void update();

  void prepare_platform(float x, float y);
  bool getVisibility() const;
  void setVisibility(bool set);
  sf::Vector2f getPosition();
  sf::FloatRect getGlobalBounds();
};