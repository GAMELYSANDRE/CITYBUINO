#ifndef __BUILDING__
#define __BUILDING__

#include <Gamebuino-Meta.h>

class Building
{
  public:
    // constructors
    Building();
    // Destructor
    ~Building();
    // getters methods
    bool GetX() const;
    // setters methods
    void SetX(uint8_t ChangeX);

    void Display();

  private:
    uint8_t m_X;
    uint8_t m_Y;
    uint8_t m_Width;
    uint8_t m_Height;
    uint8_t m_Color;
    bool** m_Windows;

};

#endif
