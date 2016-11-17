// This is the main DLL file.

#include "stdafx.h"

#include "CppWrapper.h"

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

#include "../MDS/mds.h"
#include "../MDS/mds.cpp"



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


CppWrapper::CppMDSWrapper::CppMDSWrapper(int *pInt, int arraySize)
{
  pMDS = new MDSClass(pInt, arraySize);
}

void CppWrapper::CppMDSWrapper::testMDS()
{
  pMDS->mdsTest();
}


CppWrapper::CppHistogramWrapper::CppHistogramWrapper()
{
  pHistogram = new Histogram();
}


//TO DO
void CppWrapper::CppHistogramWrapper::CriateHistogram(array<String^>^paths){

}

array<double, 2>^CppWrapper::CppHistogramWrapper::GetDistances(void){

  std::vector<std::vector<double>> vec;
  std::vector<std::vector<double>>::iterator itr;
  pHistogram->getDistMatrix(vec);
  array<double, 2>^ Distances = gcnew array<double,2>(vec.size(),vec.size());
  
  for (int i = 0; i < vec.size(); i++){
    for (int j = 0; j < vec[i].size(); j++){
      Distances[i, j] = vec[i][j];
    }
  }
  return Distances;
}

void CppWrapper::CppHistogramWrapper::testHistogram()
{
  pHistogram->test();
}