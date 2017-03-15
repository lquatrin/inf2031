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
#include "../InverseProjection/transferfunction.h"
#include "../InverseProjection/transferfunction.cpp"

#include "../DistPixel/distpixel.h"
#include "../DistPixel/distpixel.cpp"
#include "../DistPixel/distanceprop.h"
#include "../DistPixel/distanceprop.cpp"

#include <msclr\marshal_cppstd.h>
#include <math.h>
using namespace System;

namespace CppWrapper {

	public ref class CppLAMPWrapper
	{
  public:
    CppLAMPWrapper();
    CppLAMPWrapper(int* pInt, int arraySize);
	array<double, 2>^ GetLAMP(array<double, 2>^ tvalues, array<double, 2>^ controlPoints, array<int>^controlsidx, int controlsize, int arraySize);

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
    
    void SetModelSize (int width, int height, int depth);

    void SetInputColorScapeType (int type);
    void InverseProjection01(int n_sets, int n_points_per_set, array<double, 2>^ set_points, array<double, 2>^ input_points, array<System::String^>^ bytes);
    void InverseProjection02(int n_sets, int n_points_per_set, array<double, 2>^ set_points, array<double, 2>^ input_points, array<System::String^>^ bytes);

    void InverseProjectionValBased(
      int n_reference_points,
      array<double, 2>^ arraypoints,
      array<double, 2>^ input_point,
      array<System::String^>^ bytes);

    void InverseProjectionPropBased(
      int n_reference_points,
      array<double, 2>^ arraypoints,
      array<double, 2>^ input_point,
      array<System::String^>^ bytes,
      int lyr_i_sz, int lyr_j_sz,
      array<double, 1>^ limits_prop_value);
    
    void InverseProjectionMultiPropBased (
      int input_prop_file,
      array<double, 2>^ input_point,
      int n_2d_control_points,
      array<double, 2>^ ar_control_points,
      array<System::String^>^ bytes,
      int number_of_properties,
      array<double, 2>^ min_max_properties);

   void InverseProjectionByLambda(
      int n_reference_points,
      array<double, 2>^ arraypoints,
      array<double, 2>^ input_point,
      array<System::String^>^ bytes,
      int lyr_i_sz, int lyr_j_sz,
      array<double, 1>^ limits_prop_value);

    void CalcNewPropGridByInverse();

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

  public ref class CppDistanceProp
  {
  public:
    CppDistanceProp ();
    ~CppDistanceProp ();

    void SetEnvironmentType (int env_type);
    void SetNumberOfPropertiesAndCases (int props, int cases);
    array<double, 1>^ SetMultiProjectionInputFilePaths(int type, int prop, array<System::String^>^ props, double i_min, double i_max);

    void SetMapSize (int i_size, int j_size);

    array<double, 1>^ SetInputFilePaths(
      array<System::String^>^ props, 
      array<System::String^>^ filters, 
      array<int>^ layers);
    
    array<double, 2>^ GetDistances ();

    void Clear ();
  
  private:
    DistanceProp* DProp;
  };

}
