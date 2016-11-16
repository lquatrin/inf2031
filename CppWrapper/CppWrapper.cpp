// This is the main DLL file.

#include "stdafx.h"

#include "CppWrapper.h"

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

CppWrapper::CppLAMPWrapper::CppLAMPWrapper(int *pInt, int arraySize)
{
  pCC = new LAMPClass(pInt, arraySize);
}

double CppWrapper::CppLAMPWrapper::GetSum()
{
  sum = pCC->SumArray();
  
  return sum;
}

void CppWrapper::CppLAMPWrapper::testLamp()
{
  pCC->lampTest();
}
