#include "Tile.h"
#include "Image.h"

//----------------------------------------------------------------------
//                        Variables statics
//----------------------------------------------------------------------
uint16_t Tile::m_Counter = 0;

//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Tile::Tile() :
  m_Line(0),
  m_Column(0),
  m_IsoX(0),
  m_IsoY(0),
  m_Type(GRASS)
{
  InitCoordCartesian();
  TwoDToIso();
  m_Counter++;
  m_Number = m_Counter;
}

Tile::Tile (int8_t Line, int8_t Column, int16_t IsoX, int16_t IsoY, uint8_t Type)
{
  m_IsoX = IsoX;
  m_IsoY = IsoY;
  m_Line = Line;
  m_Column = Column;
  m_Type = Type;
  m_Counter++;
  m_Number = m_Counter;
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
uint16_t Tile::Number() const
{
  return (m_Number);
}
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
uint16_t Tile::Counter() const
{
  return (m_Counter);
}

//----------------------------------------------------------------------
//                        Setters methods
//----------------------------------------------------------------------
void Tile::Number(uint16_t ChangeNumber)
{
  m_Number = ChangeNumber;
}
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


//----------------------------------------------------------------------
//                        method draw tile
//----------------------------------------------------------------------
void Tile::Display()
{

  switch (m_Type)
  {
    case GRASS:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_GRASS);
      break;
    case SAND:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_SAND);
      break;
    case SEA:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_SEA);
      break;
    case ROAD_H:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_ROAD_H);
      break;
    case HOME_RED:
      gb.display.drawImage(m_IsoX, m_IsoY, IMG_HOME_RED);
      break;
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
