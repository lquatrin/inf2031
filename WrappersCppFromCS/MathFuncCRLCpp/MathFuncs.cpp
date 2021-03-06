#pragma once
#include "MathFuncs.h"

double MyMathFuncs::Add(double a, double b)
{
  return a + b;
}

double MyMathFuncs::Subtract(double a, double b)
{
  return a - b;
}

double MyMathFuncs::Multiply(double a, double b)
{
  return a*b;
}

double MyMathFuncs::Divide(double a, double b)
{
  if (b == 0)
    throw invalid_argument("b cannot be zero!");
  return a/b;
}