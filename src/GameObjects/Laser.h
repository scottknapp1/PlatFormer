#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Enemy.h"
#include "Platform.h"

class Laser
{
 private:
  sf::Sprite laser;
  sf::Texture laser_texture;
  sf::RenderWindow& window;

  sf::SoundBuffer shoot_buffer;
  sf::Sound shoot;

  const float laserSpeed = 100.0f;
  bool visibility        = false;
  bool fire_forward      = true;

 public:
  explicit Laser(sf::RenderWindow& game_window);
  ~Laser() = default;

  void render();
  void update(float dt);
  void scoreCollision(Enemy&);
  bool getVisibility() const;
  void setVisibility(bool set);
  static sf::FloatRect getGlobalBounds();
  void setPosition(float x, float y);
  void getDirection(bool set);
};