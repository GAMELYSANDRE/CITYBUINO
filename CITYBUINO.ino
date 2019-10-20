#include <Gamebuino-Meta.h>
#include "Game.h"

//#include "Menu.h"

Game *CityBuino;

//Menu *GameMenu;

void setup()
{
  gb.begin();
  CityBuino = new Game();
}

void loop()
{
  gb.waitForUpdate();
  gb.display.clear();

  CityBuino->Display();

}
