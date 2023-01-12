#include "GamePlay.h"

GamePlay ::GamePlay(sf::RenderWindow& window)
  :window(window)
{
  test.setSize((float)window.getSize().x,(float)window.getSize().y);
  test.setCenter(window.getView().getCenter());

  // audio for player footsteps
  if (!player_burn_buffer.loadFromFile("Data/Sounds/lava_burn.ogg"))
  {
    std::cout << "lava audio failed to load \n";
  }
  player_burn.setBuffer(player_burn_buffer);

  // instance of score
  score = new Score(window);

  // life
  life = new Life(window);

  // instance of player
  player = new Player(window, 75,450);

  // enemy array
  for (auto & i : enemy)
  {
    i = new Enemy(window);
  }
  // coin array
  for (auto & i : coin)
  {
    i = new Coin(window);
  }

  // platform array
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      platform[i * width + j] = new Platform(window);

      platform[i * width + j]->prepare_platform(
        70.f * (float)j, 70.f * (float)i);
      platform[i * width + j]->setVisibility(false);
    }
  }
  //instance of laser
  for (auto & i : laser)
  {
    i = new Laser(window);
  }
  // map block top and bottom horizontal
  for (int i = 0; i < height; i += 9)
  {
    for (int j = 0; j < width; j += 1)
    {
      platform[i * width + j]->setVisibility(true);
    }
  }
  for (int i = 0; i < height; i += 10)
  {
    for (int j = 0; j < width; j += 1)
    {
      platform[i * width +j]->setVisibility(true);
    }
  }
  // map block left and right vertical
  for (int i = 1; i < height; i += 1)
  {
    platform[i * 40]->setVisibility(true);
    platform[i * 39 + i - 1]->setVisibility(true);
  }
  // hole to fall though
  for (int i = 0; i < height; i += 9)
  {
    for (int j = 9; j < width; j += 9)
    {
      platform[i * width + j]->setVisibility(false);
      platform[1 + i * width + j]->setVisibility(false);
      platform[19]->setVisibility(true);
    }
  }

  // build platforms to jump on
  for (int i = 0; i < height; i += 7)
  {
    for (int j = 0; j < 5; j += 1)
    {
      platform[i * width + 4 + j]->setVisibility(true);
      platform[4 + i * width + 10 + j]->setVisibility(true);
      platform[2 + i * width + 22 + j]->setVisibility(true);
      platform[2 + i * width + 30 + j]->setVisibility(true);
    }
  }
  // build platforms to jump on
  for (int i = 0; i < 5; i += 3)
  {
    for (int j = 2; j < 5; j += 1)
    {
      platform[2 + i * width + 4 + j]->setVisibility(true);
      platform[3 + i * width + 10 + j]->setVisibility(true);
      platform[3 + i * width + 22 + j]->setVisibility(true);
      platform[3 + i * width + 30 + j]->setVisibility(true);
    }
  }
  // build platforms to jump on
  for (int i = 0; i < 6; i += 5)
  {
    for (int j = 0; j < 6; j += 1)
    {
      platform[1 + i * width + 4 + j]->setVisibility(true);
      platform[2 + i * width + 10 + j]->setVisibility(true);
      platform[+i * width + 22 + j]->setVisibility(true);
      platform[+i * width + 30 + j]->setVisibility(true);
    }
  }
  init();
}

