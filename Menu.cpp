#include "Menu.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Menu::Menu() :
  m_State(0),
  m_Choice(4),
  m_Position(0),
  m_CursorState(0),
  m_Cost(0),
  m_ButtonBLock(1)
{
  for (uint8_t x = 1; x < NBR_ITEM_MENU + 1; x++)
  {
    m_TileMenu[x - 1] = new Tile(x, 1, 58, ( x * 10 ) + 1, x + 3);
  }
  for (uint8_t x = 0; x < 3; x++)
  {
    m_Info[x] = 0;
  }
}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Menu::~Menu()
{
  for (uint8_t x = 0; x < NBR_ITEM_MENU; x++)
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
uint16_t Menu::Cost() const
{
  return (m_Cost);
}
bool Menu::ButtonBLock() const
{
  return (m_ButtonBLock);
}
uint16_t Menu::Citizen() const
{
  return (m_Info[0]);
}
uint16_t Menu::Credit() const
{
  return (m_Info[1]);
}
uint16_t Menu::Debit() const
{
  return (m_Info[2]);
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
void Menu::Cost(uint16_t ChangeCost)
{
  m_Cost = ChangeCost;
}
void Menu::ButtonBLock(bool ChangeButtonBLock)
{
  m_ButtonBLock = ChangeButtonBLock;
}
void Menu::Citizen(uint16_t ChangeCitizen )
{
  m_Info[0] = ChangeCitizen;
}
void Menu::Credit(uint16_t ChangeCredit )
{
  m_Info[1] = ChangeCredit;
}
void Menu::Debit(uint16_t ChangeDebit )
{
  m_Info[2] = ChangeDebit;
}

//----------------------------------------------------------------------
//                       Display menu methods
//----------------------------------------------------------------------

void Menu::Display()
{
  gb.display.setColor(WHITE);
  gb.display.fillRect(55, 8, 22, 54);
  gb.display.setColor(BLACK);
  gb.display.drawRect(55, 8, 22, 54);
  SquareSelection();
  for (uint8_t x = 0 + m_Position; x < 5 + m_Position ; x++)
  {
    m_TileMenu[x]->CartY( ((x + 1 - m_Position ) * 10 ) + 1);
    m_TileMenu[x]->Display(0);
  }
}

void Menu::SquareSelection()
{
  gb.display.setColor(LIGHTBLUE);
  gb.display.fillRect(57, (10 * (m_Choice - 3 - m_Position)), 18, 10);
  if ( m_Choice == INFO )
  {
    DisplayInfo();
  }
  if (gb.buttons.pressed(BUTTON_A))
  {
    if ( m_Choice < NBR_ITEM_MENU + 3 )
    {
      m_Choice++;
    }
    else
    {
      m_Choice = 4;
      m_Position = 0;
    }
    if ( m_Choice > 8 and m_Choice < NBR_ITEM_MENU + 4 )
    {
      m_Position++;
    }
    gb.sound.fx(SOUND_MENU_1);
  }
  if (gb.buttons.pressed(BUTTON_B))
  {
    gb.sound.playOK();
    m_CursorState = true;
    m_ButtonBLock = true;
    m_State = 0;
  }
  switch (m_Choice)
  {
    case INFO:
      m_State = 1;
      break;
    case BULL:
      m_Cost = 0;
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
    case POWER_STATION:
      m_Cost = 1000;
      break;
  }
  if ( m_Choice != INFO )
  {
    // Display Texte
    gb.display.setCursor(56, 2);
    gb.display.setColor(GRAY);
    gb.display.print("$");
    gb.display.print(m_Cost);
    gb.display.setCursor(55, 1);
    gb.display.setColor(RED);
    gb.display.print("$");
    gb.display.print(m_Cost);
  }
}

void Menu::DisplayInfo()
{
  // frame
  gb.display.setColor(WHITE);
  gb.display.fillRect(2, 8, 52, 54);
  gb.display.setColor(BLACK);
  gb.display.drawRect(2, 8, 52, 54);
  // Text Citizen
  gb.display.setCursor(4, 10);
  gb.display.print("Citizen ");
  gb.display.setColor(BLUE);
  gb.display.print(m_Info[0]);
  // Text Credit
  gb.display.setCursor(4, 16);
  gb.display.setColor(BLACK);
  gb.display.print("Credit ");
  gb.display.setColor(BLUE);
  gb.display.print(m_Info[1]);
  gb.display.print("$");
  // Text Debit
  gb.display.setCursor(4, 22);
  gb.display.setColor(BLACK);
  gb.display.print("Debit ");
  gb.display.setColor(BLUE);
  gb.display.print(m_Info[2]);
  gb.display.print("$");

}
