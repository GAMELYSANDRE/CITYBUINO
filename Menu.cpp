#include "Menu.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Menu::Menu() :
  m_State(0),
  m_Choice(4),
  m_CursorState(0),
  m_Cost(0),
  m_ButtonBLock(1)
{
  for (int x = 1; x < 5; x++)
  {
    m_TileMenu[x - 1] = new Tile(x, 1, 58, x * 10, x + 3);
  }
}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Menu::~Menu()
{
  for (int x = 0; x < 4; x++)
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
uint8_t Menu::Choice() const
{
  return (m_Choice);
}
bool Menu::CursorState() const
{
  return (m_CursorState);
}
uint8_t Menu::Cost() const
{
  return (m_Cost);
}
bool Menu::ButtonBLock() const
{
  return (m_ButtonBLock);
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Menu::State(bool ChangeState)
{
  m_State = ChangeState;
}
void Menu::Choice(uint8_t ChangeChoice)
{
  m_Choice = ChangeChoice;
}
void Menu::CursorState(bool ChangeCursorState)
{
  m_CursorState = ChangeCursorState;
}
void Menu::Cost(uint8_t ChangeCost)
{
  m_Cost = ChangeCost;
}
void Menu::ButtonBLock(bool ChangeButtonBLock)
{
  m_ButtonBLock = ChangeButtonBLock;
}


void Menu::Display()
{
  gb.display.setColor(WHITE);
  gb.display.fillRect(55, 8, 22, 55);
  gb.display.setColor(BLACK);
  gb.display.drawRect(55, 8, 22, 55);
  SquareSelection();
  m_TileMenu[0]->Display();
  m_TileMenu[1]->Display();
  m_TileMenu[2]->Display();
  m_TileMenu[3]->Display();
}

void Menu::SquareSelection()
{
  gb.display.setColor(LIGHTBLUE);
  gb.display.fillRect(57, (10 * (m_Choice - 3)) - 1  , 18, 10);
  if (gb.buttons.pressed(BUTTON_A))
  {
    if ( m_Choice < 7 )
    {
      m_Choice++;
    }
    else
    {
      m_Choice = 4;
    }
    gb.sound.fx(SOUND_MENU_1);
  }
  if (gb.buttons.pressed(BUTTON_B))
  {
    gb.sound.playOK();
    m_State = 0;
    m_CursorState = true;
    m_ButtonBLock = true;
  }
  switch (m_Choice)
  {
    case BULL:
      m_Cost = 10;
      break;
    case ROAD_H:
      m_Cost = 50;
      break;
    case ROAD_V:
      m_Cost = 50;
      break;
    case HOME_RED:
      m_Cost = 200;
      break;
  }
  // Display Texte
  gb.display.setCursor(56, 2);
  gb.display.setColor(GRAY);
  gb.display.print("$");
  gb.display.print(m_Cost);
  gb.display.setCursor(55, 1);
  gb.display.setColor(WHITE);
  gb.display.print("$");
  gb.display.print(m_Cost);
}
