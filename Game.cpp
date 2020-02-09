#include "Game.h"
#include "Image.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

Game::Game () :
  m_Data(true), //avoid unnecessary loops
  m_Language(ENGLISH),
  m_Mode(MENU),
  m_Setting(ENGLISH),
  m_Tutorial(true),
  m_TutorialLevel(1),
  m_Money(4000),
  m_Credit(0),
  m_Debit(0),
  m_Citizen(0),
  m_NbrDay(0)
{
  m_MainMenuEnglish = new MainMenu(MainMenuTextEnglish, 5);
  m_MainMenuFrench = new MainMenu(MainMenuTextFrench, 5);
  m_SettingMenuEnglish = new MainMenu(SettingMenuTextEnglish, 3);
  m_SettingMenuFrench = new MainMenu(SettingMenuTextFrench, 3);
  m_City = new Grid(MAP, MAP_LINE, MAP_COLUMN);
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
  delete m_Time;
}
//----------------------------------------------------------------------
//                       method display Game
//----------------------------------------------------------------------

void Game::Display()
{
  switch (m_Mode)
  {
    case MENU:
      switch (m_Language)
      {
        case ENGLISH:
          m_Mode = m_MainMenuEnglish->GetMode();
          m_MainMenuEnglish->Display();
          break;
        case FRENCH:
          m_Mode = m_MainMenuFrench->GetMode();
          m_MainMenuFrench->Display();
          break;
        default:
          gb.display.setCursor(10, 30);
          gb.display.print("ERROR MAIN MENU");
          break;
      }
      break;
    case NEWGAME:
      m_City->Display();
      // Display the money
      DisplayMoney();
      // show or not the cursor
      DisplayCursor();
      // show or not the menu
      DisplayMenu();
      // Action for info, save
      ChoiceManagement();
      // inactive cursor move map
      if (m_Cursor->State() == false)
      {
        m_City->Move();
      }
      else
      {
        MoveCursor();
        ConstructCursor();
        if ( m_Data )
        {
          // Engine
          m_City->CheckTheTile();
          // information
          UpdateInfo();
          // Desactive
          m_Data = false;
        }
      }
      // Display time
      DisplayTime();
      break;
    case CONTINUE:
      m_Menu->Choice(READ);
      m_Mode = NEWGAME;
      break;
    case TUTORIAL:
      m_Mode = NEWGAME;
      break;
    case SETTING:
      switch (m_Language)
      {
        case ENGLISH:
          m_Setting = m_SettingMenuEnglish->GetMode();
          m_SettingMenuEnglish->Display();
          break;
        case FRENCH:
          m_Setting = m_SettingMenuFrench->GetMode();
          m_SettingMenuFrench->Display();
          break;
        default:
          gb.display.setCursor(10, 30);
          gb.display.print("ERROR MENU SETTING");
          break;
      }
      switch (m_Setting)
      {
        case PAUSE:
          break;
        case ENGLISH:
          m_Language = ENGLISH;
          break;
        case FRENCH:
          m_Language = FRENCH;
          break;
        case EXIT_SETTING:
          // reset objet menu
          m_MainMenuEnglish->SetMode(MENU);
          m_SettingMenuEnglish->SetMode(PAUSE);
          m_MainMenuFrench->SetMode(MENU);
          m_SettingMenuFrench->SetMode(PAUSE);
          m_Mode = MENU;
          break;
        default:
          gb.display.setCursor(10, 30);
          gb.display.print("ERROR MENU SETTING");
          break;
      }
      break;
    case CREDITS:
      m_Mode = NEWGAME;
      break;
    default:
      gb.display.setCursor(10, 30);
      gb.display.print("ERROR MAIN MENU");
      break;
  }


}
void Game::ChoiceManagement()
{
  // Backup management window
  if ( m_Menu->Choice() == INFO and m_Menu->State() == false )
  {
    // frame
    gb.display.setColor(WHITE);
    gb.display.fillRect(2, 8, 76, 54);
    gb.display.setColor(BLACK);
    gb.display.drawRect(2, 8, 76, 54);
    // Text Citizen
    gb.display.setCursor(4, 10);
    gb.display.print("CITIZEN ");
    gb.display.setColor(BLUE);
    gb.display.print(m_Citizen);
    // Text Credit
    gb.display.setCursor(4, 16);
    gb.display.setColor(BLACK);
    gb.display.print(" CREDIT ");
    gb.display.setColor(BLUE);
    gb.display.print(m_Credit);
    gb.display.print(" $");
    // Text Debit
    gb.display.setCursor(4, 22);
    gb.display.setColor(BLACK);
    gb.display.print("  DEBIT ");
    gb.display.setColor(BLUE);
    gb.display.print(m_Debit);
    gb.display.print(" $");
    // Button Exit
    gb.display.setColor(BLACK);
    gb.display.setCursor(28, 52);
    gb.display.print("EXIT");
    gb.display.drawImage(16, 49, IMG_BUTTON_A);
    if (gb.buttons.pressed(BUTTON_A))
    {
      m_Menu->Choice(BULL);
    }
    m_Menu->State(false);
    m_Cursor->State(false);
    m_Menu->CursorState(false);
  }
  // Backup management window
  if ( m_Menu->Choice() == SAVE and m_Menu->State() == false )
  {
    gb.display.setColor(WHITE);
    gb.display.fillRect(2, 20, 76, 20);
    gb.display.setColor(BLACK);
    gb.display.drawRect(2, 20, 76, 20);
    gb.display.setCursor(10, 22);
    gb.display.print("Save the city ?");
    gb.display.setCursor(28, 31);
    gb.display.print("YES");
    gb.display.drawImage(16, 28, IMG_BUTTON_A);
    gb.display.setCursor(58, 31);
    gb.display.print("NO");
    gb.display.drawImage(46, 28, IMG_BUTTON_B);
    if (gb.buttons.pressed(BUTTON_A))
    {
      m_Menu->CursorState(false);
      m_Menu->State(false);
      // Save game
      Memory(MEM_SAVE);
      m_Menu->Choice(BULL);
    }
    if (gb.buttons.pressed(BUTTON_B))
    {
      if (m_Menu->ButtonBLock() == false)
      {
        m_Menu->Choice(BULL);
        m_Menu->CursorState(false);
        m_Menu->State(false);
      }
      m_Menu->ButtonBLock(false);
    }
    m_Cursor->State(false);
  }
  // Backup playback management window
  if ( m_Menu->Choice() == READ and m_Menu->State() == false )
  {
    gb.display.setColor(WHITE);
    gb.display.fillRect(2, 14, 76, 30);
    gb.display.setColor(BLACK);
    gb.display.drawRect(2, 14, 76, 30);
    gb.display.setCursor(4, 17);
    gb.display.print("Use the city save?");
    gb.display.setCursor(28, 27);
    gb.display.print("YES");
    gb.display.drawImage(16, 24, IMG_BUTTON_A);
    gb.display.setCursor(58, 27);
    gb.display.print("NO");
    gb.display.drawImage(46, 24, IMG_BUTTON_B);
    if (gb.buttons.pressed(BUTTON_A))
    {
      m_Menu->Choice(BULL);
      m_Menu->CursorState(false);
      m_Menu->State(false);
      // Read game
      Memory(MEM_READ);
      // Engine
      m_City->CheckTheTile();
      // information
      UpdateInfo();
    }
    if (gb.buttons.released(BUTTON_B))
    {
      if (m_Menu->ButtonBLock() == false)
      {
        m_Menu->Choice(BULL);
        m_Menu->CursorState(false);
        m_Menu->State(false);
      }
      m_Menu->ButtonBLock(false);
    }
    m_Cursor->State(false);
  }
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
      if ( m_Money > Cost and Choise != BULL )
      {
        // check if there are not already constructions
        if ( (CityTile == SAND  ) or
             (CityTile == GRASS  ) )
        {
          // Construct the new tile
          m_City->Type(i, j, Choise );
          m_Money = m_Money - Cost;
          gb.sound.fx(SOUND_CONST);
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
        if ( Choise != BULL )
        {
          Message("    NO MONEY");
        }
      }
      // destroyed and replaced by sand
      if ( CityTile != SEA and Choise == BULL )
      {
        m_City->Type(i, j, SAND );
        m_City->ResetError(i, j);
        gb.sound.fx(SOUND_BULL);
      }
      m_Data = true;
    }
  }
}
//----------------------------------------------------------------------
//                   update city information
//----------------------------------------------------------------------
void Game::UpdateInfo()
{
  // reset information variables
  m_Citizen = 0;
  m_Credit = 0;
  m_Debit = 0;
  uint8_t CityTile = m_City->Type(0, 0);
  for ( uint8_t Y = 0 ; Y < MAP_LINE; Y++)
  {
    for ( uint8_t X = 0 ; X < MAP_COLUMN; X++)
    {
      CityTile = m_City->Type(X, Y);
      switch ( CityTile )
      {
        case HOME_RED:
          SerialUSB.printf("HOME RED X = %i - Y = %i \n", X , Y);
          if ( m_City->Error(X, Y) == 0 )
          {
            m_Citizen = m_Citizen + 4;
            m_Credit = m_Credit + 50;
          }
          break;
        case ROAD:
        case ROAD_DL:
        case ROAD_DR:
        case ROAD_H:
        case ROAD_INT:
        case ROAD_INT_DOWN:
        case ROAD_INT_LEFT:
        case ROAD_INT_RIGHT:
        case ROAD_INT_UP:
        case ROAD_UL:
        case ROAD_UR:
        case ROAD_V:
          SerialUSB.printf("ROAD X = %i - Y = %i \n", X , Y);
          m_Debit = m_Debit + 5;
          break;
        case POWER_STATION:
          SerialUSB.printf("POWER STATION X = %i - Y = %i \n", X , Y);
          m_Debit = m_Debit + 200;
          break;
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
    if (m_Menu->State() == false)
    {
      m_Menu->Choice(BULL);
    }
  }
  if (m_Menu->State() == true)
  {
    m_Menu->Display();
    m_Cursor->State(false);
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
  if (m_Menu->CursorState() == true and m_Menu->State() == false )
  {
    m_Cursor->State(true);
  }
  else
  {
    m_Menu->CursorState() == false;
    m_Cursor->State(false);
  }
  if (m_Cursor->State() == true )
  {
    m_Cursor->CameraX(m_City->CameraX());
    m_Cursor->CameraY(m_City->CameraY());
    m_Cursor->Choice(m_Menu->Choice());
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
  uint8_t MoveCameraX = m_City->CameraX();
  uint8_t MoveCameraY = m_City->CameraY();
  // multiple of 8
  MoveCameraX = MoveCameraX / TILE_WIDTH;
  MoveCameraY = MoveCameraY / TILE_HEIGHT;
  MoveCameraX = MoveCameraX * TILE_WIDTH;
  MoveCameraY = MoveCameraY * TILE_HEIGHT;
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
      // limit right
      ( Line == Line and Column == (Line + 4) ) or
      ( Line == Line and Column == (Line + 5) ) or
      // limit up
      ( Line == Line and Column == (4 - Line ) ) or
      ( Line == Line and Column == (5 - Line ) )
    )
    {
      if ( MoveCameraX < LIMIT_RIGHT and  MoveCameraY > LIMIT_UP )
      {
        m_City->CameraY( MoveCameraY - 8 );
        IMG_ARROW_RIGHT_UP();
      }
      else
      {
        IMG_NO_ENTRY(70, 10);
      }
    }
    else
    {
      IMG_ARROW_RIGHT_UP();
      m_Cursor->ViewLine(Line - 1);
      // deactivates movements to avoid repetition
      RightButtonState = 0;
      UpButtonState = 0;
    }
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED RIGHT AND UP \n");
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and gb.buttons.pressed(BUTTON_UP))
  {
    // control the left edge of the screen
    if
    (
      // limit left
      ( Line == Line and Column == (Line - 4) ) or
      ( Line == Line and Column == (Line - 5) ) or
      // limit up
      ( Line == Line and Column == (4 - Line ) ) or
      ( Line == Line and Column == (5 - Line ) )
    )
    {
      if (MoveCameraX > LIMIT_LEFT and MoveCameraY > LIMIT_UP )
      {
        m_City->CameraX( MoveCameraX - 8);
        IMG_ARROW_LEFT_UP();
      }
      else
      {
        IMG_NO_ENTRY(10, 10);
      }
    }
    else
    {
      IMG_ARROW_LEFT_UP();
      m_Cursor->ViewColumn(Column - 1);
      // deactivates movements to avoid repetition
      LeftButtonState = 0;
      UpButtonState = 0;
    }
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED LEFT AND UP \n");
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
  }
  if (gb.buttons.pressed(BUTTON_RIGHT) and gb.buttons.pressed(BUTTON_DOWN))
  {
    if
    (
      // limit right
      ( Line == Line and Column == (Line + 4) ) or
      ( Line == Line and Column == (Line + 5) ) or
      // limit down
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
      if (MoveCameraX < LIMIT_RIGHT and MoveCameraY < LIMIT_DOWN )
      {
        m_City->CameraX( MoveCameraX + 8);
        IMG_ARROW_RIGHT_DOWN();
      }
      else
      {
        IMG_NO_ENTRY(70, 55);
      }
    }
    else
    {
      IMG_ARROW_RIGHT_DOWN();
      m_Cursor->ViewColumn(Column + 1);
      // deactivates movements to avoid repetition
      RightButtonState = 0;
      DownButtonState = 0;
    }
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED RIGHT AND DOWN \n");
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
  }
  if (gb.buttons.pressed(BUTTON_LEFT) and gb.buttons.pressed(BUTTON_DOWN))
  {
    if
    (
      // limit left
      ( Line == Line and Column == (Line - 4) ) or
      ( Line == Line and Column == (Line - 5) ) or
      // limit down
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
      if (MoveCameraX > LIMIT_LEFT and MoveCameraY < LIMIT_DOWN )
      {
        m_City->CameraY( MoveCameraY + 8);
        IMG_ARROW_LEFT_DOWN();
      }
      else
      {
        IMG_NO_ENTRY(10, 55);
      }
    }
    else
    {
      IMG_ARROW_LEFT_DOWN();
      m_Cursor->ViewLine(Line + 1);
      // deactivates movements to avoid repetition
      LeftButtonState = 0;
      DownButtonState = 0;
    }
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED LEFT AND DOWN \n");
    SerialUSB.printf("____________________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
  }
  //--------------------------------------------------------------------
  // classic movements and control
  //--------------------------------------------------------------------
  //
  // right move cartesian -->
  //
  if (gb.buttons.pressed(BUTTON_RIGHT) and RightButtonState == 1 )
  {
    // right screen limit
    if
    (
      ( Line == Line and Column == (Line + 4) ) or
      ( Line == Line and Column == (Line + 5) )
    )
    {
      if ( MoveCameraX < LIMIT_RIGHT )
      {
        m_City->CameraX( MoveCameraX + 8 );
        if ( MoveCameraY > LIMIT_UP )
        {
          m_City->CameraY( MoveCameraY - 8 );
        }
        IMG_ARROW_RIGHT();
      }
      else
      {
        IMG_NO_ENTRY(70, 30);
      }
    }
    // move inside the screen
    else
    {
      IMG_ARROW_RIGHT();
      m_Cursor->ViewColumn(Column + 1);
      m_Cursor->ViewLine(Line - 1);
    }
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED RIGHT  \n");
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
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
      if (MoveCameraX > LIMIT_LEFT )
      {
        m_City->CameraX( MoveCameraX - 8);
        if ( MoveCameraY < LIMIT_DOWN )
        {
          m_City->CameraY( MoveCameraY + 8);
        }
        IMG_ARROW_LEFT();
      }
      else
      {
        IMG_NO_ENTRY(10, 30);
      }
    }
    else
    {
      IMG_ARROW_LEFT();
      m_Cursor->ViewColumn(Column - 1);
      m_Cursor->ViewLine(Line + 1);
    }
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED LEFT  \n");
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
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
      if (MoveCameraY > LIMIT_UP )
      {
        m_City->CameraY( MoveCameraY - 8);
        if ( MoveCameraX > LIMIT_LEFT)
        {
          m_City->CameraX( MoveCameraX - 8);
        }
        IMG_ARROW_UP();
      }
      else
      {
        IMG_NO_ENTRY(40, 5);
      }
    }
    else
    {
      IMG_ARROW_UP();
      m_Cursor->ViewColumn(Column - 1);
      m_Cursor->ViewLine(Line - 1);
    }
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED UP  \n");
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
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
      if (MoveCameraY < LIMIT_DOWN )
      {
        m_City->CameraY( MoveCameraY + 8);
        if ( MoveCameraX < LIMIT_RIGHT)
        {
          m_City->CameraX( MoveCameraX + 8);
        }
        IMG_ARROW_DOWN();
      }
      else
      {
        IMG_NO_ENTRY(40, 55);
      }

    }
    else
    {
      IMG_ARROW_DOWN();
      m_Cursor->ViewColumn(Column + 1);
      m_Cursor->ViewLine(Line + 1);
    }
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("TILE MOVE : PRESSED DOWN  \n");
    SerialUSB.printf("______________________________\n");
    SerialUSB.printf("CAMERA : X = %i - Y = %i \n", MoveCameraX, MoveCameraY );
    SerialUSB.printf("TILE : Line = %i - Column = %i \n", Line, Column );
  }
}

