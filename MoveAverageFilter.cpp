#include "MoveAverageFilter.h"

MoveAverageFilter::MoveAverageFilter()
{
}

/*-- Move average Filter --*/
int MoveAverageFilter::start(int Xn, int Yn_1){

  double A = alpha * Xn;
  double B = (1-alpha ) * Yn_1;
  
//  char alpha_exp = 1;
//  unsigned long A = (1/(2^alpha_exp)) * Xn;
//  unsigned long B = (Yn_1*((2^alpha_exp)-1))/(2^alpha_exp);

//  unsigned long output = 0;
//  char alpha_exp = 3;
//  unsigned long A = Xn >> alpha_exp;
//  unsigned long B = (Yn_1*((2^alpha_exp)-1)) >> alpha_exp;

//  output = A + B;
  return (A + B);
}

// Set the default object
MoveAverageFilter maFilter = MoveAverageFilter();

