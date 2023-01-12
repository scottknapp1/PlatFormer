#include "OptionMenu.h"

OptionMenu ::OptionMenu(sf::RenderWindow& window): window(window)
{
  if (!option_background_texture_menu.loadFromFile("Data/Images/menu_background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  option_background_menu.setTexture(option_background_texture_menu);
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }
  init();
}
void OptionMenu::init()
{
  option_play_option.setString("Continue");
  option_play_option.setFont(font);
  option_play_option.setFillColor(sf::Color::Yellow);
  option_play_option.setCharacterSize(50);
  option_play_option.setPosition(200, 600);

  option_quit_option.setString("Quit");
  option_quit_option.setFont(font);
  option_quit_option.setFillColor(sf::Color::White);
  option_quit_option.setCharacterSize(50);
  option_quit_option.setPosition(600, 600);
}
void OptionMenu::update()
{

}
void OptionMenu::render()
{
  window.draw(option_background_menu);
  window.draw(option_menu_text);
  window.draw(option_quit_option);
  window.draw(option_play_option);
}
void OptionMenu::keyHandler(sf::Event event,GameState& current_state)
{
  if (event.type == sf::Event::KeyPressed)
  {
    if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A)
    {
      option_play_selected--;
      if (option_play_selected <= 1)
      {
        option_play_selected = 1;
      }
    }
    if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
    {
      option_play_selected++;
      if (option_play_selected >= 2)
      {
        option_play_selected = 2;
      }
    }
    if (option_play_selected == option_play)
    {
      option_play_option.setFillColor(sf::Color::Yellow);
      option_quit_option.setFillColor(sf::Color::White);
    }
    else if (option_play_selected == option_quit)
    {
      option_play_option.setFillColor(sf::Color::White);
      option_quit_option.setFillColor(sf::Color::Yellow);
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (option_play_selected == option_play)
      {
        current_state = GameState::GAME_PLAY;
      }
      else if (option_play_selected == option_quit)
      {
        window.close();
      }
    }
  }
}

