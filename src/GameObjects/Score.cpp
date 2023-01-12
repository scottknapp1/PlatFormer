#include "Score.h"

Score::Score(sf::RenderWindow& game_window)  : window(game_window)
{
  playerScore = 0;
  init();
}
void Score::update()
{
  ScoreTextPlayer.setString("Score: " + std::to_string(playerScore));
  //setPosition();
}
void Score::render()
{
  window.draw(ScoreTextPlayer);

}
void Score::init()
{
  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load \n";
  }
  ScoreTextPlayer.setString("Score: " + player);
  ScoreTextPlayer.setFont(font);
  ScoreTextPlayer.setCharacterSize(50);
  ScoreTextPlayer.setFillColor(sf::Color::Yellow);
  ScoreTextPlayer.setPosition(100, 100);
}
int Score::getScorePlayer() const{return playerScore;}

void Score::scoreUpdate(bool hit)
{
  if (hit)
  {
    playerScore += 100;
    ScoreTextPlayer.setString("Score: " + std::to_string(playerScore));
  }
}
void Score::resetScore()
{
  playerScore = 0;
  ScoreTextPlayer.setString("Score: " + std::to_string(playerScore));
}
void Score::setPosition()
{
  ScoreTextPlayer.setPosition(
    (float)window.getSize().x / 2, (float)window.getSize().y / 2);
}
