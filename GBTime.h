#ifndef __GBTIME__
#define __GBTIME__

#include <Gamebuino-Meta.h>

class GBTime 
{
   
  public:
    // constructor 
    GBTime();
    
    // getters methods
    unsigned long BeginTime() const;
    unsigned long TempTime() const;
    
    // others methods
    void IncrementTime();
    void Reset();
    void InitBeginTime();

    
  private:
    unsigned long m_BeginTime;
    unsigned long m_TempTime;
    bool m_Activate;

};

#endif

