#include "GameOverMenu.h"

GameOverMenu ::GameOverMenu(sf::RenderWindow& window): window(window)
{
  if (!background_texture_Game_over_menu.loadFromFile("Data/images/gameover_background.png"))
  {
    std::cout << "background texture did not load ";
  }
  background_Game_over_menu.setTexture(background_texture_Game_over_menu);
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  init();
}
void GameOverMenu::init()
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
void GameOverMenu::update()
{

}
void GameOverMenu::render()
{
  window.setView(window.getDefaultView());
  window.draw(background_Game_over_menu);
  window.draw(game_over_menu_text);
  window.draw(quit_option);
  window.draw(return_Game_Menu);
}
void GameOverMenu::keyHandler(sf::Event event, GameState& current_state)
{
  if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
  {
    play_selected--;
    if (play_selected <= 1)
    {
      play_selected = 1;
    }
  }
  if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
  {
    play_selected++;
    if (play_selected >= 2)
    {
      play_selected = 2;
    }
  }
  if (play_selected == return_to_menu)
  {
    return_Game_Menu.setFillColor(sf::Color::Yellow);
    quit_option.setFillColor(sf::Color::White);
  }
  else if (play_selected == quit)
  {
    return_Game_Menu.setFillColor(sf::Color::White);
    quit_option.setFillColor(sf::Color::Yellow);
  }
  if (event.key.code == sf::Keyboard::Enter)
  {
    if (play_selected == return_to_menu)
    {
      current_state = GameState::GAME_MENU;
    }
    else if (play_selected == quit)
    {
      window.close();
    }
  }
}
