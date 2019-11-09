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
    bool State() const;
    uint8_t Choice() const;
    bool CursorState() const;
    uint8_t Cost() const;
    bool ButtonBLock() const;

    // setters methods
    void State(bool ChangeState);
    void Choice(uint8_t ChangeChoice);
    void CursorState(bool ChangeCursorState);
    void Cost(uint8_t ChangeCost);
    void ButtonBLock(bool ChangeButtonBLock);

    void Display();

  private:
    bool m_State; 	       // inactive (0) or active (1)
    Tile *m_TileMenu[4];   // choice chart
    uint8_t m_Choice;	   // choice of the tile
    bool m_CursorState;    // inactive (0) or active (1)
    uint8_t m_Cost;        // cost of construction
    bool m_ButtonBLock;    // LockButtonB

    void SquareSelection();

};

#endif
