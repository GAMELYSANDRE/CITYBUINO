#include "Menu.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Menu::Menu() :
  m_State(0),
  m_Choice(4),
  m_CursorState(0)
{
  for (int x = 1; x < 3; x++)
  {
    m_TileMenu[x - 1] = new Tile(x, 1, 58, x * 10, x + 3);
  }
}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Menu::~Menu()
{
  for (int x = 0; x < 2; x++)
  {
    delete m_TileMenu[x];
  }
}

//----------------------------------------------------------------------
//                       Getters methods
//----------------------------------------------------------------------
bool Menu::State() const
{
  return (m_State);
}
bool Menu::CursorState() const
{
  return (m_CursorState);
}
uint8_t Menu::Choice() const
{
  return (m_Choice);
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Menu::State(bool ChangeState)
{
  m_State = ChangeState;
}
void Menu::CursorState(bool ChangeCursorState)
{
  m_CursorState = ChangeCursorState;
}
void Menu::Choice(uint8_t ChangeChoice)
{
  m_Choice = ChangeChoice;
}

void Menu::Display()
{
  gb.display.setColor(WHITE);
  gb.display.fillRect(55, 5, 22, 55);
  gb.display.setColor(BLACK);
  gb.display.drawRect(55, 5, 22, 55);
  SquareSelection();
  m_TileMenu[0]->Display();
  m_TileMenu[1]->Display();
}

void Menu::SquareSelection()
{
  gb.display.setColor(LIGHTGREEN);
  gb.display.fillRect(57, (10 * (m_Choice-3))-1  , 18, 10);
  if (gb.buttons.pressed(BUTTON_A))
  {
    if ( m_Choice < 5)
    {
      m_Choice++;
    }
    else
    {
      m_Choice = 4;
    }
    gb.sound.playOK();
  }
  if (gb.buttons.pressed(BUTTON_B))
  {
    gb.sound.playOK();
    m_State = 0;
    m_CursorState = 1;
  }
}
