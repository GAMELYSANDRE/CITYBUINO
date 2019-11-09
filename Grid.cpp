#include "Grid.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

Grid::Grid (const uint8_t Map[], int NumberLine, int NumberColumn) :
  m_CameraX(0),
  m_CameraY(0)
{
  m_NumberLine = NumberLine;
  m_NumberColumn = NumberColumn;
  // Create Line
  m_Grid = new Tile*[m_NumberLine];
  // create column
  for (int i = 0; i < m_NumberLine ; i++)
  {
    m_Grid[i] = new Tile[NumberColumn];
  }
  for (int i = 0; i < m_NumberLine ; i++)
  {
    for (int j = 0; j < m_NumberColumn ; j++)
    {
      m_Grid[i][j].Line(i);
      m_Grid[i][j].Column(j);
      m_Grid[i][j].Type(Map[j + (m_NumberColumn * i)]);
    }
  }
}
//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Grid::~Grid()
{
  delete[] m_Grid;
}

//----------------------------------------------------------------------
//                       Getters methods
//----------------------------------------------------------------------
int Grid::NumberLine() const
{
  return (m_NumberLine);
}

int16_t Grid::CameraX() const
{
  return (m_CameraX);
}
int16_t Grid::CameraY() const
{
  return (m_CameraY);
}
// Method return the tile on the map
int8_t Grid::Type(uint8_t I, uint8_t J ) const
{
  return (m_Grid[I][J].Type());
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
//  Method change tile on the map
void Grid::Type(uint8_t I, uint8_t J, uint8_t ChangeType)
{
  m_Grid[I][J].Type(ChangeType);
}


//----------------------------------------------------------------------
//                     Method draws the grid
//----------------------------------------------------------------------

void Grid::Display()
{
  for (int i = 0; i < NBR_TILES_HEIGHT ; i++)
  {
    for (int j = 0; j < NBR_TILES_WIDTH  ; j++)
    {
      // Calculate the tile at the top right
      float GridColumn = m_CameraX / TILE_WIDTH;
      float GridLine = m_CameraY / TILE_HEIGHT;
      float GridTileColumn = (floor(GridColumn) - GridColumn) * TILE_WIDTH;
      float GridTileLine = (floor(GridLine) - GridLine) * TILE_HEIGHT;
      // find the tile to display in the view
      uint8_t TileY = GridLine + i;
      uint8_t TileX = GridColumn + j;
      // Modify tile coordinates for displayed in the view
      m_Grid[TileY][TileX].CartX((GridTileColumn + (j * TILE_WIDTH)));
      m_Grid[TileY][TileX].CartY((GridTileLine + (i * TILE_HEIGHT)) - 35);
      m_Grid[TileY][TileX].TwoDToIso();
      m_Grid[TileY][TileX].Display();
    }
  }
}

void Grid::CheckTheTile()
{
  for (int i = 0; i < m_NumberLine ; i++)
  {
    for (int j = 0; j < m_NumberColumn  ; j++)
    {
      //-------------------------------------
      //
      //         [j]     [j]       [j]
      //
      //     UP LEFT    UP     UP RIGHT
      // [i]  -1      -1        -1
      //         -1       1        +1
      //    -----------------------------
      //      LEFT              RIGHT
      // [i]  1        1        1
      //         -1       1        +1
      //    -----------------------------
      //     DOWN LEFT   DOWN   DOWN RIGHT
      // [i]  +1        +1      +1
      //         -1       1        +1
      //-------------------------------------
      // init variables
      uint8_t TileUpLeft = SEA;
      uint8_t TileUp = SEA;
      uint8_t TileUpUp = SEA;
      uint8_t TileUpRight = SEA;
      uint8_t TileLeft = SEA;
      uint8_t TileRight = SEA;
      uint8_t TileDownLeft = SEA;
      uint8_t TileDown = SEA;
      uint8_t TileDownRight = SEA;
      if ( i != 0) // prevents segmentation fault
      {
        TileUpLeft = CheckPresenceRoad(m_Grid[i - 1][j - 1].Type());
        TileUp = CheckPresenceRoad(m_Grid[i - 1][j].Type());
        TileUpRight = CheckPresenceRoad(m_Grid[i - 1][j + 1].Type());
        TileUpUp = CheckPresenceRoad(m_Grid[i - 2][j].Type());
      }
      if ( j != 0 )  // prevents segmentation fault
      {
        TileDownLeft = CheckPresenceRoad(m_Grid[i + 1][j - 1].Type());
        TileLeft = CheckPresenceRoad(m_Grid[i][j - 1].Type());
      }
      TileRight = CheckPresenceRoad(m_Grid[i][j + 1].Type());
      TileDown = CheckPresenceRoad(m_Grid[i + 1][j].Type());
      TileDownRight = CheckPresenceRoad(m_Grid[i + 1][j + 1].Type());

      //-----------------------------------------
      // check if there is a road near the house
      //-----------------------------------------
      if (m_Grid[i][j].Type() == HOME_RED )
      {
        if
        ( TileUp == ROAD or
            TileDown == ROAD or
            TileLeft == ROAD or
            TileRight == ROAD
        )
        {
          m_Grid[i][j].Error(0);
        }
        else
        {
          m_Grid[i][j].Error(1);
        }
      }

      //-----------------------------------------
      //    create turns following the roads
      //-----------------------------------------
      if ((m_Grid[i][j].Type() == ROAD_H and i != 0 and j != 0) or
          (m_Grid[i][j].Type() == ROAD_V and i != 0 and j != 0) )
      {
        // turn up right
        if ( TileUpRight == ROAD and TileUp == ROAD and TileUpUp != ROAD)
        {
          m_Grid[i][j].Type(ROAD_H);
          m_Grid[i - 1][j].Type(ROAD_UR);
          m_Grid[i - 1][j + 1].Type(ROAD_V);
        }
        // turn up left
        if ( TileUpLeft == ROAD and TileUp == ROAD and TileUpUp != ROAD)
        {
          m_Grid[i][j].Type(ROAD_H);
          m_Grid[i - 1][j].Type(ROAD_UL);
          m_Grid[i - 1][j - 1].Type(ROAD_V);
        }
        // turn down right
        if ( TileDownRight == ROAD and TileDown == ROAD)
        {
          m_Grid[i][j].Type(ROAD_H);
          m_Grid[i + 1][j].Type(ROAD_DR);
          m_Grid[i + 1][j + 1].Type(ROAD_V);
        }
        // turn down left
        if ( TileDownLeft == ROAD and TileDown == ROAD )
        {
          m_Grid[i][j].Type(ROAD_H);
          m_Grid[i + 1][j].Type(ROAD_DL);
          m_Grid[i + 1][j - 1].Type(ROAD_V);
        }
        // intersection up
        if ( TileUpLeft == ROAD and TileUp == ROAD and
             TileUpRight == ROAD and TileUpUp != ROAD
           )
        {
          m_Grid[i - 1][j - 1].Type(ROAD_V);
          m_Grid[i - 1][j].Type(ROAD_INT_UP);
          m_Grid[i - 1][j + 1].Type(ROAD_V);
        }
        // intersection down
        if ( TileDownLeft == ROAD and TileDown == ROAD and
             TileDownRight == ROAD
           )
        {
          m_Grid[i + 1][j - 1].Type(ROAD_V);
          m_Grid[i + 1][j].Type(ROAD_INT_DOWN);
          m_Grid[i + 1][j + 1].Type(ROAD_V);
        }
        // intersection right
        if ( TileUpRight == ROAD and TileRight == ROAD and
             TileDownRight == ROAD
           )
        {
          m_Grid[i - 1][j + 1].Type(ROAD_H);
          m_Grid[i][j + 1].Type(ROAD_INT_RIGHT );
          m_Grid[i + 1][j + 1].Type(ROAD_H);
        }
        // intersection left
        if ( TileUpLeft == ROAD and TileLeft == ROAD and
             TileDownLeft == ROAD
           )
        {
          m_Grid[i - 1][j - 1].Type(ROAD_H);
          m_Grid[i][j - 1].Type(ROAD_INT_LEFT );
          m_Grid[i + 1][j - 1].Type(ROAD_H);
        }
        // intersection center
        if ( TileUp == ROAD and TileDown == ROAD and
             TileLeft == ROAD and TileRight == ROAD
           )
        {
          m_Grid[i - 1][j].Type(ROAD_V);
          m_Grid[i + 1][j].Type(ROAD_V);
          m_Grid[i][j].Type(ROAD_INT);
          m_Grid[i][j - 1].Type(ROAD_H);
          m_Grid[i][j + 1].Type(ROAD_H);
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
    return (SEA);
  }
}

//----------------------------------------------------------------------
//                   Method movement on the map
//----------------------------------------------------------------------

void Grid::Move()
{
  Color SUPERRED = gb.createColor(255, 0, 0);
  if (gb.buttons.repeat(BUTTON_RIGHT, 0))
  {
    if ( m_CameraX < (MAP_COLUMN * TILE_WIDTH ) - (NBR_TILES_WIDTH * TILE_WIDTH ))
    {
      m_CameraX = m_CameraX + MAP_SPEED;
      gb.display.setColor(SUPERRED);
      gb.display.fillTriangle(65, 60, 75, 50, 75, 60);
    }
    else
    {
      gb.display.setColor(SUPERRED);
      gb.display.fillCircle(70, 55, 6);
      gb.display.setColor(WHITE);
      gb.display.fillRect(67, 54, 6, 3);
    }
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 0))
  {
    if (m_CameraX != 0)
    {
      m_CameraX = m_CameraX - MAP_SPEED;
      gb.display.setColor(SUPERRED);
      gb.display.fillTriangle(5, 5, 15, 5, 5, 15);
    }
    else
    {
      gb.display.setColor(SUPERRED);
      gb.display.fillCircle(10, 10, 6);
      gb.display.setColor(WHITE);
      gb.display.fillRect(7, 9, 6, 3);
    }
  }
  if (gb.buttons.repeat(BUTTON_UP, 0))
  {
    if ( m_CameraY > 0)
    {
      m_CameraY = m_CameraY - MAP_SPEED;
      gb.display.setColor(SUPERRED);
      gb.display.fillTriangle(65, 5, 75, 5, 75, 15);
    }
    else
    {
      gb.display.setColor(SUPERRED);
      gb.display.fillCircle(70, 10, 6);
      gb.display.setColor(WHITE);
      gb.display.fillRect(67, 9, 6, 3);
    }
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 0))
  {
    if ( m_CameraY < (MAP_LINE * TILE_HEIGHT ) - (NBR_TILES_HEIGHT * TILE_HEIGHT ))
    {
      m_CameraY = m_CameraY + MAP_SPEED;
      gb.display.setColor(SUPERRED);
      gb.display.fillTriangle(5, 50, 5, 60, 15, 60);
    }
    else
    {
      gb.display.setColor(SUPERRED);
      gb.display.fillCircle(10, 55, 6);
      gb.display.setColor(WHITE);
      gb.display.fillRect(7, 54, 6, 3);
    }
  }
}
