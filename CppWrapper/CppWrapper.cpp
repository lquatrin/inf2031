// This is the main DLL file.

#include "stdafx.h"

#include "CppWrapper.h"

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

ClassCppToCS_Wrapper::CppWrapperClass::CppWrapperClass(int *pInt, int arraySize)
{
  pCC = new LAMPClass(pInt, arraySize);
}

double ClassCppToCS_Wrapper::CppWrapperClass::GetSum ()
{
  sum = pCC->SumArray();
  
  return sum;
}

void ClassCppToCS_Wrapper::CppWrapperClass::testLamp ()
{
  pCC->lampTest();
}
