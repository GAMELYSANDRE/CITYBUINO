#include "Game.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

Game::Game () :
  m_Money(4000),
  m_Credit(0),
  m_Debit(0),
  m_Citizen(0),
  m_NbrDay(0)
{
  m_City = new Grid(Map, MAP_LINE, MAP_COLUMN);
  m_Menu = new Menu();
  m_Cursor = new Cursor();
  m_Time = new GBTime();
}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Game::~Game()
{
  delete m_City;
  delete m_Menu;
  delete m_Cursor;
}
//----------------------------------------------------------------------
//                       method display Game
//----------------------------------------------------------------------

void Game::Display()
{
  m_City->Display();
  // show or not the cursor
  DisplayCursor();
  // show or not the menu
  DisplayMenu();
  // inactive cursor move map
  if (m_Cursor->State() == false)
  {
    m_City->Move();
  }
  else
  {
    MoveCursor();
    ConstructCursor();
    // Engine
    m_City->CheckTheTile();
  }
  // Display the money
  DisplayMoney();
  // Display time
  DisplayTime();

}

void Game::ConstructCursor()
{
  uint8_t i = m_Cursor->GridLine();
  uint8_t j = m_Cursor->GridColumn();
  uint8_t Choise = m_Cursor->Choice();
  uint8_t Cost = m_Menu->Cost();
  uint8_t CityTile = m_City->Type(i, j);
  // disable the a button if the menu is visible
  if (m_Menu->State() == false)
  {
    if (gb.buttons.pressed(BUTTON_A) )
    {
      // check the money
      if ( m_Money > Cost)
      {
        // check if there are not already constructions
        if ( (CityTile == SAND and Choise != BULL ) or 
             (CityTile == GRASS and Choise != BULL ) )
        {
          // Construct the new tile
            m_City->Type(i, j, Choise );
            m_Money = m_Money - Cost;
            gb.sound.fx(SOUND_CONST);
            switch ( Choise )
            {
              case HOME_RED:
                m_Citizen = m_Citizen + 4;
                m_Credit = m_Credit + 50;
                break;
              case ROAD_H:
              case ROAD_V:
                m_Debit = m_Debit + 5;
                break;
              case POWER_STATION:
                m_Debit = m_Debit + 100;
            }
        }
        else
        {
          if ( CityTile == SEA )
          {
            Message("NOT IN TNE WATER");
          }
          else
          {
            Message("PRESENT CONSTRUCT.");
          }
        }
        
      }
      else
      {
        Message("    NO MONEY");
      }
      // destroyed and replaced by sand
      if ( CityTile != SEA and Choise == BULL )
      {
            m_City->Type(i, j, SAND );
            m_City->ResetError(i, j);
            gb.sound.fx(SOUND_BULL);
            switch ( CityTile )
            {
              case HOME_RED:
                m_Citizen = m_Citizen - 4;
                m_Credit = m_Credit - 50;
                break;
              case ROAD_H:
                m_Debit = m_Debit - 5;
                break;
              case POWER_STATION:
                m_Debit = m_Debit - 100;  
            }
      }
    }
  }


}

//----------------------------------------------------------------------
//                 make appear and disappear the menu
//----------------------------------------------------------------------

void Game::DisplayMenu()
{
  if (gb.buttons.pressed(BUTTON_MENU))
  {
    m_Menu->State(!m_Menu->State());
  }
  if (m_Menu->State())
  {
    m_Menu->Display();
  }
}

//----------------------------------------------------------------------
//                          display a message
//----------------------------------------------------------------------

void Game::Message( char TextMessage[18] )
{
  gb.sound.fx(SOUND_ERROR);
  gb.display.setColor(RED);
  gb.display.fillRect(2, 20, 76, 20);
  gb.display.setColor(BLACK);
  gb.display.drawRect(2, 20, 76, 20);
  gb.display.setColor(WHITE);
  gb.display.setCursor(30, 23);
  gb.display.print("ERROR !");
  gb.display.setCursor(6, 30);
  gb.display.print(TextMessage);
  delay(1000);
}


//----------------------------------------------------------------------
//                        show cursor
//----------------------------------------------------------------------

void Game::DisplayCursor()
{
  if (m_Menu->CursorState())
  {
    m_Cursor->State(true);
    m_Cursor->CameraX(m_City->CameraX());
    m_Cursor->CameraY(m_City->CameraY());
    m_Cursor->Choice(m_Menu->Choice());
  }
  if (m_Cursor->State() == true and m_Cursor->Choice() != INFO )
  {
    m_Cursor->Display();
  }
}

//----------------------------------------------------------------------
//        move the cursor and limit it to the screen edges
//----------------------------------------------------------------------

