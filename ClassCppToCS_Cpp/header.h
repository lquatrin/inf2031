#pragma once

#include <vector>

class computingClass
{
public:
  computingClass(int* pInt, int arrSize);
  ~computingClass() {}

  double SumArray();

private:
  std::vector<int> vec;
};