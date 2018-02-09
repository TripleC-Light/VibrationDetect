#include "ExponentialFilter.h"

ExponentialFilter::ExponentialFilter()
{
  SampleInd = 0;
}

/*-- Kalman Filter --*/
unsigned long ExponentialFilter::start(unsigned long Xt){
  
    if( SampleInd < AVG_level ){
      SampleRec[SampleInd] = Xt;
      SampleInd++;
    }else{
      SampleInd = 0;
    }
    
    SampleAVG = 0;
    int i = 0;
    for( i=0 ; i<AVG_level ; i++ ){
      SampleAVG += SampleRec[i];
    }
    return SampleAVG / AVG_level;
}

// Set the default object
ExponentialFilter ExpFilter = ExponentialFilter();

