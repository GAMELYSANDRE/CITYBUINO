#ifndef __TILE__
#define __TILE__


#include "Constant.h"
#include <Gamebuino-Meta.h>

class Tile
{
  public:
    // constructors
    Tile();
    Tile (
      int8_t Line,
      int8_t Column,
      int16_t CartX,
      int16_t CartY,
      uint8_t Type
    );
    // Destructor
    ~Tile();


    // getters methods
    int8_t Line() const;
    int8_t Column() const;
    int16_t CartX() const;
    int16_t CartY() const;
    uint8_t Type() const;
    uint8_t Error() const;


    // setters methods
    void Line(int8_t ChangeLine);
    void Column(int8_t ChangeColumn);
    void CartX(int16_t ChangeCartX);
    void CartY(int16_t ChangeCartY);
    void Type(uint8_t ChangeType);
    void Error(uint8_t ChangeError);

    // method other
    void Display(bool Cart_OR_iso);
    void InitCoordCartesian();
    //void TwoDToIso();


  private:
    int8_t m_Line;             // line number
    int8_t m_Column;           // column number
    //Cartesian
    int16_t m_CartX;           // acoordinate iso of the x axis
    int16_t m_CartY;           // acoordinate iso of the Y axis
    //isometric
    //int16_t m_IsoX;            // acoordinate iso of the x axis
    //int16_t m_IsoY;            // acoordinate iso of the Y axis
    uint8_t m_Type;            // see file : constant.h
    uint8_t m_Error;              // active(0) inactive (1) error
};



#endif
