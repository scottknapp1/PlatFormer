#include "Life.h"

Life::Life(sf::RenderWindow& window)  : window(window)
{
  player_life = 3;
  init();
}
void Life::update()
{
  life_text_player.setString("Life: " + std::to_string(player_life));
}
void Life::render()
{
  window.draw(life_text_player);
}
void Life::init()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load \n";
  }
  life_text_player.setString("Score: " + player_life_Text);
  life_text_player.setFont(font);
  life_text_player.setCharacterSize(50);
  life_text_player.setFillColor(sf::Color::Yellow);
  life_text_player.setPosition(850, 100);
}
int Life::getLifePlayer() const{return player_life;}

void Life::lifeUpdate(bool hit)
{
  if (hit)
  {
    player_life -= 1;
    life_text_player.setString("Life: " + std::to_string(player_life));
  }
}
void Life::resetLife()
{
  player_life = 3;
  life_text_player.setString("Life: " + std::to_string(player_life));
}
void Life::setPosition()
{
  life_text_player.setPosition(
    (float)window.getSize().x / 2, (float)window.getSize().y / 2);
}
