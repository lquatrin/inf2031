#include <stdio.h>

#include "header.h"

using namespace std;

int main()
{
  int noElements = 3;
  int* myarray = new int[noElements];

  myarray[0] = 10;
  myarray[1] = 15;
  myarray[2] = 75;

  computingClass cC = computingClass(myarray, noElements);

  delete[] myarray;
  return 0;
}