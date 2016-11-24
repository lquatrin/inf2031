// This is the main DLL file.

#include "stdafx.h"

#include "CppWrapper.h"

#include "../LAMP/lamp.h"
#include "../LAMP/lamp.cpp"
#include "../LAMP/lamp_f.cpp"

#include "../MDS/mds.h"
#include "../MDS/mds.cpp"

#include "../InverseProjection/invproj.h"
#include "../InverseProjection/invproj.cpp"

CppWrapper::CppLAMPWrapper::CppLAMPWrapper(int *pInt, int arraySize)
{
	pCC = new LAMPClass(pInt, arraySize);
}

CppWrapper::CppLAMPWrapper::CppLAMPWrapper (array<double, 2>^ tvalues, int arraySize)
{
  dists = tvalues;
  double **m = (double**)malloc(arraySize * sizeof(double*));

  for (int i = 0; i < arraySize; i++){
    m[i] = (double*)malloc(arraySize * sizeof(double));
    for (int j = 0; j < arraySize; j++){
      m[i][j] = tvalues[i, j];
    }
  }

  pCC = new LAMPClass(m, arraySize);
  std::vector<std::vector<double>> vec = pCC->calcLAMP();
  for (int i = 0; i < vec.size(); i++){
    for (int j = 0; j < vec[i].size(); j++){
      dists[i, j] = vec[i][j];
    }
  }
}

array<double, 2>^ CppWrapper::CppLAMPWrapper::GetLAMP ()
{
  return dists;
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


CppWrapper::CppMDSWrapper::CppMDSWrapper(array<double, 2>^ tvalues, int arraySize)
{
	dists = tvalues;
	double **m = (double**)malloc(arraySize * sizeof(double*)); 

	for (int i = 0; i < arraySize; i++){
		m[i] = (double*)malloc(arraySize * sizeof(double)); 
		for (int j = 0; j < arraySize; j++){ 
			m[i][j] = tvalues[i, j];
		}
	}

	pMDS = new MDSClass(m, arraySize);
	std::vector<std::vector<double>> vec = pMDS->calcMDS();
	for (int i = 0; i < vec.size(); i++){
		for (int j = 0; j < vec[i].size(); j++){
			dists[i, j] = vec[i][j];
		}
	}
}


array<double, 2>^ CppWrapper::CppMDSWrapper::GetMDS()
{
	return dists;
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
void CppWrapper::CppHistogramWrapper::CreateHistogram(char** ppNames, int iNbOfNames){

}

void CppWrapper::CppHistogramWrapper::addPath(array<System::String^>^ bytes,int channel){
	std::vector<std::string> mpath;
	for (int i = 0; i < bytes->Length; i++){
#ifdef _DEBUG
		printf("%s\n", bytes[i]);
#endif
    msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(bytes[i]);
		mpath.push_back(standardString);
	}

	pHistogram->ReadImages(mpath,channel);
	pHistogram->CalcHistogram();
}

array<double, 2>^CppWrapper::CppHistogramWrapper::GetDistances(void){

	std::vector<std::vector<double>> vec;
	std::vector<std::vector<double>>::iterator itr;
	pHistogram->getDistMatrix(vec);
	array<double, 2>^ Distances = gcnew array<double, 2>(vec.size(), vec.size());

 
	for (int i = 0; i < vec.size(); i++){
		for (int j = 0; j < vec[i].size(); j++){
			Distances[i, j] = vec[i][j];
#ifdef _DEBUG
      printf("%g\n", vec[i][j]);
#endif
    }
	}
#ifdef _DEBUG
	printf("tamanho %d\n", Distances->Length);
#endif
  return Distances;
}

void CppWrapper::CppHistogramWrapper::testHistogram()
{
	pHistogram->test();
}

void CppWrapper::CppHistogramWrapper::Clear()
{
  pHistogram->Clear();
}

CppWrapper::CppInverseProjectionWrapper::CppInverseProjectionWrapper ()
{
  pinvproj = new InverseProjection();
}

void CppWrapper::CppInverseProjectionWrapper::SetInputColorScapeType (int type)
{
  pinvproj->input_colorspace = type;
}

void CppWrapper::CppInverseProjectionWrapper::InverseProjection01(array<double, 2>^ t_points,
  int n_points_per_series,
  int number_of_charts,
  array<System::String^>^ bytes,
  array<double, 2>^ input_point)
{
  double **m = (double**)malloc(n_points_per_series*number_of_charts * sizeof(double*));

  for (int i = 0; i < n_points_per_series*number_of_charts; i++)
  {
    m[i] = (double*)malloc(2 * sizeof(double));
    m[i][0] = t_points[i, 0];
    m[i][1] = t_points[i, 1];
  }

  std::vector<std::string> image_paths;
  for (int i = 0; i < bytes->Length; i++)
  {
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    image_paths.push_back(standardString);
  }


  double **p = (double**)malloc(number_of_charts * sizeof(double*));
  for (int i = 0; i < number_of_charts; i++)
  {
    p[i] = (double*)malloc(2 * sizeof(double));

    p[i][0] = input_point[i, 0];
    p[i][1] = input_point[i, 1];
  }

  pinvproj->CalcInverseProjection01(number_of_charts, n_points_per_series, 2, m, p, image_paths);

  for (int i = 0; i < n_points_per_series*number_of_charts; i++)
    free(m[i]);
  free(m);

  for (int i = 0; i < number_of_charts; i++)
    free(p[i]);
  free(p);
}