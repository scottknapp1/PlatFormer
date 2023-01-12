#pragma once
#include "Player.h"
#include "Score.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Coin
{
 private:
  sf::Sprite coin;
  sf::Texture coin_texture;
  sf::RenderWindow& window;

  sf::SoundBuffer coin_pick_buffer;
  sf::Sound coin_pickup;

  int coins_collected   = 0;
  bool visibility       = true;
  int coin_bounce_timer = 0;

 public:
  explicit Coin(sf::RenderWindow& game_window);
  ~Coin() = default;

  void render();
  void update();
  void prepare_coin(float x, float y);
  void scoreCollision(Player&, Score&);
  bool getVisibility() const;
  void setVisibility(bool set);
  void movement();
  static sf::FloatRect getGlobalBounds();
};