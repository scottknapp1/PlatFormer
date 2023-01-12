#include "MainMenu.h"

MainMenu ::MainMenu(sf::RenderWindow& window): window(window)
{
  if (!background_texture_menu.loadFromFile("Data/Images/game_menu_background.png"))
  {
    std::cout << "background texture did not load \n";
  }
  background_menu.setTexture(background_texture_menu);
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "font did not load \n";
  }

  if (!game_music.openFromFile("Data/Sounds/Game_Music.ogg"))
  {
    std::cout << "game music did not load\n";
  }
  game_music.setLoop(true);
  game_music.setVolume(5);
  game_music.play();

  init();
}
void MainMenu::init()
{
  menu_text.setString("Welcome to JumpPad");
  menu_text.setFont(font);
  menu_text.setFillColor(sf::Color::White);
  menu_text.setCharacterSize(60);
  menu_text.setPosition(100, 50);

  play_option.setString("Play");
  play_option.setFont(font);
  play_option.setFillColor(sf::Color::Yellow);
  play_option.setCharacterSize(50);
  play_option.setPosition(200, 600);

  quit_option.setString("Quit");
  quit_option.setFont(font);
  quit_option.setFillColor(sf::Color::White);
  quit_option.setCharacterSize(50);
  quit_option.setPosition(600, 600);
}
void MainMenu::update()
{

}
void MainMenu::render()
{
  window.draw(background_menu);
  window.draw(menu_text);
  window.draw(quit_option);
  window.draw(play_option);
}
void MainMenu::keyHandler(sf::Event event,GameState& current_state)
{
  if (event.type == sf::Event::KeyPressed)
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
    if (play_selected == play)
    {
      play_option.setFillColor(sf::Color::Yellow);
      quit_option.setFillColor(sf::Color::White);
    }
    else if (play_selected == quit)
    {
      play_option.setFillColor(sf::Color::White);
      quit_option.setFillColor(sf::Color::Yellow);
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (play_selected == play)
      {
        current_state = GameState::GAME_OPTION;
      }
      else if (play_selected == quit)
      {
        window.close();
      }
    }
  }
}
