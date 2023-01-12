#pragma once

#include "GameState.h"
#include <SFML/Audio/Music.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>

class MainMenu
{
 private:
  sf::Text menu_text;
  sf::Text play_option;
  sf::Text quit_option;
  sf::Sprite background_menu;
  sf::Texture background_texture_menu;
  sf::RenderWindow& window;
  sf::Font font;
  sf::Music game_music;

  // constants for menu state selection
  int play_selected = 1;
  int play          = 1;
  int quit          = 2;

 public:
  explicit MainMenu(sf::RenderWindow& window);
  ~MainMenu() = default;
  void init();
  void update();
  void render();
  void keyHandler(sf::Event event, GameState& current_state);
};
