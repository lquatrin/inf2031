#pragma once

#include <stdexcept>
using namespace std;

#define EXPORT extern "C" __declspec(dllexport)

namespace MathFuncs
{
  EXPORT double Add(double a, double b);
  EXPORT double Subtract(double a, double b);
  EXPORT double Multiply(double a, double b);
  EXPORT double Divide(double a, double b);
}