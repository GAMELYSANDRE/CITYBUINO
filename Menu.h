#ifndef __MENU__
#define __MENU__

#include "Tile.h"
#include "Constant.h"
#include <Gamebuino-Meta.h>

class Menu
{
  public:
    // constructors
    Menu();
    // Destructor
    ~Menu();

    // getters methods
    bool GetState() const;
    uint8_t Choice() const;
    bool CursorState() const;
    uint16_t Cost() const;
    uint16_t Citizen() const;
    uint16_t Credit() const;
    uint16_t Debit() const;

    // setters methods
    void State(bool ChangeState);
    void Choice(uint8_t ChangeChoice);
    void CursorState(bool ChangeCursorState);
    void Cost(uint16_t ChangeCost);
    void Citizen(uint16_t ChangeCitizen);
    void Credit(uint16_t ChangeCredit);
    void Debit(uint16_t ChangeDebit);

    void Display();

  private:
    bool m_State; 	       // inactive (0) or active (1)
    Tile *m_TileMenu[ NBR_ITEM_MENU ];   // choice chart
    uint8_t m_Choice;	   // choice of the tile
    uint8_t m_Position;    // menu navigation
    bool m_CursorState;    // inactive (0) or active (1)
    uint16_t m_Cost;        // cost of construction
    bool m_ButtonBLock;    // LockButtonB

    // others methods
    void DebugMenu();
    void SquareSelection();
    void DisplayInfo();

};

#endif
