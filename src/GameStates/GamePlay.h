#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "../GameObjects/Coin.h"
#include "../GameObjects/Enemy.h"
#include "../GameObjects/Laser.h"
#include "../GameObjects/Life.h"
#include "../GameObjects/Platform.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Score.h"
#include "../GameObjects/AnimationState.h"

class GamePlay
{
 private:
  static const int height      = 11;
  static const int width       = 40;
  static const int laser_count = 10;
  static const int enemy_count = 4;
  static const int coin_count  = 4;

  int active_laser = 0;

  Platform* platform[height * width]{};
  Laser* laser[laser_count]{};
  Enemy* enemy[enemy_count]{};
  Coin* coin[coin_count]{};

  Player* player;
  Score* score;
  Life* life;

  sf::Sprite background_menu;
  sf::Texture background_texture_gameplay;
  sf::Font font;
  sf::RenderWindow& window;
  sf::View test;

  sf::SoundBuffer player_burn_buffer;
  sf::Sound player_burn;

 public:
  explicit GamePlay(sf::RenderWindow& window);
  ~GamePlay();
  void init();
  void update(float dt, GameState& current_state);
  void render();
  void resetPlayer();
  void keyHandler(sf::Event event, GameState& current_state);
  void keyPressed(sf::Event event);
};