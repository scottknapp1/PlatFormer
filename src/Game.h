
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "GameObjects/Platform.h"
#include "GameObjects/Player.h"
#include "GameStates/GameOverMenu.h"
#include "GameStates/GamePlay.h"
#include "GameStates/GameState.h"
#include "GameStates/GameWon.h"
#include "GameStates/MainMenu.h"
#include "GameStates/OptionMenu.h"

#include <SFML/Graphics.hpp>

class Game
{
 public:
  explicit Game(sf::RenderWindow& window);
  ~Game();
  static bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);

 private:
  sf::RenderWindow& window;
  GameState current_state = GameState::GAME_MENU;

  MainMenu* main_menu;
  GamePlay* game_play;
  GameOverMenu* game_over_menu;
  GameWon* game_won;
  OptionMenu* option_menu;
};

#endif // PLATFORMER_GAME_H
