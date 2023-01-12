#include "Enemy.h"


Enemy::Enemy(sf::RenderWindow& game_window):window(game_window)
{
  if (!sprite_Texture.loadFromFile("Data/Images/Flight-Sheet.png"))
  {
    std::cout << "Enemy texture did not load \n";
  }
  sprite.setTexture(sprite_Texture);

  // audio for enemy collision
  if (!player_collide_enemy_buffer.loadFromFile("Data/Sounds/player_collision_enemy.wav"))
  {
    std::cout << "collision audio failed to load \n";
  }
  player_collide_enemy.setBuffer(player_collide_enemy_buffer);

  current_frame = sf::IntRect(0, 0, 48, 48);
  sprite.setTextureRect(current_frame);
}
void Enemy::PlayerCollision(
  Player &collider,GameState&current_state, Life& life,sf::View &test)

{
  if (
    sprite.getPosition().x <
      collider.getPosition().x + collider.getGlobalBounds().width - 60 &&
    sprite.getPosition().x + sprite.getGlobalBounds().width >
      collider.getPosition().x + 60 &&
    sprite.getPosition().y <
      collider.getPosition().y + collider.getGlobalBounds().height &&
    sprite.getPosition().y + sprite.getGlobalBounds().height - 40 >
      collider.getPosition().y)
  {
    player_collide_enemy.play();
    collider.setPosition(75, 450);
    life.lifeUpdate(true);
    test.setCenter((float)1080 / 2, (float)720 / 2);
  }
}
void Enemy::update()
{
  enemyMovement();
  enemyAnimator(0.09f, current_frame, 384, 48);
}
void Enemy::enemyMovement()
{
  moving_timer += 1.0f;

  if (moving_timer <= 90)
  {
    sprite.move(-2, 0);
    // flips sprite
    sprite.setScale(-3, 3);
    sprite.setOrigin(sprite.getGlobalBounds().width / 3, 0);
  }
  else
  {
    sprite.move(2, 0);
    // flips sprite
    sprite.setScale(3, 3);
    sprite.setOrigin(0, 0);
  }
  // reset patrol
  if (moving_timer >= 180)
  {
    moving_timer = 0;
  }
}
void Enemy::render()
{
  window.draw(sprite);
}
void Enemy::prepare_Enemy(float x,float y)
{
  sprite.setScale(3, 3);
  sprite.setPosition(x, y);
  visibility   = true;
  moving_timer = 0;
}
bool Enemy::getVisibility() const
{
  return visibility;
}
void Enemy::setVisibility(bool set)
{
  visibility = set;
}
sf::Vector2f Enemy::getPosition()
{
  return sprite.getPosition();
}
sf::FloatRect Enemy::getGlobalBounds()
{
  return sprite.getGlobalBounds();
}
void Enemy::enemyAnimator(
  float update_animation, sf::IntRect& player_texture_rectangles,
  int max_size, int sprite_size)
{
  if (enemy_clock_animation_texture.getElapsedTime().asSeconds() >= update_animation)
  {
    current_frame.left += sprite_size;
    current_frame.width  = 48.f;
    current_frame.top    = 0.f;
    current_frame.height = 48;
    if (current_frame.left >= max_size)
    {
      current_frame.left = 0;
    }
    enemy_clock_animation_texture.restart();
    sprite.setTextureRect(current_frame);
  }
}
