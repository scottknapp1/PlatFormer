#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameOverMenu
{
 private:
  sf::Text game_over_menu_text;
  sf::Text return_Game_Menu;
  sf::Text quit_option;
  sf::Sprite background_Game_over_menu;
  sf::Texture background_texture_Game_over_menu;
  sf::RenderWindow& window;
  sf::Font font;

  // constants for menu state selection
  int play_selected  = 1;
  int return_to_menu = 1;
  int quit           = 2;

 public:
  explicit GameOverMenu(sf::RenderWindow& window);
  ~GameOverMenu() = default;
  void init();
  void update();
  void render();
  void keyHandler(sf::Event event, GameState& current_state);
};