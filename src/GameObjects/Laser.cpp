#include "Laser.h"

Laser::Laser(sf::RenderWindow& game_window):window(game_window)
{
  srand(time(nullptr));
  if (!laser_texture.loadFromFile("Data/Images/kenney_physicspack"
                                  "/PNG/Other/coinBronze.png"))
  {
    std::cout << "laser texture did not load \n";
  }
  visibility = false;
  laser.setTexture(laser_texture);
  laser.rotate(90);
  laser.setPosition(0, 0);
  laser.setScale(0.5, 0.5);

  if (!shoot_buffer.loadFromFile("Data/Sounds/Shoot.wav"))
  {
    std::cout << "shoot audio failed to load \n";
  }
  shoot.setBuffer(shoot_buffer);
}
void Laser::update(float dt)
{
  if (fire_forward)
  {
    laser.move(4.0f * laserSpeed * dt, 0.5);
  }
  else
  {
    laser.move(-4.0f * laserSpeed * dt, 0.5);
  }

  if (laser.getPosition().y >= (float)window.getSize().y)
  {
    visibility = false;
    std::cout << laser.getPosition().y << std::endl;
  }
}
void Laser::render()
{
  window.draw(laser);
}
void Laser::scoreCollision(Enemy &collider)
{
  if (
    laser.getPosition().x <
      collider.getPosition().x - 40 + collider.getGlobalBounds().width &&
    laser.getPosition().x + laser.getGlobalBounds().width >
      collider.getPosition().x + 40 &&
    laser.getPosition().y <
      collider.getPosition().y + collider.getGlobalBounds().height &&
    laser.getPosition().y + laser.getGlobalBounds().height >
      collider.getPosition().y)
  {
    collider.setVisibility(false);
    laser.setPosition(0, 0);
    visibility = false;
    shoot.play();
  }
}
bool Laser::getVisibility() const
{
  return visibility;
}
void Laser::setVisibility(bool set)
{
  visibility = set;
}
sf::FloatRect Laser::getGlobalBounds()
{
  return {};
}
void Laser::setPosition(float x,float y)
{
  laser.setPosition(x,y);
}
void Laser::getDirection(bool set)
{
  fire_forward = set;
}
