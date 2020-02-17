#include "Game.h"
#include "Image.h"
//----------------------------------------//
//   external file to separate the code   //
//----------------------------------------//
#include "GameCursor.h"
#include "GameDisplay.h"

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
  m_Money(10000),
  m_NbrDay(0),
  m_Credit(0),
  m_Debit(0),
  m_Citizen(0),
  m_Job(0)
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
      // Action for info, save, read
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
      m_Menu->Choice(LOAD);
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

//----------------------------------------------------------------------
//         management of specific menu actions
//----------------------------------------------------------------------

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
    gb.display.print(TranslateCitizen[m_Language]);
    gb.display.setColor(BLUE);
    gb.display.print(m_Citizen);
    // Text Credit
    gb.display.setCursor(4, 16);
    gb.display.setColor(BLACK);
    gb.display.print(" CREDIT ");
    gb.display.setColor(BLUE);
    gb.display.print(m_Credit);
    gb.display.print(TranslateSymbMoney[m_Language]);
    // Text Debit
    gb.display.setCursor(4, 22);
    gb.display.setColor(BLACK);
    gb.display.print("  DEBIT ");
    gb.display.setColor(BLUE);
    gb.display.print(m_Debit);
    gb.display.print(TranslateSymbMoney[m_Language]);
    // Text Job
    gb.display.setCursor(4, 28);
    gb.display.setColor(BLACK);
    gb.display.print("    JOB ");
    gb.display.setColor(BLUE);
    gb.display.print(m_Job);
    // Button Exit
    gb.display.setColor(BLACK);
    gb.display.setCursor(40, 51);
    gb.display.print(TranslateMenuInfo[m_Language]);
    gb.display.drawImage(28, 48, IMG_BUTTON_A);
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
    gb.display.setCursor(4, 22);
    gb.display.print(TranslateBackupQuestion[m_Language]);
    gb.display.setCursor(28, 31);
    gb.display.print(TranslateYes[m_Language]);
    gb.display.drawImage(16, 28, IMG_BUTTON_A);
    gb.display.setCursor(58, 31);
    gb.display.print(TranslateNo[m_Language]);
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
  if ( m_Menu->Choice() == LOAD and m_Menu->State() == false )
  {
    gb.display.setColor(WHITE);
    gb.display.fillRect(2, 14, 76, 30);
    gb.display.setColor(BLACK);
    gb.display.drawRect(2, 14, 76, 30);
    gb.display.setCursor(4, 17);
    gb.display.print(TranslateLoadQuestion[m_Language]);
    gb.display.setCursor(28, 27);
    gb.display.print(TranslateYes[m_Language]);
    gb.display.drawImage(16, 24, IMG_BUTTON_A);
    gb.display.setCursor(58, 27);
    gb.display.print(TranslateNo[m_Language]);
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

//----------------------------------------------------------------------
//                   update city information
//----------------------------------------------------------------------
void Game::UpdateInfo()
{
  // reset information variables
  m_Citizen = 0;
  m_Credit = 0;
  m_Debit = 0;
  m_Job = 0;
  uint8_t CityTile = m_City->Type(0, 0);
  for ( uint8_t Y = 0 ; Y < MAP_LINE; Y++)
  {
    for ( uint8_t X = 0 ; X < MAP_COLUMN; X++)
    {
      CityTile = m_City->Type(X, Y);
      switch ( CityTile )
      {
        case FACTORY:
          m_Job = m_Job + 20;
          break;
        case HOME_RED:
          SerialUSB.printf("HOME RED X = %i - Y = %i \n", X , Y);
          if ( m_City->Error(X, Y) == 0 )
          {
            m_Citizen = m_Citizen + 2;
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
          m_Debit = m_Debit + 2;
          break;
        case POWER_STATION:
          SerialUSB.printf("POWER STATION X = %i - Y = %i \n", X , Y);
          m_Debit = m_Debit + 200;
          break;
        case WATER_TOWER:
          SerialUSB.printf("WATER_TOWER X = %i - Y = %i \n", X , Y);
          m_Debit = m_Debit + 50;
          break;
        default:
          break;
      }
    }
  }
  // compares citizens and work
  uint16_t SaveJob = m_Job;
  for ( uint8_t Y = 0 ; Y < MAP_LINE; Y++)
  {
    for ( uint8_t X = 0 ; X < MAP_COLUMN; X++)
    {
      CityTile = m_City->Type(X, Y);
      if ( CityTile == HOME_RED )
      {
        if ( m_Job == 0 )
        {
          m_City->Error(X, Y, ERROR_JOB);
          m_Citizen = m_Citizen - 2;
          m_Credit = m_Credit - 50;
        }
        else
        {
          m_Job = m_Job - 2;
        }
      }
    }
  }
  m_Job = SaveJob;
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
      gb.display.print(TranslateBackupAction[m_Language]);
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
