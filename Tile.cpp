#include "Tile.h"
#include "Image.h"


//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Tile::Tile() :
  m_Line(0),
  m_Column(0),
  m_IsoX(0),
  m_IsoY(0),
  m_Type(GRASS),
  m_Error(false)
{
  InitCoordCartesian();
  TwoDToIso();
}

Tile::Tile (int8_t Line, int8_t Column, int16_t IsoX, int16_t IsoY, uint8_t Type)
{
  m_IsoX = IsoX;
  m_IsoY = IsoY;
  m_Line = Line;
  m_Column = Column;
  m_Type = Type;
  m_Error = false;
}
//----------------------------------------------------------------------
//                           DESTRUCTOR
//----------------------------------------------------------------------

Tile::~Tile()
{

}

//----------------------------------------------------------------------
//                       Getters methods
//----------------------------------------------------------------------
int8_t Tile::Line() const
{
  return (m_Line);
}
int8_t Tile::Column() const
{
  return (m_Column);
}
int16_t Tile::CartX() const
{
  return (m_CartX);
}
int16_t Tile::CartY() const
{
  return (m_CartY);
}
int16_t Tile::IsoX() const
{
  return (m_IsoX);
}
int16_t Tile::IsoY() const
{
  return (m_IsoY);
}
uint8_t Tile::Type() const
{
  return (m_Type);
}
bool Tile::Error() const
{
  return (m_Error);
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Tile::Line(int8_t ChangeLine)
{
  m_Line = ChangeLine;
}
void Tile::Column(int8_t ChangeColumn)
{
  m_Column = ChangeColumn;
}
void Tile::CartX(int16_t ChangeCartX)
{
  m_CartX = ChangeCartX;
}
void Tile::CartY(int16_t ChangeCartY)
{
  m_CartY = ChangeCartY;
}
void Tile::IsoX(int16_t ChangeIsoX)
{
  m_IsoX = ChangeIsoX;
}
void Tile::IsoY(int16_t ChangeIsoY)
{
  m_IsoY = ChangeIsoY;
}
void Tile::Type(uint8_t ChangeType)
{
  m_Type = ChangeType;
}
void Tile::Error(bool ChangeError)
{
  m_Error = ChangeError;
}


//----------------------------------------------------------------------
//                        method draw tile
//----------------------------------------------------------------------
void Tile::Display()
{

  switch (m_Type)
  {
    case GRASS:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_GRASS);
      m_Error = false;
      break;
    case SAND:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_SAND);
      m_Error = false;
      break;
    case SEA:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_SEA);
      m_Error = false;
      break;
    case ROAD_H:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_H);
      break;
    case ROAD_V:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_V);
      break;
    case ROAD_DR:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_DR);
      break;
    case ROAD_DL:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_DL);
      break;
    case ROAD_UR:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_UR);
      break;
    case ROAD_UL:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_UL);
      break;
    case ROAD_INT_DOWN:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_INT_DOWN);
      break;
    case ROAD_INT_UP:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_INT_UP);
      break;
    case ROAD_INT_RIGHT:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_INT_RIGHT);
      break;
    case ROAD_INT_LEFT:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_INT_LEFT);
      break;
    case ROAD_INT:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_INT);
      break;
    case HOME_RED:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_HOME_RED);
      break;
    case BULL:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_BULL);
      break;
  }
  if ( m_Error == true)
  {
    gb.display.drawImage(m_IsoX, m_IsoY, IMG_ERROR);
  }
}

//----------------------------------------------------------------------
// method that initializes Cartesian coordinates from line and columns
//----------------------------------------------------------------------
void Tile::InitCoordCartesian()
{
  m_CartX = m_Column * TILE_WIDTH;
  m_CartY = m_Line * TILE_HEIGHT;
}
//----------------------------------------------------------------------
//        method converts Cartesian coordinates to isometric
//----------------------------------------------------------------------
void Tile::TwoDToIso()
{
  m_IsoX = m_CartX - m_CartY;
  m_IsoY = (m_CartX + m_CartY) / 2;
}
