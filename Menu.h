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
    bool CursorState() const;
    uint8_t Choice() const;

    // setters methods
    void State(bool ChangeState);
    void CursorState(bool ChangeCursorState);
    void Choice(uint8_t ChangeChoice);

    void Display();

  private:
    bool m_State; 	       // inactive (0) or active (1)
    Tile *m_TileMenu[2];   // choice chart
    uint8_t m_Choice;	   // choice of the tile
    bool m_CursorState;    // inactive (0) or active (1)

    void SquareSelection();

};

#endif
