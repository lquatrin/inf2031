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
#include "../InverseProjection/transferfunction.h"
#include "../InverseProjection/transferfunction.cpp"

CppWrapper::CppLAMPWrapper::CppLAMPWrapper()
{
  pCC = new LAMPClass();
}

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

void CppWrapper::CppInverseProjectionWrapper::InverseProjection01(
  int n_sets,
  int n_points_per_set,
  array<double, 2>^ set_points,
  array<double, 2>^ input_points,
  array<System::String^>^ bytes)
{
  double **m = (double**)malloc(n_points_per_set*n_sets * sizeof(double*));

  for (int i = 0; i < n_points_per_set*n_sets; i++)
  {
    m[i] = (double*)malloc(2 * sizeof(double));
    m[i][0] = set_points[i, 0];
    m[i][1] = set_points[i, 1];
  }

  std::vector<std::string> image_paths;
  for (int i = 0; i < bytes->Length; i++)
  {
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    image_paths.push_back(standardString);
  }


  double **p = (double**)malloc(n_sets * sizeof(double*));
  for (int i = 0; i < n_sets; i++)
  {
    p[i] = (double*)malloc(2 * sizeof(double));

    p[i][0] = input_points[i, 0];
    p[i][1] = input_points[i, 1];
  }

  pinvproj->CalcInverseProjection01(n_sets, n_points_per_set, 2, m, p, image_paths);

  for (int i = 0; i < n_points_per_set*n_sets; i++)
    free(m[i]);
  free(m);

  for (int i = 0; i < n_sets; i++)
    free(p[i]);
  free(p);
}

void CppWrapper::CppInverseProjectionWrapper::InverseProjection02(
  int n_sets,
  int n_points_per_set,
  array<double, 2>^ set_points,
  array<double, 2>^ input_points,
  array<System::String^>^ bytes)
{
  double **m = (double**)malloc(n_points_per_set*n_sets * sizeof(double*));

  for (int i = 0; i < n_points_per_set*n_sets; i++)
  {
    m[i] = (double*)malloc(2 * sizeof(double));
    m[i][0] = set_points[i, 0];
    m[i][1] = set_points[i, 1];
  }

  std::vector<std::string> image_paths;
  for (int i = 0; i < bytes->Length; i++)
  {
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    image_paths.push_back(standardString);
  }


  double **p = (double**)malloc(n_sets * sizeof(double*));
  for (int i = 0; i < n_sets; i++)
  {
    p[i] = (double*)malloc(2 * sizeof(double));

    p[i][0] = input_points[i, 0];
    p[i][1] = input_points[i, 1];
  }

  pinvproj->CalcInverseProjection02(n_sets, n_points_per_set, 2, m, p, image_paths);

  for (int i = 0; i < n_points_per_set*n_sets; i++)
    free(m[i]);
  free(m);

  for (int i = 0; i < n_sets; i++)
    free(p[i]);
  free(p);
}

void CppWrapper::CppInverseProjectionWrapper::InverseProjectionValBased (int n_reference_points,
                                                                         array<double, 2>^ arraypoints,
                                                                         array<double, 2>^ input_point,
                                                                         array<System::String^>^ bytes)
{
  double **m = (double**)malloc(n_reference_points * sizeof(double*));

  for (int i = 0; i < n_reference_points; i++)
  {
    m[i] = (double*)malloc(2 * sizeof(double));
    m[i][0] = arraypoints[i, 0];
    m[i][1] = arraypoints[i, 1];
  }

  std::vector<std::string> image_paths;
  for (int i = 0; i < bytes->Length; i++)
  {
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    image_paths.push_back(standardString);
  }


  double *p = (double*)malloc(2 * sizeof(double));
  p[0] = input_point[0, 0];
  p[1] = input_point[0, 1];

  pinvproj->CalcInverseProjectionValBased(n_reference_points, m, image_paths, p);

  for (int i = 0; i < n_reference_points; i++)
    free(m[i]);
  free(m);
  free(p);
}

