#include "Grid.h"
#include "GridEngine.h"

//----------------------------------------------------------------------
//                      Constructors
//----------------------------------------------------------------------

Grid::Grid (const uint8_t Map[], uint8_t NumberLine, uint8_t NumberColumn) :
  m_CameraX(50),
  m_CameraY(50),
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
uint8_t Grid::Error(uint8_t I, uint8_t J ) const
{
  return (m_Grid[I][J].Error());
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Grid::CameraX( uint8_t ChangeCameraX)
{
  m_CameraX = ChangeCameraX;
}
void Grid::CameraY( uint8_t ChangeCameraY)
{
  m_CameraY = ChangeCameraY;
}
//  Method change tile on the map
void Grid::Type(uint8_t I, uint8_t J, uint8_t ChangeType)
{
  m_Grid[I][J].Type(ChangeType);
}
//  Method change error tile
void Grid::Error(uint8_t I, uint8_t J, uint8_t ChangeError)
{
  m_Grid[I][J].Error(ChangeError);
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
}


//----------------------------------------------------------------------
//                   Method movement on the map
//----------------------------------------------------------------------

void Grid::Move()
{
  if (gb.buttons.repeat(BUTTON_RIGHT, 0))
  {
    if ( m_CameraX < LIMIT_RIGHT )
    {
      m_CameraX = m_CameraX + MAP_SPEED;
      IMG_ARROW_RIGHT_DOWN();
    }
    else
    {
      IMG_NO_ENTRY(70, 55);
    }
    DebugGrid();
  }
  if (gb.buttons.repeat(BUTTON_LEFT, 0))
  {
    if (m_CameraX > LIMIT_LEFT + MAP_SPEED )
    {
      m_CameraX = m_CameraX - MAP_SPEED;
      IMG_ARROW_LEFT_UP();
    }
    else
    {
      IMG_NO_ENTRY(10, 10);
    }
    DebugGrid();
  }
  if (gb.buttons.repeat(BUTTON_UP, 0))
  {
    if ( m_CameraY > LIMIT_UP + MAP_SPEED )
    {
      m_CameraY = m_CameraY - MAP_SPEED;
      IMG_ARROW_RIGHT_UP();
    }
    else
    {
      IMG_NO_ENTRY(70, 10);
    }
    DebugGrid();
  }
  if (gb.buttons.repeat(BUTTON_DOWN, 0))
  {
    if ( m_CameraY < LIMIT_DOWN )
    {
      m_CameraY = m_CameraY + MAP_SPEED;
      IMG_ARROW_LEFT_DOWN();
    }
    else
    {
      IMG_NO_ENTRY(10, 55);
    }
    DebugGrid();
  }
}

void Grid::ResetError(uint8_t I, uint8_t J)
{
  m_Grid[I][J].Error(0);
}

void Grid::DebugGrid()
{
  SerialUSB.printf("-----------------------------------------------\n");
  SerialUSB.printf("CPU: %i ,RAM: %i  \n", gb.getCpuLoad(), gb.getFreeRam());
  SerialUSB.printf("-----------------------------------------------\n");
  SerialUSB.printf("CameraX: %i ,CameraY: %i  \n", m_CameraX, m_CameraY);
  SerialUSB.printf("CameraTileX: %i ,CameraTileY: %i  \n", m_CameraTileX, m_CameraTileY);
  SerialUSB.printf("-----------------------------------------------\n");
}
