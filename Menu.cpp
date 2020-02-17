#include "Menu.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Menu::Menu() :
  m_State(0),
  m_Choice(0),
  m_Position(0),
  m_CursorState(0),
  m_Cost(0),
  m_ButtonBLock(1)
{
  for (uint8_t x = 1; x < NBR_ITEM_MENU + 1; x++)
  {
    m_TileMenu[x - 1] = new Tile(x, 1, 58, ( x * 10 ) + 1, x);
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

//----------------------------------------------------------------------
//                       Display menu methods
//----------------------------------------------------------------------

void Menu::Display()
{
  if (m_Choice == 0)
  {
    m_Choice = INFO;
  }
  gb.display.setColor(WHITE);
  gb.display.fillRect(55, 8, 22, 54);
  gb.display.setColor(BLACK);
  gb.display.drawRect(55, 8, 22, 54);
  SquareSelection();
  for (uint8_t x = 1 + m_Position; x < 6 + m_Position ; x++)
  {
    m_TileMenu[x - 1]->CartY( ((x - m_Position ) * 10 ) + 1);
    m_TileMenu[x - 1]->Display(0);
  }
}

void Menu::SquareSelection()
{
  gb.display.setColor(LIGHTBLUE);
  gb.display.fillRect(57, (10 * (m_Choice - m_Position)), 18, 10);
  if (gb.buttons.pressed(BUTTON_A))
  {
    if ( m_Choice < NBR_ITEM_MENU )
    {
      m_Choice++;
    }
    else
    {
      m_Choice = 1;
      m_Position = 0;
    }
    if ( m_Choice > 5 and m_Choice < NBR_ITEM_MENU + 1 )
    {
      m_Position++;
    }
    gb.sound.fx(SOUND_MENU_1);
    switch (m_Choice)
  {
    case BULL:
      m_Cost = 0;
      break;
    case ROAD_H:
      m_Cost = 50;
      break;
    case HOME_RED:
      m_Cost = 250;
      break;
    case POWER_STATION:
      m_Cost = 1000;
      break;
    case WATER_TOWER:
      m_Cost = 500;
      break;
    case FACTORY:
      m_Cost = 2000;
      break;  
    default:
      m_Cost = 0;
      break;
  }
    DebugMenu();
  }
  if (gb.buttons.pressed(BUTTON_B))
  {
    gb.sound.playOK();
    m_CursorState = true;
    m_ButtonBLock = true;
    m_State = 0;
  }
  if ( m_Choice == BULL or m_Choice == ROAD_H or m_Choice == HOME_RED
       or m_Choice == POWER_STATION or m_Choice == WATER_TOWER or
       m_Choice == FACTORY )
  {
    // Display Texte
    gb.display.setCursor(56, 3);
    gb.display.setColor(GRAY);
    gb.display.print("$");
    gb.display.print(m_Cost);
    gb.display.setCursor(55, 2);
    gb.display.setColor(BLACK);
    gb.display.print("$");
    gb.display.print(m_Cost);
  }
}

void Menu::DebugMenu()
{
  SerialUSB.printf("-----------------------------------------------\n");
  SerialUSB.printf("                 Menu : %i\n", m_State);
  SerialUSB.printf("-----------------------------------------------\n");
  SerialUSB.printf("Number item: %i ,Choice: %i  \n", NBR_ITEM_MENU, m_Choice);
  SerialUSB.printf("Position : %i \n", m_Position);
  SerialUSB.printf("Cursor : %i \n", m_CursorState);
  SerialUSB.printf("Cost : %i \n", m_Cost);
  SerialUSB.printf("-----------------------------------------------\n");
}
