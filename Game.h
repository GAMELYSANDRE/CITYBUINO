#ifndef __GAME__
#define __GAME__
#include <Gamebuino-Meta.h>
#include "Constant.h"
#include "Language.hpp"
#include "Tile.h"
#include "MainMenu.h"
#include "Grid.h"
#include "Menu.h"
#include "Cursor.h"
#include "GBTime.h"

class Game
{
  public:
    // constructor
    Game ();
    // Destructor
    ~Game();
    // method of use
    void Display();
    void Reset();

  private:
    MainMenu *m_MainMenuEnglish;
    MainMenu *m_MainMenuFrench;
    MainMenu *m_SettingMenuEnglish;
    MainMenu *m_SettingMenuFrench;
    Grid *m_City;
    Menu *m_Menu;
    Cursor *m_Cursor;
    GBTime *m_Time;
    //avoid unnecessary loops
    bool m_Data;
    // main menu variable
    uint8_t m_Language;
    // main menu variable
    uint8_t m_Mode;
    // Setting menu variable
    uint8_t m_Setting;
    // open update menu
    bool m_Update;
    Tile *m_TileUpdate;
    // variable to block the buttons
    bool m_ButtonA_Lock;
    bool m_ButtonB_Lock;
    // stop musique money
    bool m_PlayMusicMoney;
    // activate or not the tutorial
    bool m_Tutorial;
    uint8_t m_TutorialLevel;
    // Variables Information
    int32_t m_Money;
    uint16_t m_NbrDay;
    uint32_t m_Credit;
    uint32_t m_Debit;
    uint16_t m_Citizen;
    uint16_t m_Job;


    // method of use
    void DisplayMenu();
    void DisplayCursor();
    void MoveCursor();
    void ErrorCursor();
    void ConstructCursor();
    void DisplayMoney();
    void AnimateMoney();
    void DisplayTime();
    void UpdateInfo();
    void Message(const char TextMessage[18] );
    void Memory(uint8_t Memory_Action);
    void ChoiceManagement();


};
#endif
