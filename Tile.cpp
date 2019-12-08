#include "Tile.h"
#include "Image.h"


//----------------------------------------------------------------------
//                        Constructors
//----------------------------------------------------------------------
Tile::Tile() :
  m_Line(0),
  m_Column(0),
  m_CartX(0),
  m_CartY(0),
  m_Type(GRASS),
  m_Error(0)
{
  InitCoordCartesian();
}

Tile::Tile (int8_t Line, int8_t Column, int16_t CartX, int16_t CartY, uint8_t Type)
{
  m_Line = Line;
  m_Column = Column;
  m_CartX = CartX;
  m_CartY = CartY;
  m_Type = Type;
  m_Error = 0;
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
uint8_t Tile::Type() const
{
  return (m_Type);
}
uint8_t Tile::Error() const
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
void Tile::Type(uint8_t ChangeType)
{
  m_Type = ChangeType;
}

void Tile::Error(uint8_t ChangeError)
{
  m_Error = ChangeError;
}


//----------------------------------------------------------------------
//                        method draw tile
//----------------------------------------------------------------------
void Tile::Display(bool Cart_OR_iso)
{
  int16_t IsoX = 0;
  int16_t IsoY = 0;
  if ( Cart_OR_iso )
  {
    IsoX = m_CartX - m_CartY;
    IsoY = (m_CartX + m_CartY) / 2;
  }
  else
  {
    IsoX = m_CartX;
    IsoY = m_CartY;
  }
  switch (m_Type)
  {
    case GRASS:
      gb.display.drawImage(IsoX, IsoY, IMG_GRASS);
      break;
    case SAND:
      gb.display.drawImage(IsoX, IsoY, IMG_SAND);
      break;
    case SEA:
      gb.display.drawImage(IsoX, IsoY, IMG_SEA);
      break;
    case INFO:
      gb.display.drawImage(IsoX, IsoY, IMG_INFO);
      break;
    case ROAD_H:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_H);
      break;
    case ROAD_V:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_V);
      break;
    case ROAD_DR:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_DR);
      break;
    case ROAD_DL:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_DL);
      break;
    case ROAD_UR:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_UR);
      break;
    case ROAD_UL:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_UL);
      break;
    case ROAD_INT_DOWN:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_INT_DOWN);
      break;
    case ROAD_INT_UP:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_INT_UP);
      break;
    case ROAD_INT_RIGHT:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_INT_RIGHT);
      break;
    case ROAD_INT_LEFT:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_INT_LEFT);
      break;
    case ROAD_INT:
      gb.display.drawImage(IsoX, IsoY, IMG_ROAD_INT);
      break;
    case HOME_RED:
      gb.display.drawImage(IsoX, IsoY, IMG_HOME_RED );
      break;
    case POWER_STATION:
      gb.display.drawImage(IsoX, IsoY, IMG_POWER_STATION );
      break;
    case BULL:
      gb.display.drawImage(IsoX, IsoY, IMG_BULL);
      break;
  }
  switch (m_Error)
  {
    case ERROR_ROAD:
      gb.display.drawImage(IsoX, IsoY, IMG_ERROR_ROAD);
      break;
    case ERROR_ELEC:
      gb.display.drawImage(IsoX, IsoY, IMG_ERROR_ELEC);
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

