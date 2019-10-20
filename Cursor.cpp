#include "Cursor.h"

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Cursor::Cursor() :
  m_State(0),
  m_Choice(1),
  m_Line(6),
  m_Column(6),
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
uint16_t Cursor::Line() const
{
  return (m_Line);
}
uint16_t Cursor::Column() const
{
  return (m_Column);
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
void Cursor::Line(uint16_t ChangeLine)
{
  m_Line = ChangeLine;
}
void Cursor::Column(uint16_t ChangeColumn)
{
  m_Column = ChangeColumn;
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
  m_TileCursor->CartX((GridTileColumn + (m_Column*TILE_WIDTH)));
  m_TileCursor->CartY((GridTileLine + (m_Line*TILE_HEIGHT)) - 35);
  m_TileCursor->TwoDToIso();
  m_TileCursor->Type(m_Choice);
  m_TileCursor->Display();
};
