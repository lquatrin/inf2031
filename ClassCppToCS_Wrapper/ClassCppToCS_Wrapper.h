// ClassCppToCS_Wrapper.h

#pragma once

#include "../ClassCppToCS_Cpp/header.h"
#include "../ClassCppToCS_Cpp/body.cpp"

using namespace System;

namespace ClassCppToCS_Wrapper {

	public ref class CppWrapperClass
	{
  public:
    CppWrapperClass(int* pInt, int arraySize);
    double GetSum();
    double sum;

  private:
    computingClass* pCC;
	};
}
