#ifndef __GAME__
#define __GAME__
#include <Gamebuino-Meta.h>
#include "Constant.h"
#include "Grid.h"
#include "Menu.h"
#include "Cursor.h"
#include "GBTime.h"

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
    GBTime *m_Time;
    bool m_Data; //avoid unnecessary loops
    int32_t m_Money;
    uint32_t m_Credit;
    uint32_t m_Debit;
    uint16_t m_Citizen;
    uint16_t m_NbrDay;

    // method of use
    void DisplayMenu();
    void DisplayCursor();
    void MoveCursor();
    void ErrorCursor();
    void ConstructCursor();
    void DisplayMoney();
    void DisplayTime();
    void UpdateInfo();
    void Message( char TextMessage[18] );
    void Memory(uint8_t Memory_Action);


};
#endif