void Game::MoveCursor()
{
  // exit mode construction
  if (gb.buttons.pressed(BUTTON_B) )
  {
    if (m_Menu->ButtonBLock() == false)
    {
      m_Menu->CursorState(false);
      m_Cursor->State(false);
    }
    m_Menu->ButtonBLock(false);
  }
  // Movements
  uint16_t Column = m_Cursor->ViewColumn();
  uint16_t Line = m_Cursor->ViewLine();
  bool RightButtonState = 1;
  bool LeftButtonState = 1;
  bool UpButtonState = 1;
  bool DownButtonState = 1;
  //
  // diagonal movements
  //
  if (gb.buttons.pressed(BUTTON_RIGHT) and gb.buttons.pressed(BUTTON_UP))
  {
    if
    (
      ( Line == Line and Column == (Line + 4) ) or
      ( Line == Line and Column == (Line + 5) )
    )
    {
      ErrorCursor();
    }
    else
    {
      m_Cursor->ViewLine(Line - 1);
      // deactivates movements to avoid repetition
      RightButtonState = 0;
      UpButtonState = 0;
    }
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and gb.buttons.pressed(BUTTON_UP))
  {
    // control the left edge of the screen
    if
    (
      ( Line == Line and Column == (Line - 4) ) or
      ( Line == Line and Column == (Line - 5) )
    )
    {
      ErrorCursor();
    }
    else
    {
      m_Cursor->ViewColumn(Column - 1);
      // deactivates movements to avoid repetition
      LeftButtonState = 0;
      UpButtonState = 0;
    }
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and gb.buttons.pressed(BUTTON_DOWN))
  {
    m_Cursor->ViewLine(Line + 1);
    // deactivates movements to avoid repetition
    LeftButtonState = 0;
    DownButtonState = 0;
  }
  if (gb.buttons.pressed(BUTTON_RIGHT) and gb.buttons.pressed(BUTTON_DOWN))
  {
    m_Cursor->ViewColumn(Column + 1);
    // deactivates movements to avoid repetition
    RightButtonState = 0;
    DownButtonState = 0;
  }
  //
  // classic movements and control
  //

  //
  // right move cartesian -->
  //
  if (gb.buttons.pressed(BUTTON_RIGHT) and RightButtonState == 1 )
  {
    //
    if
    (
      ( Line == Line and Column == (Line + 4) ) or
      ( Line == Line and Column == (Line + 5) )
    )
    {
      ErrorCursor();
    }
    else
    {
      m_Cursor->ViewColumn(Column + 1);
      m_Cursor->ViewLine(Line - 1);
    }
  }
  //
  // left move cartesian <--
  //
  if (gb.buttons.pressed(BUTTON_LEFT) and LeftButtonState == 1)
  {
    // control the left edge of the screen
    if
    (
      ( Line == Line and Column == (Line - 4) ) or
      ( Line == Line and Column == (Line - 5) )
    )
    {
      ErrorCursor();
    }
    else
    {
      m_Cursor->ViewColumn(Column - 1);
      m_Cursor->ViewLine(Line + 1);
    }
  }
  //                        I
  // down move cartesian    I
  //                        V
  if (gb.buttons.pressed(BUTTON_DOWN) and DownButtonState == 1)
  {
    if
    (
      ( Line == 11 and Column == 7 ) or
      ( Line == 10 and Column == 8 ) or
      ( Line == 9 and Column == 9 ) or
      ( Line == 8 and Column == 10 ) or
      ( Line == 7 and Column == 11 ) or
      // ----------------------------------
      ( Line == 12 and Column == 7 ) or
      ( Line == 11 and Column == 8 ) or
      ( Line == 10 and Column == 9 ) or
      ( Line == 9 and Column == 10 ) or
      ( Line == 8 and Column == 11 ) or
      ( Line == 7 and Column == 12 )
    )
    {
      ErrorCursor();
    }
    else
    {
      m_Cursor->ViewColumn(Column + 1);
      m_Cursor->ViewLine(Line + 1);
    }
  }
  //
  // up move cartesian
  //
  if (gb.buttons.pressed(BUTTON_UP) and UpButtonState == 1)
  {
    if
    (
      ( Line == Line and Column == (4 - Line ) ) or
      ( Line == Line and Column == (5 - Line ) )
    )
    {
      ErrorCursor();
    }
    else
    {
      m_Cursor->ViewColumn(Column - 1);
      m_Cursor->ViewLine(Line - 1);
    }

  }
}

//----------------------------------------------------------------------
//                     cursor screen output
//----------------------------------------------------------------------

void Game::ErrorCursor()
{
  gb.display.setColor(BLACK);
  gb.display.fillRect(0, 0, 80, 65);
  gb.sound.playTick();

}

void Game::DisplayMoney()
{
  gb.display.setCursor(4, 2);
  gb.display.setColor(GRAY);
  gb.display.print("$ ");
  gb.display.print(m_Money);

  gb.display.print(" DY ");
  gb.display.print(m_NbrDay);

  gb.display.setCursor(3, 1);
  gb.display.setColor(WHITE);
  gb.display.print("$ ");
  gb.display.print(m_Money);

  gb.display.print(" DY ");
  gb.display.print(m_NbrDay);

  m_Menu->Citizen(m_Citizen);
  m_Menu->Credit(m_Credit);
  m_Menu->Debit(m_Debit);
}

//----------------------------------------------------------------------
//                    manage city information
//----------------------------------------------------------------------
void Game::ManageInfo()
{

}  


//----------------------------------------------------------------------
//                     management of time
//----------------------------------------------------------------------

void Game::DisplayTime()
{
  m_Time->InitBeginTime();
  m_Time->IncrementTime();
  // add a day after the delay
  if ( m_Time->TempTime() > ( DELAY_MONEY * 1000 ) )
  {
    m_NbrDay++;
    m_Time->Reset();
    m_Money = m_Money + m_Credit - m_Debit;
  }
}
