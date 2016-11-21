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

void CppWrapper::CppHistogramWrapper::addPath(array<System::String^>^ bytes){
	std::vector<std::string> mpath;
	for (int i = 0; i < bytes->Length; i++){
		printf("%s\n", bytes[i]);
		msclr::interop::marshal_context context;
		std::string standardString = context.marshal_as<std::string>(bytes[i]);
		mpath.push_back(standardString);
	}

	pHistogram->ReadImages(mpath);
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
		}
	}
	printf("tamanho %d\n", Distances->Length);
	return Distances;
}

void CppWrapper::CppHistogramWrapper::testHistogram()
{
	pHistogram->test();
}