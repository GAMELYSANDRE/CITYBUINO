#include "Cursor.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Cursor::Cursor() :
  m_State(0),
  m_Choice(1),
  m_ViewLine(6),   // center screen
  m_ViewColumn(6), // center screen
  m_GridLine(1),
  m_GridColumn(1),
  m_CameraX(1),
  m_CameraY(1)

{
  m_TileCursor = new Tile();
}

//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Cursor::~Cursor()
{
  delete m_TileCursor;
}

//----------------------------------------------------------------------
//                       Getters methods
//----------------------------------------------------------------------
bool Cursor::State() const
{
  return (m_State);
}
uint8_t Cursor::Choice() const
{
  return (m_Choice);
}
uint16_t Cursor::ViewLine() const
{
  return (m_ViewLine);
}
uint16_t Cursor::ViewColumn() const
{
  return (m_ViewColumn);
}
uint8_t Cursor::GridLine() const
{
  return (m_GridLine);
}
uint8_t Cursor::GridColumn() const
{
  return (m_GridColumn);
}
uint16_t Cursor::CameraX() const
{
  return (m_CameraX);
}
uint16_t Cursor::CameraY() const
{
  return (m_CameraY);
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Cursor::State(bool ChangeState)
{
  m_State = ChangeState;
}
void Cursor::Choice(uint8_t ChangeChoice)
{
  m_Choice = ChangeChoice;
}
void Cursor::ViewLine(uint16_t ChangeViewLine)
{
  m_ViewLine = ChangeViewLine;
}
void Cursor::ViewColumn(uint16_t ChangeViewColumn)
{
  m_ViewColumn = ChangeViewColumn;
}
void Cursor::GridLine(uint8_t ChangeGridLine)
{
  m_GridLine = ChangeGridLine;
}
void Cursor::GridColumn(uint8_t ChangeGridColumn)
{
  m_GridColumn = ChangeGridColumn;
}
void Cursor::CameraX(uint16_t ChangeCameraX)
{
  m_CameraX = ChangeCameraX;
}
void Cursor::CameraY(uint16_t ChangeCameraY)
{
  m_CameraY = ChangeCameraY;
}


//----------------------------------------------------------------------
//                        method draw Cursor
//----------------------------------------------------------------------
void Cursor::Display()
{
  // Calculate the tile at the top right
  float GridColumn = m_CameraX / TILE_WIDTH;
  float GridLine = m_CameraY / TILE_HEIGHT;
  float GridTileColumn = (floor(GridColumn) - GridColumn) * TILE_WIDTH;
  float GridTileLine = (floor(GridLine) - GridLine) * TILE_HEIGHT;
  // Modify tile coordinates for displayed in the view
  m_TileCursor->CartX((GridTileColumn + (m_ViewColumn * TILE_WIDTH)));
  m_TileCursor->CartY((GridTileLine + (m_ViewLine * TILE_HEIGHT)) - 35);
  m_TileCursor->TwoDToIso();
  m_TileCursor->Type(m_Choice);
  m_TileCursor->Display();
  // save position cursor
  m_GridLine = GridLine + m_ViewLine;
  m_GridColumn = GridColumn + m_ViewColumn;
};