//----------------------------------------------------------------------
//         displays the currency and the days at the top left
//----------------------------------------------------------------------


void Game::DisplayMoney()
{
  switch (m_Language)
  {
    case ENGLISH:
      gb.display.setCursor(4, 2);
      gb.display.setColor(GRAY);
      gb.display.print("$ ");
      gb.display.print(m_Money);
      gb.display.print(" DAY ");
      gb.display.print(m_NbrDay);
      gb.display.setCursor(3, 1);
      gb.display.setColor(WHITE);
      gb.display.print("$ ");
      gb.display.print(m_Money);
      gb.display.print(" DAY ");
      gb.display.print(m_NbrDay);
      break;
    case FRENCH:
      gb.display.setCursor(4, 2);
      gb.display.setColor(GRAY);
      gb.display.print("E ");
      gb.display.print(m_Money);
      gb.display.print(" JOUR ");
      gb.display.print(m_NbrDay);
      gb.display.setCursor(3, 1);
      gb.display.setColor(WHITE);
      gb.display.print("E ");
      gb.display.print(m_Money);
      gb.display.print(" JOUR ");
      gb.display.print(m_NbrDay);
      break;
    default:
      gb.display.print("ERROR TEXT DAY");
      break;
  }
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

//----------------------------------------------------------------------
//                     Save Data Game
//----------------------------------------------------------------------

void Game::Memory(uint8_t Memory_Action)
{
  uint8_t buffer[30] = { 0 };
  switch (Memory_Action)
  {
    case MEM_SAVE:
      gb.display.setColor(WHITE);
      gb.display.fillRect(2, 20, 76, 20);
      gb.display.setColor(BLACK);
      gb.display.drawRect(2, 20, 76, 20);
      gb.display.setCursor(4, 23);
      gb.display.print("BACKUP IN PROGRESS");
      SerialUSB.printf("______________________________\n");
      SerialUSB.printf("GAME SAVE \n");
      SerialUSB.printf("______________________________\n");
      for (uint8_t Line = 0; Line < 30; Line++)
      {
        SerialUSB.printf("LINE %i : ", Line);
        for (uint16_t Column = Line * 30; Column < 30 + (Line * 30); Column++)
        {
          //buffer[i-(y*30)]=MAP[i];
          buffer[Column - (Line * 30)] = m_City->Type(Column - (Line * 30), Line);
          SerialUSB.printf("%i ", buffer[Column - (Line * 30)]);
        }
        SerialUSB.printf("\n");
        gb.save.del(Line);
        gb.save.set(Line, buffer, 30);
        gb.display.setColor(RED);
        gb.display.fillRect(5, 30, 2.4 * Line, 6);
        delay(1);
      }
      gb.save.del(30);
      gb.save.set(30, m_Money);
      gb.save.del(31);
      gb.save.set(31, m_NbrDay);

      break;
    case MEM_READ:
      SerialUSB.printf("______________________________\n");
      SerialUSB.printf("GAME RESTORED  \n");
      SerialUSB.printf("______________________________\n");
      for (uint8_t Line = 0; Line < 30; Line++)
      {
        SerialUSB.printf("LINE %i : ", Line);
        gb.save.get(Line, buffer, 30);
        for (uint16_t Column = Line * 30; Column < 30 + (Line * 30); Column++)
        {
          m_City->Type(Column - (Line * 30), Line, buffer[Column - (Line * 30)]);
        }
        gb.display.setColor(RED);
        gb.display.fillRect(5, 35, 2.4 * Line, 6);
        delay(20);
      }
      m_Money = gb.save.get(30);
      m_NbrDay = gb.save.get(31);

      break;
  }
}
