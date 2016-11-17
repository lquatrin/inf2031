#include <stdio.h>

#include "mds.h"

#include <opencv2/core/core.hpp>

using namespace std;

int main()
{
  int noElements = 3;
  int* myarray = new int[noElements];

  myarray[0] = 10;
  myarray[1] = 15;
  myarray[2] = 75;

  MDSClass cC = MDSClass(myarray, noElements);

  cC.mdsTest();

  delete[] myarray;
  return 0;
}