#include <stdio.h>

#include "invproj.h"

#include <opencv2/core/core.hpp>

using namespace std;

int main()
{
  InverseProjection h = InverseProjection();
  h.test();
  system("pause");
  return 0;
}