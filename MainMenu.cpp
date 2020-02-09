#include "MainMenu.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------

MainMenu::MainMenu (const char* const MenuTextList[], uint8_t MenuSize):
  m_MenuPosition(0),
  m_Mode(MENU)
{
  m_MenuSize = MenuSize;
  // Create the array to save string lengths
  m_MenuTextSize = new uint8_t[MenuSize];
  // Create row
  m_MenuTextList = new char*[MenuSize];
  // create column according to the string length
  for (uint8_t i = 0; i < MenuSize; i++)
  {
    uint8_t TextSize = strlen(MenuTextList[i]);
    m_MenuTextSize[i] = TextSize;
    m_MenuTextList[i] = new char[TextSize];
  }
  // copy the string length
  for (uint8_t i = 0; i < MenuSize; i++)
  {
    strcpy(m_MenuTextList[i], MenuTextList[i]);
  }
  // initialize building
  for (uint8_t i = 0; i < 5; i++)
  {
    m_Building[i] = new Building();
  }

}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

MainMenu::~MainMenu()
{
  for (uint8_t i = 0; i < m_MenuSize; i++)
  {
    delete[] m_MenuTextList[i];
  }
  delete[] m_MenuTextList;
  for (uint8_t i = 0; i < 5; i++)
  {
    delete m_Building[i];
  }
}
//----------------------------------------------------------------------
//           Getters Methods
//----------------------------------------------------------------------
uint8_t MainMenu::GetMode() const
{
  return (m_Mode);
}


//----------------------------------------------------------------------
//          Setters Methods
//----------------------------------------------------------------------
void MainMenu::SetMode(uint8_t ChangeMode)
{
  m_Mode = ChangeMode;
}

void MainMenu::DisplayText (uint8_t RowText)
{
  uint8_t CenterTextHoriz = (80 - m_MenuTextSize[RowText] * 4) / 2;
  uint8_t CenterTextVert = (64 - 9 * m_MenuSize) + (RowText * 9);
  if ( RowText == m_MenuPosition )
  {
    gb.display.setColor(0, 255, 77);
  }
  else
  {
    gb.display.setColor(255, 77, 0);
  }
  gb.display.setCursor(CenterTextHoriz, CenterTextVert);
  gb.display.print(m_MenuTextList[RowText]);
}

void MainMenu::Display()
{
  // TITLE
  gb.display.setFontSize(2);
  gb.display.setCursor(6, 3);
  gb.display.setColor(95, 79, 0);
  gb.display.print("CITYBUINO");
  gb.display.setCursor(5, 2);
  gb.display.setColor(252, 211, 0);
  gb.display.print("CITYBUINO");
  // display the building
  m_Building[0]->SetX(15);
  m_Building[0]->Display();
  m_Building[1]->SetX(45);
  m_Building[1]->Display();
  m_Building[2]->SetX(0);
  m_Building[2]->Display();
  m_Building[3]->SetX(30);
  m_Building[3]->Display();
  m_Building[4]->SetX(60);
  m_Building[4]->Display();
  // display menu
  gb.display.setFontSize(1);
  Create();
  MoveText();
}
void MainMenu::Create()
{
  for (uint8_t i = 0; i < m_MenuSize; i++)
  {
    DisplayText(i);
  }
}

void MainMenu::MoveText()
{
  if (gb.buttons.pressed(BUTTON_DOWN))
  {
    if (m_MenuPosition >= (m_MenuSize - 1))
    {
      m_MenuPosition = m_MenuSize - 1;
    }
    else
    {
      m_MenuPosition++;
    }
    gb.sound.playOK();
  }
  if (gb.buttons.pressed(BUTTON_UP))
  {

    if (m_MenuPosition <= 0)
    {
      m_MenuPosition = 0;
    }
    else
    {
      m_MenuPosition--;
    }
    gb.sound.playOK();
  }
  if (gb.buttons.pressed(BUTTON_A))
  {
    m_Mode = m_MenuPosition;
    gb.sound.playTick();
  }
}
