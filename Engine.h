#ifndef __ENGINE__
#define __ENGINE__

void Grid::CheckTheTile()
{
  for (int i = m_CameraTileY; i < m_CameraTileY + NBR_TILES_HEIGHT  ; i++) // prevents segmentation fault
  {
    for (int j = m_CameraTileX; j < m_CameraTileX + NBR_TILES_WIDTH ; j++)
    {
      //-------------------------------------
      //
      //         [j]     [j]       [j]
      //
      //     UP LEFT    UP     UP RIGHT
      // [i]  -1      -1        -1
      //         -1       1        +1
      //    -----------------------------
      //      LEFT    CENTER    RIGHT
      // [i]  1        1        1
      //         -1       1        +1
      //    -----------------------------
      //     DOWN LEFT   DOWN   DOWN RIGHT
      // [i]  +1        +1      +1
      //         -1       1        +1
      //
      //-------------------------------------
      // init variables
      uint8_t TileUpLeft = SEA;
      uint8_t TileUp = SEA;
      uint8_t TileUpRight = SEA;

      uint8_t TileLeft = SEA;
      uint8_t TileCenter = SEA;
      uint8_t TileRight = SEA;

      uint8_t TileDownLeft = SEA;
      uint8_t TileDown = SEA;
      uint8_t TileDownRight = SEA;

      TileUpLeft = CheckPresenceRoad(m_Grid[i - 1][j - 1].Type());
      TileUp = CheckPresenceRoad(m_Grid[i - 1][j].Type());
      TileUpRight = CheckPresenceRoad(m_Grid[i - 1][j + 1].Type());

      TileLeft = CheckPresenceRoad(m_Grid[i][j - 1].Type());
      TileCenter = CheckPresenceRoad(m_Grid[i][j].Type());
      TileRight = CheckPresenceRoad(m_Grid[i][j + 1].Type());

      TileDownLeft = CheckPresenceRoad(m_Grid[i + 1][j - 1].Type());
      TileDown = CheckPresenceRoad(m_Grid[i + 1][j].Type());
      TileDownRight = CheckPresenceRoad(m_Grid[i + 1][j + 1].Type());

      //-----------------------------------------
      // check if there is a road near the house
      //-----------------------------------------
      if ( TileCenter == HOME_RED or TileCenter == POWER_STATION )
      {
        if
        ( TileUp == ROAD or TileDown == ROAD or
            TileLeft == ROAD or TileRight == ROAD
        )
        {
          m_Grid[i][j].Error( 0 );
        }
        else
        {
          m_Grid[i][j].Error( ERROR_ROAD );
        }
      }
      //-----------------------------------------------------
      // check if there is a station power near the house
      //-----------------------------------------------------
      if ( TileCenter == HOME_RED and m_Grid[i][j].Error() == 0 )
      {
        uint8_t DetectXPowStat = 0;
        uint8_t DetectYPowStat = 0;
        bool DetectPowStat = false;
        // limite Screen X
        if ( m_Grid[i][j].Column() < 5 )
        {
          DetectXPowStat = m_CameraTileX;
        }
        else
        {
          DetectXPowStat = m_Grid[i][j].Column() - 5;
        }
        // limite Screen Y
        if ( m_Grid[i][j].Line() < 5 )
        {
          DetectYPowStat = m_CameraTileY;
        }
        else
        {
          DetectYPowStat = m_Grid[i][j].Line() - 5;
        }
        SerialUSB.printf("Pos X: %i\n", DetectXPowStat );
        SerialUSB.printf("Pos Y: %i\n", DetectYPowStat );
        SerialUSB.printf("Line: %i\n", m_Grid[i][j].Line() );
        SerialUSB.printf("Column: %i\n", m_Grid[i][j].Column() );
        for ( uint8_t X = DetectXPowStat; X < DetectXPowStat + 10; X++)
        {
          for (uint8_t Y = DetectYPowStat; Y < DetectYPowStat + 10; Y++)
          {
            if ( m_Grid[Y][X].Type() == POWER_STATION )
            {
              SerialUSB.printf("Station detected");
              DetectPowStat = true;
            }
          }
        }
        if ( DetectPowStat == true )
        {
          m_Grid[i][j].Error( 0 );
        }
        else
        {
          m_Grid[i][j].Error( ERROR_ELEC );
        }
      }






      //-----------------------------------------------------
      //    create turns et crossing following the roads
      //-----------------------------------------------------
      if ( TileCenter == ROAD )
      {
        // turn up right
        if ( TileDown == ROAD and TileCenter == ROAD
             and TileRight == ROAD and TileUp != ROAD
             and TileLeft != ROAD )
        {
          m_Grid[i][j + 1].Type(ROAD_V);
          m_Grid[i][j].Type(ROAD_UR);
          m_Grid[i + 1][j].Type(ROAD_H);
        }
        // turn up left
        if ( TileDown == ROAD and TileCenter == ROAD
             and TileLeft == ROAD and TileUp != ROAD
             and TileRight != ROAD )
        {
          m_Grid[i][j - 1].Type(ROAD_V);
          m_Grid[i][j].Type(ROAD_UL);
          m_Grid[i + 1][j].Type(ROAD_H);
        }
        // turn down right
        if ( TileUp == ROAD and TileCenter == ROAD
             and TileRight == ROAD and TileDown != ROAD
             and TileLeft != ROAD )
        {
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i][j].Type(ROAD_DR);
          m_Grid[i][j + 1].Type(ROAD_V);
        }
        // turn down left
        if ( TileUp == ROAD and TileCenter == ROAD
             and TileLeft == ROAD and TileDown != ROAD
             and TileRight != ROAD )
        {
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i][j].Type(ROAD_DL);
          m_Grid[i][j - 1].Type(ROAD_V);
        }
        // intersection up
        if ( TileCenter == ROAD and TileRight == ROAD
             and TileLeft == ROAD and TileDown == ROAD
             and TileUp != ROAD )
        {
          m_Grid[i][j - 1].Type(ROAD_V);
          m_Grid[i][j].Type(ROAD_INT_UP);
          m_Grid[i][j + 1].Type(ROAD_V);
          m_Grid[i + 1][j].Type(ROAD_H);
        }
        // intersection down
        if ( TileCenter == ROAD and TileRight == ROAD
             and TileLeft == ROAD and TileUp == ROAD
             and TileDown != ROAD )
        {
          m_Grid[i][j - 1].Type(ROAD_V);
          m_Grid[i][j].Type(ROAD_INT_DOWN);
          m_Grid[i][j + 1].Type(ROAD_V);
          m_Grid[i - 1][j].Type(ROAD_H);
        }
        // intersection right
        if ( TileCenter == ROAD and TileUp == ROAD
             and TileDown == ROAD and TileRight == ROAD
             and TileLeft != ROAD )
        {
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i][j].Type(ROAD_INT_LEFT);
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i][j + 1].Type(ROAD_V);
        }
        // intersection left
        if ( TileCenter == ROAD and TileUp == ROAD
             and TileDown == ROAD and TileLeft == ROAD
             and TileRight != ROAD )
        {
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i][j].Type(ROAD_INT_RIGHT);
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i][j - 1].Type(ROAD_V);
        }
        // intersection center
        if ( TileCenter == ROAD and TileUp == ROAD
             and TileDown == ROAD and TileLeft == ROAD
             and TileRight == ROAD )
        {
          m_Grid[i - 1][j].Type(ROAD_H);
          m_Grid[i + 1][j].Type(ROAD_H);
          m_Grid[i][j].Type(ROAD_INT);
          m_Grid[i][j - 1].Type(ROAD_V);
          m_Grid[i][j + 1].Type(ROAD_V);
        }
        // detects vertical roads
        if ( ( m_Grid[i][j].Type() == ROAD_H and
               m_Grid[i][j - 1].Type() == ROAD_V ) or
             ( m_Grid[i][j].Type() == ROAD_H and
               m_Grid[i][j + 1].Type() == ROAD_V )
           )
        {
          m_Grid[i][j].Type(ROAD_V);
        }
        // detects horizontal roads
        if ( ( m_Grid[i][j].Type() == ROAD_V and
               m_Grid[i - 1][j].Type() == ROAD_H ) or
             ( m_Grid[i][j].Type() == ROAD_V and
               m_Grid[i + 1][j].Type() == ROAD_H )
           )
        {
          m_Grid[i][j].Type(ROAD_H);
        }
      }
    }
  }

}

uint8_t Grid::CheckPresenceRoad(uint8_t VerifTile )
{
  if ( VerifTile == ROAD_H or
       VerifTile == ROAD_V or
       VerifTile == ROAD_UL or
       VerifTile == ROAD_UR or
       VerifTile == ROAD_DL or
       VerifTile == ROAD_DR or
       VerifTile == ROAD_INT_DOWN or
       VerifTile == ROAD_INT_UP or
       VerifTile == ROAD_INT_RIGHT or
       VerifTile == ROAD_INT_LEFT or
       VerifTile == ROAD_INT
     )
  {
    return (ROAD);
  }
  else
  {
    return (VerifTile);
  }
}


#endif
