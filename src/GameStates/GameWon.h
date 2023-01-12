#pragma once

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class GameWon
{
 private:
  sf::Text game_Won_text;
  sf::Text return_Game_Menu;
  sf::Text quit_option;
  sf::Sprite background_Game_Won;
  sf::Texture background_texture_Game_Won;
  sf::RenderWindow& window;
  sf::Font font;

  // constants for menu state selection
  int play_selected_won  = 1;
  int return_to_menu_won = 1;
  int quit_won           = 2;

 public:
  explicit GameWon(sf::RenderWindow& window);
  ~GameWon() = default;
  void init();
  void update();
  void render();
  void keyHandler(sf::Event event, GameState& current_state);
};