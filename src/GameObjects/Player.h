#pragma once
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <iostream>

#include "../GameStates/GameState.h"
#include "AnimationState.h"
#include "Platform.h"

class Player
{
 private:
  sf::Sprite player;
  sf::Texture player_texture;
  sf::IntRect player_texture_rectangle;
  sf::Clock clock_animation_texture;
  sf::RenderWindow& window;

  sf::SoundBuffer player_footsteps_buffer;
  sf::Sound player_footsteps;

  const float player_Speed  = 100.0f;
  const float gravity_speed = 10.0f;

  float x              = 0;
  float y              = 0;
  float jump_timer     = 1;
  float velocity       = 0;
  float jump_force     = 12;
  float footstep_timer = 0;

  bool landed = true;
  bool jump   = false;

  int jumping = 0;

  AnimationState current_animation = AnimationState::IDLE;

 public:
  Player(sf::RenderWindow& game_window, float startX, float startY);
  ~Player() = default;

  sf::Vector2f getPosition();
  void setPosition(float x, float y);
  void update(float dt);
  void render();
  void playerMovement(float dt);
  void resetMovement();
  bool CollisionPlayerAdvanced(Platform&);
  bool CollisionPlayer(Platform&);
  void keyPressed(sf::Event event);
  void setGravity(bool grav);
  void keyReleased(sf::Event event);
  sf::FloatRect getGlobalBounds();

  void playerAnimator(
    float update_animation, AnimationState& current,
    sf::IntRect& player_texture_rectangle, int max_size, int sprite_size);
};
