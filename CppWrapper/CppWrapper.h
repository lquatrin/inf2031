// ClassCppToCS_Wrapper.h

#pragma once

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

#include "../MDS/mds.h"
#include "../MDS/mds.cpp"

#include "../Histogram/Histogram.h"
#include "../Histogram/Histogram.cpp"

#include "../InverseProjection/invproj.h"
#include "../InverseProjection/invproj.cpp"

#include "../DistPixel/distpixel.h"
#include "../DistPixel/distpixel.cpp"

#include <msclr\marshal_cppstd.h>
#include <math.h>
using namespace System;

namespace CppWrapper {

	public ref class CppLAMPWrapper
	{
  public:
    CppLAMPWrapper(int* pInt, int arraySize);
    CppLAMPWrapper(array<double, 2>^ tvalues, int arraySize);

    array<double, 2>^ GetLAMP();

    double GetSum();
    double sum;

    void testLamp ();

  private:
    LAMPClass* pCC;
    array<double, 2>^ dists;
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
	  void addPath(array<System::String^>^ bytes,int channel);
    void testHistogram();
    array<double, 2>^GetDistances(void);
    void Clear();
    private:
      Histogram* pHistogram;
  };

  public ref class CppInverseProjectionWrapper
  {
  public:
    CppInverseProjectionWrapper ();

    void SetInputColorScapeType (int type);
    void InverseProjection01(int n_sets, int n_points_per_set, array<double, 2>^ set_points, array<double, 2>^ input_points, array<System::String^>^ bytes);
    void InverseProjection02(int n_sets, int n_points_per_set, array<double, 2>^ set_points, array<double, 2>^ input_points, array<System::String^>^ bytes);

    void InverseProjectionValBased(
      int n_reference_points,
      array<double, 2>^ arraypoints,
      array<double, 2>^ input_point,
      array<System::String^>^ bytes);

  private:
    InverseProjection* pinvproj;
  };


  public ref class CppDistPixelWrapper
  {
  public:
    CppDistPixelWrapper();

    void addPath(array<System::String^>^ bytes, int channel);
    void testDists();
    array<double, 2>^GetDistances(void);
    void Clear();
  private:
    distpixel* pdists;
    
  };

}