void CppWrapper::CppInverseProjectionWrapper::InverseProjectionPropBased(int n_reference_points,
                                                                        array<double, 2>^ arraypoints,
                                                                        array<double, 2>^ input_point,
                                                                        array<System::String^>^ bytes, 
                                                                        int lyr_i_sz, int lyr_j_sz,
                                                                        array<double, 1>^ limits_prop_val)
{
  double **m = (double**)malloc(n_reference_points * sizeof(double*));

  for (int i = 0; i < n_reference_points; i++)
  {
    m[i] = (double*)malloc(2 * sizeof(double));
    m[i][0] = arraypoints[i, 0];
    m[i][1] = arraypoints[i, 1];
  }

  std::vector<std::string> image_paths;
  for (int i = 0; i < bytes->Length; i++)
  {
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    image_paths.push_back(standardString);
  }

  double *p = (double*)malloc(2 * sizeof(double));
  p[0] = input_point[0, 0];
  p[1] = input_point[0, 1];

  double *limits = (double*)malloc(2 * sizeof(double));
  limits[0] = limits_prop_val[0];
  limits[1] = limits_prop_val[1];

  pinvproj->CalcInverseProjectionPropBased(n_reference_points, m, image_paths, p, lyr_i_sz, lyr_j_sz, limits);

  for (int i = 0; i < n_reference_points; i++)
    free(m[i]);
  free(m);
  free(p);
}

void CppWrapper::CppInverseProjectionWrapper::CalcNewPropGridByInverse(void){
  
  pinvproj->CalcNewPropGridByInverse();
  pinvproj->ClearInverseArray();
}

CppWrapper::CppDistPixelWrapper::CppDistPixelWrapper(){
  pdists = new distpixel();
}

void CppWrapper::CppDistPixelWrapper::addPath(array<System::String^>^ bytes, int channel){
  std::vector<std::string> mpath;
  for (int i = 0; i < bytes->Length; i++){
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    mpath.push_back(standardString);
  }

  pdists->SetPaths(mpath, channel);
}

array<double, 2>^CppWrapper::CppDistPixelWrapper::GetDistances(void){

  std::vector<std::vector<double>> vec;
  std::vector<std::vector<double>>::iterator itr;
  pdists->getDist(vec);
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

void CppWrapper::CppDistPixelWrapper::testDists ()
{
  pdists->teste();
}

void CppWrapper::CppDistPixelWrapper::Clear ()
{
  pdists->clear();
}

CppWrapper::CppDistanceProp::CppDistanceProp ()
{
  DProp = new DistanceProp();
}

CppWrapper::CppDistanceProp::~CppDistanceProp ()
{
  delete DProp;
}

void CppWrapper::CppDistanceProp::SetMapSize (int i_size, int j_size)
{
  DProp->SetMapSize(i_size, j_size);
}

array<double, 1>^ CppWrapper::CppDistanceProp::SetInputFilePaths(array<System::String^>^ props, array<System::String^>^ filters, array<int>^ layers)
{
  DProp->Clear();

  std::vector<std::string> p_path;
  std::vector<std::string> f_path;
  std::vector<int> l_list;
 
  for (int i = 0; i < props->Length; i++)
  {
    {
      msclr::interop::marshal_context context;
      std::string standardString = context.marshal_as<std::string>(props[i]);
      p_path.push_back(standardString);
    }

    {
      msclr::interop::marshal_context context;
      std::string standardString = context.marshal_as<std::string>(filters[i]);
      f_path.push_back(standardString);
    }
    
    {
      int standardString = layers[i];
      l_list.push_back(standardString);
    }
  }

  double* data_limits = new double[2];

  DProp->SetPaths(p_path, f_path, l_list, data_limits);

  array<double, 1>^ Distances = gcnew array<double, 1>(2);

  Distances[0] = data_limits[0];
  Distances[1] = data_limits[1];
  delete[] data_limits;

  return Distances;
}

array<double, 2>^ CppWrapper::CppDistanceProp::GetDistances()
{
  std::vector<std::vector<double>> vec;
  std::vector<std::vector<double>>::iterator itr;
  
  DProp->GetDistance(vec);

  array<double, 2>^ Distances = gcnew array<double, 2>(vec.size(), vec.size());

  for (int i = 0; i < vec.size(); i++)
  {
    for (int j = 0; j < vec[i].size(); j++)
    {
      Distances[i, j] = vec[i][j];
    }
  }

  return Distances;
}

void CppWrapper::CppDistanceProp::Clear ()
{
  DProp->Clear();
}
