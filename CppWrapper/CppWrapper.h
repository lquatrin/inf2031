// ClassCppToCS_Wrapper.h

#pragma once

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

using namespace System;

namespace CppWrapper {

	public ref class CppLAMPWrapper
	{
  public:
    CppLAMPWrapper(int* pInt, int arraySize);
    double GetSum();
    double sum;

    void testLamp ();

  private:
    LAMPClass* pCC;
	};
}
