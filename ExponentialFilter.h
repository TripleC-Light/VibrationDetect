#include "Arduino.h"

#ifndef ExponentialFilter_h
#define ExponentialFilter_h
#define AVG_level 16

class ExponentialFilter
{
  public:
    ExponentialFilter();
    unsigned long SampleRec[AVG_level];
    unsigned long start(unsigned long Xt);
  private:
    int SampleInd;
    unsigned long SampleAVG;
};

extern ExponentialFilter ExpFilter;

#endif

