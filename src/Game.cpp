
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(nullptr));

  main_menu      = new MainMenu(window);
  game_play      = new GamePlay(window);
  game_over_menu = new GameOverMenu(window);
  game_won       = new GameWon(window);
  option_menu    = new OptionMenu(window);
}
Game::~Game()
{
  delete main_menu;
  delete game_play;
  delete game_over_menu;
  delete game_won;
  delete option_menu;
}
bool Game::init()
{
  return true;
}
void Game::update(float dt)
{
  switch (current_state)
  {
    case GameState::GAME_MENU:
      main_menu->update();
      break;
    case GameState::GAME_PLAY:
      game_play->update(dt, current_state);
      break;
    case GameState::GAME_OVER:
      game_over_menu->update();
      break;
    case GameState::GAME_WON:
      game_won->update();
      break;
    case GameState::GAME_OPTION:
      option_menu->update();
      break;
  }
}
void Game::render()
{
  switch (current_state)
  {
    case GameState::GAME_MENU:
      main_menu->render();
      break;
    case GameState::GAME_PLAY:
      game_play->render();
      break;
    case GameState::GAME_OVER:
      game_over_menu->render();
      break;
    case GameState::GAME_WON:
      game_won->render();
      break;
    case GameState::GAME_OPTION:
      option_menu->render();
      break;
  }
}

void Game::keyPressed(sf::Event event)
{
  switch (current_state)
  {
    case GameState::GAME_MENU:
      main_menu->keyHandler(event, current_state);
      break;
    case GameState::GAME_PLAY:
      game_play->keyHandler(event, current_state);
      break;
    case GameState::GAME_OVER:
      game_over_menu->keyHandler(event, current_state);
      break;
    case GameState::GAME_WON:
      game_won->keyHandler(event, current_state);
      break;
    case GameState::GAME_OPTION:
      option_menu->keyHandler(event, current_state);
      break;
  }
}
