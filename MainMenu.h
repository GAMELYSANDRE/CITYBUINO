#ifndef __MainMenu__
#define __MainMenu__
#include <Gamebuino-Meta.h>
#include "Constant.h"
#include "Building.hpp"

class MainMenu
{

  public:
    // constructor
    MainMenu (const char *MenuTextList[], uint8_t MenuSize);
    // Destructor
    ~MainMenu();
    // getters Methods
    uint8_t GetMode() const;   // Method for the main menu

    // setters methods
    void SetMode(uint8_t ChangeMode);



    void Display ();

  private:
    char** m_MenuTextList;        // table 2 dimensions to save strings of characters
    uint8_t m_MenuSize;           // size menu
    uint8_t* m_MenuTextSize;      // size of the menu texts
    uint8_t m_MenuPosition;       // Position in the menu
    uint8_t m_MenuPositionPressed;    // Save the position in the menu when pressing the A button
    uint8_t m_Mode;                   // Variable main menu
    // Building
    Building *m_Building[5];
    void Create();
    void DisplayText (uint8_t RowText);
    void MoveText ();
};


#endif
