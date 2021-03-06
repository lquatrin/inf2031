#include <stdio.h>

#include "header.h"

#include <opencv2/core/core.hpp>

using namespace std;

int main()
{
  int noElements = 3;
  int* myarray = new int[noElements];

  myarray[0] = 10;
  myarray[1] = 15;
  myarray[2] = 75;

  computingClass cC = computingClass(myarray, noElements);

  cC.lampTest();

  delete[] myarray;
  return 0;
}