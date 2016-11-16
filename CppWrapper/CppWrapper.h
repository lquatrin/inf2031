// ClassCppToCS_Wrapper.h

#pragma once

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

using namespace System;

namespace ClassCppToCS_Wrapper {

	public ref class CppWrapperClass
	{
  public:
    CppWrapperClass(int* pInt, int arraySize);
    double GetSum();
    double sum;

    void testLamp ();

  private:
    LAMPClass* pCC;
	};
}
