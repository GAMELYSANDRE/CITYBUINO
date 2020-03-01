#ifndef __GAMECURSOR__
#define __GAMECURSOR__

//----------------------------------------------------------------------
//                        show cursor
//----------------------------------------------------------------------

void Game::DisplayCursor()
{
  if (m_Menu->CursorState() == true and m_Menu->GetState() == false )
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
    if (m_ButtonB_Lock == true)
    {
      m_Menu->CursorState(false);
      m_Cursor->State(false);
      m_ButtonB_Lock = false;
    }
    else
    {
      m_ButtonB_Lock = true;
    }
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
    SerialUSB.printf("---------------------------------\n");
    SerialUSB.printf("TILE MOVE : PRESSED RIGHT AND UP \n");
    SerialUSB.printf("---------------------------------\n");
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
//        Cursor action when buttons are pressed
//----------------------------------------------------------------------

void Game::ConstructCursor()
{
  uint8_t i = m_Cursor->GridLine();
  uint8_t j = m_Cursor->GridColumn();
  uint8_t Choise = m_Cursor->Choice();
  uint16_t Cost = m_Menu->Cost();
  uint8_t CityTile = m_City->Type(i, j);
  // disable the a button if the menu is visible
  if (m_Menu->GetState() == false)
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
          if ( Choise != UPDATE)
          {
            // Construct the new tile
            m_City->Type(i, j, Choise );
            m_Money = m_Money - Cost;
            gb.sound.fx(SOUND_CONST);
          }  
        }
        else
        {
          if ( CityTile == SEA )
          {
            Message(TranslateErrorWater[m_Language]);
          }
          else
          {
            if ( Choise != UPDATE)
            {
              Message(TranslateErrorPresent[m_Language]);
            }
          }
        }
      }
      else
      {
        if ( Choise != BULL )
        {
          Message(TranslateErrorNoMoney[m_Language]);
        }
      }
      // destroyed and replaced by sand
      if ( CityTile != SEA and Choise == BULL )
      {
        m_City->Type(i, j, SAND );
        m_City->ResetError(i, j);
        gb.sound.fx(SOUND_BULL);
        UpdateInfo();
      }
      m_Data = true;
    }
  }
}
#endif
