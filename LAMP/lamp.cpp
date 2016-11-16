#pragma once

#include "lamp.h"

#include <vector>

#include <opencv2/core/core_c.h>

LAMPClass::LAMPClass(int* pInt, int arrSize)
{
  for (int i = 0; i < arrSize; i++)
  {
    vec.push_back(pInt[i]);
  }
}

double LAMPClass::SumArray()
{
  int sum = 0;
  for (int i = 0; i < vec.size(); i++)
  {
    sum += vec[i];
  }
  return (double)sum;
}