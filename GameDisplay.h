#ifndef __GAMEDISPLAY__
#define __GAMEDISPLAY__

//----------------------------------------------------------------------
//         displays the currency and the days at the top left
//----------------------------------------------------------------------

void Game::DisplayMoney()
{
  gb.display.setCursor(4, 2);
  gb.display.setColor(GRAY);
  gb.display.print(TranslateSymbMoney[m_Language]);
  gb.display.print(m_Money);
  gb.display.print(TranslateDay[m_Language]);
  gb.display.print(m_NbrDay);
  gb.display.setCursor(3, 1);
  gb.display.setColor(WHITE);
  gb.display.print(TranslateSymbMoney[m_Language]);
  gb.display.print(m_Money);
  gb.display.print(TranslateDay[m_Language]);
  gb.display.print(m_NbrDay);
}


//----------------------------------------------------------------------
//                 make appear and disappear the menu
//----------------------------------------------------------------------

void Game::DisplayMenu()
{
  if (gb.buttons.pressed(BUTTON_MENU))
  {
    m_Menu->State(!m_Menu->GetState());
    if (m_Menu->GetState() == false)
    {
      m_Menu->Choice(BULL);
    }
  }
  if (m_Menu->GetState() == true)
  {
    m_Menu->Display();
    m_Cursor->State(false);
  }
}

//----------------------------------------------------------------------
//                          display a message
//----------------------------------------------------------------------

void Game::Message(const char TextMessage[18] )
{
  gb.display.setColor(RED);
  gb.display.fillRect(2, 20, 76, 20);
  gb.display.setColor(BLACK);
  gb.display.drawRect(2, 20, 76, 20);
  gb.display.setColor(WHITE);
  gb.display.setCursor(30, 23);
  gb.display.print(TranslateError[m_Language]);
  gb.display.setCursor(6, 30);
  gb.display.print(TextMessage);
  //gb.sound.fx(SOUND_ERROR);
  delay(1000);
}



void Game::AnimateMoney()
{
  int16_t Profit = m_Credit - m_Debit;
  if ( Profit >= 0 )
  {
    gb.display.setCursor(12, 9);
    gb.display.setColor(GRAY);
    gb.display.print("+");
    gb.display.print(Profit);
    gb.display.setCursor(11, 8);
    gb.display.setColor(0, 255, 0);
    gb.display.print("+");
    gb.display.print(Profit);
  }
  else
  {
    gb.display.setCursor(12, 9);
    gb.display.setColor(GRAY);
    gb.display.print(Profit);
    gb.display.setCursor(11, 8);
    gb.display.setColor(255, 0, 0);
    gb.display.print(Profit);
  }
}

#endif
