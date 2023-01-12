#include "Platform.h"

Platform::Platform(sf::RenderWindow& game_window):window(game_window)
{
  if (!sprite_Texture.loadFromFile("Data/Images/rock_sprite.png"))
  {
    std::cout << "ball texture did not load \n";
  }
  sprite.setTexture(sprite_Texture);
}
void Platform::update()
{

}
void Platform::render()
{
  window.draw(sprite);
}
void Platform::prepare_platform(float x, float y)
{
  sprite.setScale(1, 1);
  sprite.setPosition(x, y);
}

bool Platform::getVisibility() const
{
  return visibility;
}
void Platform::setVisibility(bool set)
{
  visibility = set;
}
sf::Vector2f Platform::getPosition()
{
  return sprite.getPosition();
}
sf::FloatRect Platform::getGlobalBounds()
{
  return sprite.getGlobalBounds();
}
