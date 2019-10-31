#ifndef __GAME__
#define __GAME__
#include <Gamebuino-Meta.h>
#include "Constant.h"
#include "Grid.h"
#include "Menu.h"
#include "Cursor.h"

class Game
{
  public:
    // constructor
    Game ();
    // Destructor
    ~Game();
    // method of use
    void Display();

  private:
    Grid *m_City;
    Menu *m_Menu;
    Cursor *m_Cursor;
    uint16_t m_Money;

    // method of use
    void DisplayMenu();
    void DisplayCursor();
    void MoveCursor();
    void ErrorCursor();
    void ConstructCursor();
    void DisplayMoney();


};
#endif
