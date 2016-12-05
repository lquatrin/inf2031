#include "distanceprop.h"

#include <iostream>
#include <fstream>

DistanceProp::DistanceProp ()
{
  i_size = 0;
  j_size = 0;
}

DistanceProp::~DistanceProp ()
{}

void DistanceProp::SetMapSize (int is, int js)
{
  i_size = is;
  j_size = js;
}

void DistanceProp::SetPaths (std::vector<std::string> property_paths, std::vector<std::string> filter_paths, std::vector<int> layers)
{
  if (!((property_paths.size() == filter_paths.size()) && (filter_paths.size() == layers.size()))) return;

  int n_maps = property_paths.size();

  for (int i = 0; i < property_paths.size(); i++)
  {
    prop_paths.push_back(property_paths[i]);
  }

  for (int i = 0; i < filter_paths.size(); i++)
    fltr_paths.push_back(filter_paths[i]);

  for (int i = 0; i < layers.size(); i++)
    lyrs_array.push_back(layers[i]);

  for (int t = 0; t < n_maps; t++ )
  {
    cv::Mat map = cv::Mat::zeros(j_size, i_size, cv::DataType<double>::type);
    
    std::ifstream propfile;
    propfile.open(prop_paths[t]);

    int skip = i_size * j_size * (lyrs_array[t] - 1);

    double val;
    for (int j = 0; j < j_size; j++)
      for (int i = 0; i < i_size && propfile >> val; i++)
        map.at<double>(j, i) = val;

    propfile.close();

    prop_maps.push_back(map);
  }
}

void DistanceProp::GetDistance (std::vector<std::vector<double>> &distMat)
{
  if (prop_paths.size() == 0) return;

  int n = prop_maps.size();
  int s_i = i_size, s_j = j_size;
  
  double min = 0;
  double max = 0;
  
  for (int i = 0; i < n; i++)
  {
    std::vector<double> d;
    for (int j = 0; j < n; j++)
    {
      double sum = 0;
      //Calcula a soma apenas dos valores que são positivos
      for (int k = 0; k < s_j; k++)
        for (int w = 0; w < s_i; w++)
          if (prop_maps[i].at<double>(k, w) >= 0 && prop_maps[j].at<double>(k, w) >= 0)
            sum += pow(prop_maps[i].at<double>(k, w) - prop_maps[j].at<double>(k, w), 2);
      
      sum = sqrt(sum);

      if (max < sum) max = sum;
      if (min > sum) min = sum;

      d.push_back(sum);
    }
    distMat.push_back(d);
  }

  for (int i = 0; i < distMat.size(); i++){
    for (int j = 0; j < distMat[i].size(); j++){
      double z = (distMat[i][j] - min) / (max - min);
      distMat[i][j] = z;
    }
  }
}

void DistanceProp::Clear ()
{
  prop_paths.clear();
  fltr_paths.clear();
  lyrs_array.clear();
  prop_maps.clear();
}