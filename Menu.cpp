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
    m_TileMenu[x - 1] = new Tile(x, 1, 60, ( x * 10 ) + 1, x);
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
bool Menu::getState() const
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

//----------------------------------------------------------------------
//                       Display menu methods
//----------------------------------------------------------------------

void Menu::Display(uint8_t Language)
{
  m_Language = Language;
  if (m_Choice == 0)
  {
    m_Choice = INFO;
  }
  // adjusts the size of the menu
  uint8_t MenuHeight = 0;
  uint8_t MenuPosY = 0;
  for (uint8_t x = 0 + m_Position; x < 5 + m_Position ; x++)
  {
    MenuHeight += ITEM_MENU_HEIGHT[x];
  }
  MenuHeight += 4;
  gb.display.setColor(WHITE);
  gb.display.fillRect(57, 2, 22, MenuHeight);
  gb.display.setColor(BLACK);
  gb.display.drawRect(57, 2, 22, MenuHeight);
  for (uint8_t x = 1 + m_Position; x < 6 + m_Position ; x++)
  {
    MenuPosY += ITEM_MENU_HEIGHT[ x - 1];
    if ( m_Choice == x )
    {
      // Display square
      Square(MenuPosY - ( ITEM_MENU_HEIGHT[ x - 1] - 4 ), ITEM_MENU_HEIGHT[x - 1] );
      // Display text cost
      TextCost(MenuPosY - ( ITEM_MENU_HEIGHT[ x - 1] - 8 ));
    }
    m_TileMenu[x - 1]->CartY( MenuPosY - 5 );
    m_TileMenu[x - 1]->Display(0);
  }
  Selection();
}
void Menu::Square(uint8_t Y, uint8_t Height )
{
  gb.display.setColor(LIGHTBLUE);
  gb.display.fillRect(59, Y , 18, Height);
}

void Menu::TextCost(uint8_t Y)
{
  gb.display.setCursor(4, 10);
  gb.display.setColor(GRAY);
  switch ( m_Choice)
  {
    case INFO:
      gb.display.print("INFORMATION");
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print("INFORMATION");
      break;
    case SAVE:
      gb.display.print(TranslateSave[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslateSave[m_Language]);
      break;
    case LOAD:
      gb.display.print(TranslateRestore[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslateRestore[m_Language]);
      break;
    case BULL:
      gb.display.print("BULLDOZER");
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print("BULLDOZER");
      break;
    case ROAD_H:
      gb.display.print(TranslateRoad[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslateRoad[m_Language]);
      break;
    case HOME_RED:
      gb.display.print(TranslateHome[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslateHome[m_Language]);
      break;
    case POWER_STATION:
      gb.display.print(TranslatePowerStation[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslatePowerStation[m_Language]);
      break;
    case WATER_TOWER:
      gb.display.print(TranslateWaterTower[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslateWaterTower[m_Language]);
      break;
    case FACTORY:
      gb.display.print(TranslateFactory[m_Language]);
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print(TranslateFactory[m_Language]);
      break;
    case UPDATE:
      gb.display.print("EVOLUTION");
      gb.display.setCursor(3, 9);
      gb.display.setColor(WHITE);
      gb.display.print("EVOLUTION");
      break;
    default:
      break;
  }
  if ( m_Choice == BULL or m_Choice == ROAD_H or m_Choice == HOME_RED
       or m_Choice == POWER_STATION or m_Choice == WATER_TOWER or
       m_Choice == FACTORY )
  {
    gb.display.setCursor(4, 17);
    gb.display.setColor(GRAY);
    gb.display.print(TranslateCost[m_Language]);
    gb.display.print(m_Cost);
    gb.display.print("$");
    gb.display.setCursor(3, 16);
    gb.display.setColor(WHITE);
    gb.display.print(TranslateCost[m_Language]);
    gb.display.print(m_Cost);
    gb.display.print("$");
  }
}

void Menu::Selection()
{
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
    else
    {
      m_Position = 0;
    }
    gb.sound.fx(SOUND_MENU_1);
    switch (m_Choice)
    {
      case BULL:
        m_Cost = 0;
        break;
      case ROAD_H:
        m_Cost = COST_ROAD;
        break;
      case HOME_RED:
        m_Cost = COST_HOME_RED;
        break;
      case POWER_STATION:
        m_Cost = COST_POWER_STATION;
        break;
      case WATER_TOWER:
        m_Cost = COST_WATER_TOWER;
        break;
      case FACTORY:
        m_Cost = COST_FACTORY;
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
