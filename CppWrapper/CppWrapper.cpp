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

array<double, 2>^ CppWrapper::CppLAMPWrapper::GetLAMP(array<double, 2>^ tvalues, array<double, 2>^ controlPoints, array<int>^controlsidx, int controlsize, int arraySize)
{
  dists = tvalues;
  double **m = (double**)malloc(arraySize * sizeof(double*));
  double **cpoints = (double**)malloc(controlsize * sizeof(double*));
  int *cindex = (int*)malloc(controlsize * sizeof(int));

  for (int i = 0; i < arraySize; i++){
    m[i] = (double*)malloc(2 * sizeof(double));
    for (int j = 0; j < 2; j++){
      m[i][j] = tvalues[i, j];
    }
  }

  for (int i = 0; i < controlsize; i++){
	  cpoints[i] = (double*)malloc(2 * sizeof(double));
	  cindex[i] = controlsidx[i];
	  for (int j = 0; j < 2; j++){
		  cpoints[i][j] = controlPoints[i, j];
	  }
  }

  pCC = new LAMPClass();
  std::vector<std::vector<double>> vec = pCC->calcLAMP(m,cindex,cpoints,arraySize,controlsize);
  
  for (int i = 0; i < vec.size(); i++){
    for (int j = 0; j < vec[i].size(); j++){
		dists[i, j] = vec[i][j];
    }
  }

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

void CppWrapper::CppInverseProjectionWrapper::SetModelSize (int width, int height, int depth)
{
  pinvproj->SetModelSize(width, height, depth);
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

  printf("calling sheppard!");
  pinvproj->CalcInverseProjectionPropBased(n_reference_points, m, image_paths, p, lyr_i_sz, lyr_j_sz, limits);

  for (int i = 0; i < n_reference_points; i++)
    free(m[i]);
  free(m);
  free(p);
}

void CppWrapper::CppInverseProjectionWrapper::InverseProjectionMultiPropBased (
  int input_prop_file,
  array<double, 2>^ input_point,
  int n_2d_control_points,
  array<double, 2>^ ar_control_points,
  array<System::String^>^ bytes,
  int number_of_properties,
  array<double, 2>^ min_max_properties)
{
  
  double **i_control_points = (double**)malloc(n_2d_control_points * sizeof(double*));
  for (int i = 0; i < n_2d_control_points; i++)
  {
    i_control_points[i] = (double*)malloc(2 * sizeof(double));
    i_control_points[i][0] = ar_control_points[i, 0];
    i_control_points[i][1] = ar_control_points[i, 1];
  }

  double *p = (double*)malloc(2 * sizeof(double));
  p[0] = input_point[0, 0];
  p[1] = input_point[0, 1];
  

  std::vector<std::string> prop_paths;
  for (int i = 0; i < bytes->Length; i++)
  {
    msclr::interop::marshal_context context;
    std::string standardString = context.marshal_as<std::string>(bytes[i]);
    prop_paths.push_back(standardString);
  }

  double *limits = (double*)malloc(number_of_properties * 2 * sizeof(double));
  for (int i = 0; i < number_of_properties; i++)
  {
    limits[0 + i*2] = min_max_properties[i, 0];
    limits[1 + i*2] = min_max_properties[i, 1];
  }

  printf("chameiiiiiiiii\n");
  pinvproj->CalcInverseProjectionMultiPropBased(input_prop_file
    , number_of_properties
    , n_2d_control_points
    , i_control_points
    , p 
    , prop_paths
    , limits
  );


  for (int i = 0; i < n_2d_control_points; i++)
    free(i_control_points[i]);
  free(i_control_points);
  free(p);
  free(limits);
}

void CppWrapper::CppInverseProjectionWrapper::InverseProjectionByLambda(int n_reference_points,
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

  pinvproj->CalcByLambdas(n_reference_points, m, image_paths, p, lyr_i_sz, lyr_j_sz, limits);

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

void CppWrapper::CppDistanceProp::SetEnvironmentType (int env_type)
{ 
  DProp->SetEnvironmentType(env_type);
}

void CppWrapper::CppDistanceProp::SetNumberOfPropertiesAndCases (int props, int cases)
{
  DProp->SetNumberOfPropertiesAndCases(props, cases);
}

array<double, 1>^ CppWrapper::CppDistanceProp::SetMultiProjectionInputFilePaths(int type, int prop, array<System::String^>^ props, double i_min, double i_max)
{
  std::vector<std::string> p_path;
  for (int i = 0; i < props->Length; i++)
  {
    {
      msclr::interop::marshal_context context;
      std::string standardString = context.marshal_as<std::string>(props[i]);
      p_path.push_back(standardString);
    }
  }
  DProp->AddMultiPropPaths(p_path, i_min, i_max, type);

  array<double, 1>^ ret_min_max = gcnew array<double, 1>(2);

  double m1, m2;
  DProp->GetMinMaxPropValue(prop, &m1, &m2);

  ret_min_max[0] = m1;
  ret_min_max[1] = m2;

  return ret_min_max;
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
