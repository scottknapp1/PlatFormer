#include "Coin.h"

Coin::Coin(sf::RenderWindow& game_window):window(game_window)
{
  srand(time(nullptr));
  if (!coin_texture.loadFromFile("Data/Images/kenney_physicspack/PNG/Other/coinBronze.png"))
  {
    std::cout << "ball texture did not load \n";
  }
  coin.setTexture(coin_texture);

  // audio for coin pickup
  if (!coin_pick_buffer.loadFromFile("Data/Sounds/pickupCoin.wav"))
  {
    std::cout << "coin pickup audio failed to load \n";
  }
  coin_pickup.setBuffer(coin_pick_buffer);
}
void Coin::prepare_coin(float x, float y)
{
  coin.setScale(1, 1);
  coin.setPosition(x, y);
  visibility = true;
}

void Coin::movement()
{
  coin_bounce_timer += 1.0f;
  // gives coin bounce
  if (coin_bounce_timer <= 18)
  {
    coin.move(0, -0.1);
  }
  else
  {
    coin.move(0, 0.1);
  }
  // reset coin bounce
  if (coin_bounce_timer >= 36)
  {
    coin_bounce_timer = 0;
  }
}
void Coin::update()
{
  movement();
}
void Coin::render()
{
  window.draw(coin);

}
void Coin::scoreCollision(Player &collider,Score &scoreboard)
{
  if (
    coin.getPosition().x <
      collider.getPosition().x - 50 + collider.getGlobalBounds().width &&
    coin.getPosition().x + coin.getGlobalBounds().width >
      collider.getPosition().x + 50 &&
    coin.getPosition().y <
      collider.getPosition().y + collider.getGlobalBounds().height &&
    coin.getPosition().y + coin.getGlobalBounds().height - 50 >
      collider.getPosition().y)
  {
    coin_pickup.play();
    setVisibility(false);
    scoreboard.scoreUpdate(true);
    coins_collected++;
  }
}
bool Coin::getVisibility() const
{
  return visibility;
}
void Coin::setVisibility(bool set)
{
  visibility = set;
}
sf::FloatRect Coin::getGlobalBounds()
{
  return {};
}

