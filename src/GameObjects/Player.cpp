#include "Player.h"

Player::Player(sf::RenderWindow& game_window, float startX, float startY)
  : window(game_window)

{
  if (!player_texture.loadFromFile("Data/Images/player_sprite.png"))
  {
    std::cout << "player texture did not load \n";
  }
  player.setTexture(player_texture);
  player.setPosition(startX, startY);

  // audio for player footsteps
  if (!player_footsteps_buffer.loadFromFile("Data/Sounds/step3.wav"))
  {
    std::cout << "collision audio failed to load \n";
  }
  player_footsteps.setBuffer(player_footsteps_buffer);

  // player animation
  if (current_animation == AnimationState::IDLE)
  {
    player_texture_rectangle = sf::IntRect(0, 0, 49, 40);
    player.setTextureRect(player_texture_rectangle);
  }

  else if (current_animation == AnimationState::JUMPING)
  {
    player_texture_rectangle = sf::IntRect(0, 80, 49, 40);
    player.setTextureRect(player_texture_rectangle);
  }

  else if (current_animation == AnimationState::RUNNING)
  {
    player_texture_rectangle = sf::IntRect(0, 0, 49, 40);
    player.setTextureRect(player_texture_rectangle);
  }
  player.setScale(2, 2);
}
sf::Vector2f Player::getPosition()
{
  return player.getPosition();
}
void Player::setPosition(float _x, float _y)
{
  player.setPosition(_x,_y);
}
void Player::update(float dt)
{
  // jump
  if (jump)
  {
    jumping += 1;
    if (jumping < 60)
    {
      y = -jump_force * player_Speed * dt;
    }
    else
    {
      y = +jump_force * player_Speed * dt;
    }
  }
  // stop jump
  if (jumping >= 60)
  {
    jumping = 0;
    jump    = false;
  }

  footstep_timer += 1.0f * dt;
  jump_timer += 0.7f * dt;
  playerMovement(dt);

  // player animation state
  if (current_animation == AnimationState::RUNNING)
  {
    if (footstep_timer > 1.2f)
    {
      player_footsteps.play();
      footstep_timer = 0;
    }
    playerAnimator(
      0.05f, current_animation, player_texture_rectangle, 1225, 49);
  }
  else if (current_animation == AnimationState::JUMPING)
  {
    playerAnimator(
      1.2f * dt, current_animation, player_texture_rectangle, 980, 49);
  }
  else if (current_animation == AnimationState::IDLE)
  {
    playerAnimator(
      0.3f * dt, current_animation, player_texture_rectangle, 98, 49);
  }
  if (velocity == 0)
  {
    current_animation = AnimationState::IDLE;
  }
  if (!landed)
  {
    current_animation = AnimationState::JUMPING;
  }
}
void Player::render()
{
  window.draw(player);
}
void Player::playerMovement(float dt)
{
  player.move(x * dt * player_Speed, y * gravity_speed * dt);
}
void Player::resetMovement()
{
  x = 0;
}
bool Player::CollisionPlayerAdvanced(Platform &collider)

