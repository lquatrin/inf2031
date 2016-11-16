// MathFuncCRL.h

#pragma once

#include "../MathFuncCRLCpp/MathFuncs.h"
#include "../MathFuncCRLCpp/MathFuncs.cpp"

using namespace System;

namespace CppWrapper {

  public ref class MyMathFuncsWrapper
  {
  public:
    // constructor
    MyMathFuncsWrapper();

    // wrapper methods
    double AddWrapper (double a, double b);
    double SubtractWrapper (double a, double b);
    double MultiplyWrapper (double a, double b);
    double DivideWrapper (double a, double b);

    // public variable
    double initVal;

  private:
    MyMathFuncs *myCppClass; // an instance of class in C++
  };
}
