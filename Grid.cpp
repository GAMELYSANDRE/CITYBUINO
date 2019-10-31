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
//----------------------------------------------------------------------
//                   Method movement on the map
//----------------------------------------------------------------------

void Grid::ChangeTile(uint8_t ChangeI, uint8_t ChangeJ, uint8_t ChangeType)
{
  m_Grid[ChangeI][ChangeJ].Type(ChangeType);
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