{
  sf::Vector2f top_left = player.getPosition(); // 1
  sf::Vector2f bottom_right;                    // 2
  bottom_right.x = player.getPosition().x + player.getGlobalBounds().width;
  bottom_right.y = player.getPosition().y + player.getGlobalBounds().height;

  sf::Vector2f top_left_collider = collider.getPosition(); // 3
  sf::Vector2f bottom_right_collider;                      // 4
  bottom_right_collider.x =
    collider.getPosition().x + collider.getGlobalBounds().width;
  bottom_right_collider.y =
    collider.getPosition().y + collider.getGlobalBounds().height;

  float x_pen = 0;
  float y_pen = 0;
  bool top    = true;
  bool left   = true;

  // both x if true collision on x-axis
  if (top_left_collider.x < top_left.x && top_left.x < bottom_right_collider.x)
  {
    // right side collider
    x_pen = bottom_right_collider.x - top_left.x;
    left  = false;
  }
  else if (
    top_left_collider.x < bottom_right.x &&
    bottom_right.x < bottom_right_collider.x)
  {
    // left side collider
    x_pen = bottom_right.x - top_left_collider.x;
  }

  // both y if true collision on y-axis
  if (top_left_collider.y < top_left.x && top_left.y < bottom_right_collider.y)
  {
    // bottom collider
    y_pen = bottom_right_collider.y - top_left.y;
    top   = false;
  }
  else if (
    top_left_collider.y < bottom_right.y &&
    bottom_right.y < bottom_right_collider.y)
  {
    // top collider
    y_pen = bottom_right.y - top_left_collider.y;
  }

  if (x_pen == 0 || y_pen == 0)
  {
  }
  else
  {
    if (x_pen < y_pen)
    {
      if (left)
      {
        // hit left collider

        // std::cout<<"left"<<std::endl;
      }
      else
      {
        // hit right collider

        // std::cout<<"right"<<std::endl;
      }
    }
    else
    {
      // collide y
      if (top)
      {
        // std::cout<<"top"<<std::endl;
        //  hit top collider
      }
      else
      {
        // std::cout<<"bottom"<<std::endl;
        // hit bottom collider
      }
    }
    return true;
  }
  return false;
}
bool Player::CollisionPlayer(Platform& collider)
{
  if (player.getPosition().x < collider.getPosition().x-20  + collider.getGlobalBounds().width &&
      player.getPosition().x + player.getGlobalBounds().width  > collider.getPosition().x + 20 &&
      player.getPosition().y < collider.getPosition().y - 140 + collider.getGlobalBounds().height &&
      player.getPosition().y + player.getGlobalBounds().height > collider.getPosition().y)
  {
    landed  = true;
    y = -0.1f;
  }
  else
  {
    landed = false;
    y = (float)1.5f *gravity_speed;
    return false;
  }
  return true;
}

void Player::keyPressed(sf::Event event)
{
  if (event.key.code == (sf::Keyboard::A))
  {
    current_animation = AnimationState::RUNNING;
    x                 = -2;
    player.setScale(2, 2);
    player.setOrigin(0, 0);
    velocity = 1;
  }
  else if (event.key.code == (sf::Keyboard::D))
  {
    current_animation = AnimationState::RUNNING;
    x                 = 2;
    player.setScale(-2, 2);
    player.setOrigin(player.getGlobalBounds().width / 2, 0);
    velocity = 1;
  }
  if (event.key.code == (sf::Keyboard::Key::Space))
  {
    if (jump_timer > 2)
    {
      landed = false;
      // player.move(0,-2* player_Speed);
      jump       = true;
      jump_timer = 0;
    }
  }
}
void Player::keyReleased(sf::Event event)
{
  if (event.key.code == (sf::Keyboard::A))
  {
    x                 = 0;
    velocity          = 0;
    current_animation = AnimationState::IDLE;
  }
  else if (event.key.code == (sf::Keyboard::D))
  {
    x                 = 0;
    velocity          = 0;
    current_animation = AnimationState::IDLE;
  }

  if (event.key.code == sf::Keyboard::Space)
  {
    y = 5;
  }
}
void Player::setGravity(bool grav)
{
  landed = grav;
}
sf::FloatRect Player::getGlobalBounds()
{
  return player.getGlobalBounds();
}
void Player::playerAnimator(
  float update_animation, AnimationState &current, sf::IntRect& player_texture_rectangles,
  int max_size, int sprite_size)
{
  if (clock_animation_texture.getElapsedTime().asSeconds() >= update_animation)
  {
    if (current_animation == AnimationState::RUNNING)
    {
      player_texture_rectangle.left += sprite_size;
      player_texture_rectangle.width  = 49;
      player_texture_rectangle.top    = 0.f;
      player_texture_rectangle.height = 40;
      if (player_texture_rectangle.left >= max_size)
      {
        player_texture_rectangle.left = 0;
      }
    }

    else if (current_animation == AnimationState::JUMPING)
    {
      player_texture_rectangle.left += sprite_size;
      player_texture_rectangle.width  = 49;
      player_texture_rectangle.top    = 80.f;
      player_texture_rectangle.height = 40;
      if (player_texture_rectangle.left >= max_size)
      {
        player_texture_rectangle.left = 0;
      }
    }

    else if (current_animation == AnimationState::IDLE)
    {
      player_texture_rectangle.left += sprite_size;
      player_texture_rectangle.width  = 49;
      player_texture_rectangle.top    = 120.f;
      player_texture_rectangle.height = 40;
      if (player_texture_rectangle.left >= max_size)
      {
        player_texture_rectangle.left = 0;
      }
    }

    clock_animation_texture.restart();
    player.setTextureRect(player_texture_rectangle);
  }
}
