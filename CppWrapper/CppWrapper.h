// ClassCppToCS_Wrapper.h

#pragma once

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

#include "../MDS/mds.h"
#include "../MDS/mds.cpp"

#include "../Histogram/Histogram.h"
#include "../Histogram/Histogram.cpp"

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

  public ref class CppMDSWrapper
  {
    public:
      CppMDSWrapper(int* pInt, int arraySize);
   
      void testMDS();

    private:
      MDSClass* pMDS;
  };

  public ref class CppHistogramWrapper
  {
    public:
      CppHistogramWrapper();
      void CriateHistogram(array<String^>^paths);
      void testHistogram();
      array<double, 2>^GetDistances(void);

    private:
      Histogram* pHistogram;
     
  };

}
