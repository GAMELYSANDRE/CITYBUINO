#include "Game.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

Game::Game ()
{
  m_City = new Grid(Map, MAP_LINE, MAP_COLUMN);
  m_Menu = new Menu();
  m_Cursor = new Cursor();
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

void Game::DisplayCursor()
{
  if (m_Menu->CursorState())
  {
    m_Cursor->State(true);
    m_Cursor->CameraX(m_City->CameraX());
    m_Cursor->CameraY(m_City->CameraY());
    m_Cursor->Choice(m_Menu->Choice());
  }
  if (m_Cursor->State() == true)
  {
    m_Cursor->Display();
  }
}

void Game::MoveCursor()
{
  // exit mode construction
  if (gb.buttons.pressed(BUTTON_B))
  {
    m_Menu->CursorState(false);
    m_Cursor->State(false);
  }
  // Movements
  uint16_t Column = m_Cursor->Column();
  uint16_t Line = m_Cursor->Line();
  bool RightButtonState = 1;
  bool LeftButtonState = 1;
  bool UpButtonState = 1;
  bool DownButtonState = 1;
  // diagonal movements
  if (gb.buttons.pressed(BUTTON_RIGHT) and gb.buttons.pressed(BUTTON_UP))
  {
    m_Cursor->Line(Line-1);
    RightButtonState = 0;
    UpButtonState = 0;
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and gb.buttons.pressed(BUTTON_UP))
  {
    m_Cursor->Column(Column-1);
    LeftButtonState = 0;
    UpButtonState = 0;
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and gb.buttons.pressed(BUTTON_DOWN))
  {
    m_Cursor->Line(Line+1);
    LeftButtonState = 0;
    DownButtonState = 0;
  }
  if (gb.buttons.pressed(BUTTON_RIGHT) and gb.buttons.pressed(BUTTON_DOWN))
  {
    m_Cursor->Column(Column+1);
    RightButtonState = 0;
    DownButtonState = 0;
  }
  // classic movements and control
  if (gb.buttons.pressed(BUTTON_RIGHT) and RightButtonState == 1 )
  {
    if ( Line == Line and Column == (Line + 4) )
    {
      gb.display.setColor(BLACK);
      gb.display.fillRect(0, 0, 80, 65);
      gb.sound.playTick();
    }
    else
    { 
      m_Cursor->Column(Column+1);
      m_Cursor->Line(Line-1);
    }  
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and LeftButtonState == 1)
  {
    if ( Line == Line and Column == (Line - 4) )
    {
      gb.display.setColor(BLACK);
      gb.display.fillRect(0, 0, 80, 65);
      gb.sound.playTick();
    }
    else
    {  
      m_Cursor->Column(Column-1);
      m_Cursor->Line(Line+1);
    }  
  }
  if (gb.buttons.pressed(BUTTON_DOWN) and DownButtonState == 1)
  {
    m_Cursor->Column(Column+1);
    m_Cursor->Line(Line+1);
  }
  if (gb.buttons.pressed(BUTTON_UP) and UpButtonState == 1)
  {
    m_Cursor->Column(Column-1);
    m_Cursor->Line(Line-1);
  }
  gb.display.print(Line);
  gb.display.print(" - ");
  gb.display.print(Column);
}
