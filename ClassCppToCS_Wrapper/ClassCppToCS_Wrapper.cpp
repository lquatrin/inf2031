// This is the main DLL file.

#include "stdafx.h"

#include "ClassCppToCS_Wrapper.h"

#include "../ClassCppToCS_Cpp/header.h"
#include "../ClassCppToCS_Cpp/body.cpp"


ClassCppToCS_Wrapper::CppWrapperClass::CppWrapperClass(int *pInt, int arraySize)
{
  pCC = new computingClass(pInt, arraySize);



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
