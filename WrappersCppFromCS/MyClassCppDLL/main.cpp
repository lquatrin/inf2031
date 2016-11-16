//Include all files from the first CPP Project
#include "../MyClassCpp/header.h"
#include "../MyClassCpp/body.cpp"

#define EXTERN extern "C" __declspec(dllexport)

EXTERN double sumTwo(double a, double b)
{
  MultiProjAlg mp(a,b);
  return mp.SumX_Y();
}


