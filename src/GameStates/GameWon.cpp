#include "GameWon.h"

GameWon ::GameWon(sf::RenderWindow& window): window(window)
{
  if (!background_texture_Game_Won.loadFromFile("Data/images/game_won_background.png"))
  {
    std::cout << "background texture did not load ";
  }
  background_Game_Won.setTexture(background_texture_Game_Won);
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  init();
}
void GameWon::init()
{
  return_Game_Menu.setString("Return to Menu");
  return_Game_Menu.setFont(font);
  return_Game_Menu.setFillColor(sf::Color::Yellow);
  return_Game_Menu.setCharacterSize(50);
  return_Game_Menu.setPosition(200, 150);

  quit_option.setString("Quit");
  quit_option.setFont(font);
  quit_option.setFillColor(sf::Color::White);
  quit_option.setCharacterSize(50);
  quit_option.setPosition(800, 150);
}
void GameWon::update()
{

}
void GameWon::render()
{
  window.draw(background_Game_Won);
  window.draw(game_Won_text);
  window.draw(quit_option);
  window.draw(return_Game_Menu);
}
void GameWon::keyHandler(sf::Event event, GameState& current_state)
{
  if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
  {
    play_selected_won--;
    if (play_selected_won <= 1)
    {
      play_selected_won = 1;
    }
  }
  if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
  {
    play_selected_won++;
    if (play_selected_won >= 2)
    {
      play_selected_won = 2;
    }
  }
  if (play_selected_won == return_to_menu_won)
  {
    return_Game_Menu.setFillColor(sf::Color::Yellow);
    quit_option.setFillColor(sf::Color::White);
  }
  else if (play_selected_won == quit_won)
  {
    return_Game_Menu.setFillColor(sf::Color::White);
    quit_option.setFillColor(sf::Color::Yellow);
  }
  if (event.key.code == sf::Keyboard::Enter)
  {
    if (play_selected_won == return_to_menu_won)
    {
      current_state = GameState::GAME_MENU;
    }
    else if (play_selected_won == quit_won)
    {
      window.close();
    }
  }
}

