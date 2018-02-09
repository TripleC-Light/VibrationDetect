#include "Arduino.h"

#ifndef KalmanFilter_h
#define KalmanFilter_h

class KalmanFilter
{
  public:
    KalmanFilter();
    int start(int Xt, int Yt_1);
    double Q = 0.1;
    double R = 40;
  private:
    double Vkt;
    double St;
    double Vpt;
    unsigned long Yt;
    double Kt;
};

extern KalmanFilter KlmFilter;

#endif