GamePlay::~GamePlay()
{
  delete life;
  delete player;
  delete score;

  for (auto& i : platform)
  {
    delete i;
  }

  for (auto& i : laser)
  {
    delete i;
  }

  for (auto& i : enemy)
  {
    delete i;
  }

  for (auto& i : coin)
  {
    delete i;
  }
}
void GamePlay::init()
{
  // background init
  if (!background_texture_gameplay.loadFromFile("Data/Images/cave_background.png"))
  {
    std::cout << "background texture did not load \n";
  }

  background_menu.setTexture(background_texture_gameplay);
  background_texture_gameplay.setRepeated(true);

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  int x_pos_enemy[enemy_count] = { 700, 1190, 2030, 2590 };
  int x_pos_coin[coin_count]   = { 635, 1125, 1958, 2520 };

  // instance of enemy array location
  for (int i = 0; i < enemy_count; ++i)
  {
    enemy[i]->prepare_Enemy((float)x_pos_enemy[i], 80);
  }

  for (int i = 0; i < coin_count; ++i)
  {
    coin[i]->prepare_coin((float)x_pos_coin[i], 150);
  }
}
void GamePlay::update(float dt,GameState& current_state)
{
  player->update(dt);

  // win condition
  if (score->getScorePlayer() == 400)
  {
    test.setCenter((float)1080 / 2, (float)720 / 2);
    resetPlayer();
    current_state = GameState::GAME_WON;
  }
  // stop player going out of map
  if (player->getPosition().y < 20)
  {
    player->resetMovement();
  }
  if (player->getPosition().x < 20)
  {
    player->setPosition(30, 550);
  }
  if (player->getPosition().x > 2650)
  {
    player->setPosition(2650, 550);
  }
  // player looses all lives
  if (life->getLifePlayer() == 0)
  {
    test.setCenter((float)1080 / 2, (float)720 / 2);
    resetPlayer();
    current_state = GameState::GAME_OVER;
  }
  // player falling in lava
  if (player->getPosition().y > (float)window.getSize().y-100)
  {
    player_burn.play();
    life->lifeUpdate(true);
    test.setCenter((float)1080 / 2, (float)720 / 2);
    player->setPosition(200, 500);
  }
  // updates coin
  for (auto& i : coin)
  {
    if (i->getVisibility())
    {
      i->update();
      i->scoreCollision(*player, *score);
    }
  }

  // enemy update
  for (auto& i : enemy)
  {
    if (i->getVisibility())
    {
      i->update();
      i->PlayerCollision(*player, current_state, *life, test);
    }
  }

  score->update();
  life->update();

  for (auto& i : laser)
  {
    // updates laser movement if visible
    if (i->getVisibility())
    {
      for (auto& I : enemy)
      {
        i->scoreCollision(*I);
      }
      i->update(dt);
    }
  }
  // updates player
  player->update(dt);

  // makes camera move with player

  if (player->getPosition().x < ((float)window.getSize().x / 2))
  {
    // test.setCenter(player->getPosition().x,test.getCenter().y);
  }
  else if (player->getPosition().x + (float)window.getSize().x / 2 < 2800)
  {
    test.setCenter(player->getPosition().x, window.getView().getCenter().y);
  }
  // sets the camera
  window.setView(test);

  // platform collision check left/right
  for (auto& i : platform)
  {
    if (player->CollisionPlayerAdvanced(*i) && i->getVisibility())
    {
    }
    player->setGravity(true);
  }
  for (auto& i : platform)
  {
    if (player->CollisionPlayer(*i) && i->getVisibility())
    {
      return;
    }
    // sets gravity on if not colliding
    player->setGravity(true);
  }
}

void GamePlay::keyHandler(sf::Event event, GameState& current_state)
{
  // key pressed
  if (event.type == sf::Event::KeyPressed)
  {
    player->keyPressed(event);
    keyPressed(event);
  }
  // key released
  else if (event.type == sf::Event::KeyReleased)
  {
    player->keyReleased(event);
  }
}
void GamePlay::render()
{
  window.setView(test);
  window.draw(background_menu);

  // renders coin if visible
  for (auto& i : coin)
  {
    if (i->getVisibility())
    {
      i->render();
    }
  }

  // renders enemy if visible
  for (auto& i : enemy)
  {
    if (i->getVisibility())
    {
      i->render();
    }
  }
  // renders laser if visible
  for (auto& i : laser)
  {
    i->render();
    if (i->getVisibility())
    {
      i->render();
    }
  }
  // renders platform if visible
  for (auto& i : platform)
  {
    if (i->getVisibility())
    {
      i->render();
    }
  }

  player->render();

  // overlay render
  window.setView(window.getDefaultView());
  score->render();
  life->render();
}
void GamePlay::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Q)
  {
    if (!laser[active_laser]->getVisibility())
    {
      laser[active_laser]->setPosition(
        player->getPosition().x + player->getGlobalBounds().width / 2,
        player->getPosition().y + player->getGlobalBounds().height / 2);
      laser[active_laser]->setVisibility(true);
      laser[active_laser]->getDirection(false);
      if (active_laser == 9)
      {
        active_laser = 0;
      }
      else
      {
        active_laser++;
      }
    }
  }
  if (event.key.code == sf::Keyboard::E)
  {
    if (!laser[active_laser]->getVisibility())
    {
      laser[active_laser]->setPosition(
        player->getPosition().x + player->getGlobalBounds().width / 2,
        player->getPosition().y + player->getGlobalBounds().height / 2);
      laser[active_laser]->setVisibility(true);
      laser[active_laser]->getDirection(true);
      if (active_laser == 9)
      {
        active_laser = 0;
      }
      else
      {
        active_laser++;
      }
    }
  }
}
void GamePlay::resetPlayer()
{
  window.setView(window.getDefaultView());
  player->setPosition(200, 300);
  score->resetScore();
  life->resetLife();
  player->resetMovement();
  init();
}

