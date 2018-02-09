#include "Arduino.h"

#ifndef MoveAverageFilter_h
#define MoveAverageFilter_h

class MoveAverageFilter
{
  public:
    MoveAverageFilter();
    int start(int Xn, int Yn_1);
    double alpha = 0.5;
  private:
};

extern MoveAverageFilter maFilter;

#endif

