#include "Grid.h"
#include "Engine.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

Grid::Grid (const uint8_t Map[], uint8_t NumberLine, uint8_t NumberColumn) :
  m_CameraX(0),
  m_CameraY(0),
  m_CameraTileX(0),
  m_CameraTileY(0)
{
  // Create Line
  m_Grid = new Tile*[NumberLine];
  // create column
  for (uint8_t X = 0; X < NumberLine ; X++)
  {
    m_Grid[X] = new Tile[NumberColumn];
  }
  for (uint8_t X = 0; X < NumberLine ; X++)
  {
    for (uint8_t Y = 0; Y < NumberColumn ; Y++)
    {
      m_Grid[X][Y].Line(X);
      m_Grid[X][Y].Column(Y);
      m_Grid[X][Y].Type(Map[X + (NumberColumn * Y)]);
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
uint8_t Grid::CameraX() const
{
  return (m_CameraX);
}
uint8_t Grid::CameraY() const
{
  return (m_CameraY);
}
// Method return the tile on the map
int8_t Grid::Type(uint8_t I, uint8_t J ) const
{
  return (m_Grid[I][J].Type());
}
// Method return error tile
bool Grid::Error(uint8_t I, uint8_t J ) const
{
  return (m_Grid[I][J].Error());
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
      // Calculate the tile at the top left
      float GridColumn = m_CameraX / TILE_WIDTH;
      float GridLine = m_CameraY / TILE_HEIGHT;
      float GridTileColumn = (floor(GridColumn) - GridColumn) * TILE_WIDTH;
      float GridTileLine = (floor(GridLine) - GridLine) * TILE_HEIGHT;
      // find the tile to display in the view
      uint8_t TileY = GridLine + i;
      uint8_t TileX = GridColumn + j;
      m_CameraTileY = GridLine;
      m_CameraTileX = GridColumn;
      // Modify tile coordinates for displayed in the view
      m_Grid[TileY][TileX].CartX((GridTileColumn + (j * TILE_WIDTH)));
      m_Grid[TileY][TileX].CartY((GridTileLine + (i * TILE_HEIGHT)) - 35);
      m_Grid[TileY][TileX].Display(1);
    }
  }
  TestGame();
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

void Grid::ResetError(uint8_t I, uint8_t J)
{
  m_Grid[I][J].Error(0);
}
void Grid::TestGame()
{
  SerialUSB.printf("-----------------------------------------------\n");
  SerialUSB.printf("CPU: %i ,RAM: %i  \n", gb.getCpuLoad(), gb.getFreeRam());
  SerialUSB.printf("-----------------------------------------------\n");
  SerialUSB.printf("CameraX: %i ,CameraY: %i  \n", m_CameraX, m_CameraY);
  SerialUSB.printf("CameraTileX: %i ,CameraTileY: %i  \n", m_CameraTileX, m_CameraTileY);

}
