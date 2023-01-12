#pragma once

#include "GameState.h"
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>

class OptionMenu
{
 private:
  sf::Text option_menu_text;
  sf::Text option_play_option;
  sf::Text option_quit_option;
  sf::Sprite option_background_menu;
  sf::Texture option_background_texture_menu;
  sf::RenderWindow& window;
  sf::Font font;

  // constants for menu state selection
  int option_play_selected = 1;
  int option_play          = 1;
  int option_quit          = 2;

 public:
  explicit OptionMenu(sf::RenderWindow& window);
  ~OptionMenu() = default;
  void init();
  void update();
  void render();
  void keyHandler(sf::Event event, GameState& current_state);
};