#include "KalmanFilter.h"

KalmanFilter::KalmanFilter()
{
}

/*-- Kalman Filter --*/
int KalmanFilter::start(int Xt, int Yt_1){
  St = Yt_1;
  Vpt = Vkt + Q;
  Kt = Vpt/(Vpt+R);
  Yt = St + (Kt * ( Xt - St ));
  Vkt = ( 1 - Kt ) * Vpt;
  return Yt;
}

// Set the default object
KalmanFilter KlmFilter = KalmanFilter();

