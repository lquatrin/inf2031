#include "header.h"

MultiProjAlg::MultiProjAlg(double vx, double vy)
  : x(vx), y(vy)
{

}

double MultiProjAlg::SumX_Y ()
{
  return x+y;
}