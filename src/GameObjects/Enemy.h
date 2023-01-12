#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../GameStates/GameState.h"
#include "Life.h"
#include "Player.h"

class Enemy
{
 private:
  sf::Sprite sprite;
  sf::Texture sprite_Texture;
  sf::RenderWindow& window;

  sf::SoundBuffer player_collide_enemy_buffer;
  sf::Sound player_collide_enemy;

  sf::IntRect current_frame;
  sf::Clock enemy_clock_animation_texture;

  bool visibility  = true;
  int moving_timer = 0;

 public:
  explicit Enemy(sf::RenderWindow& game_window);
  ~Enemy() = default;

  sf::Vector2f getPosition();
  sf::FloatRect getGlobalBounds();

  void render();
  void update();
  void prepare_Enemy(float x, float y);
  bool getVisibility() const;
  void setVisibility(bool set);

  void enemyMovement();
  void
  PlayerCollision(Player&, GameState& current_state, Life&, sf::View& view);

  void enemyAnimator(
    float update_animation, sf::IntRect& player_texture_rectangle, int max_size,
    int sprite_size);
};