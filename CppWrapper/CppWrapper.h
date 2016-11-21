// ClassCppToCS_Wrapper.h

#pragma once

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

#include "../MDS/mds.h"
#include "../MDS/mds.cpp"

#include "../Histogram/Histogram.h"
#include "../Histogram/Histogram.cpp"

#include <msclr\marshal_cppstd.h>
#include <math.h>
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
	CppMDSWrapper(array<double,2>^ tvalues, int arraySize);
	array<double, 2>^ GetMDS();
    void testMDS();
    private:
	MDSClass* pMDS;
	array<double, 2>^ dists;
  };

  public ref class CppHistogramWrapper
  {
    public:
      CppHistogramWrapper();
	  void CreateHistogram(char** ppNames, int iNbOfNames);
	  void addPath(array<System::String^>^ bytes);
      void testHistogram();
      array<double, 2>^GetDistances(void);

    private:
      Histogram* pHistogram;
  };

}
