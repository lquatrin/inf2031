#include "distanceprop.h"

#include <iostream>
#include <fstream>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

DistanceProp::DistanceProp ()
{
  i_size = 0;
  j_size = 0;

  environment_type = 0;
}

DistanceProp::~DistanceProp ()
{}

void DistanceProp::SetMapSize (int is, int js)
{
  i_size = is;
  j_size = js;
}

void DistanceProp::SetPaths(std::vector<std::string> property_paths, std::vector<std::string> filter_paths, std::vector<int> layers, double* data_limits)
{
  if (!((property_paths.size() == filter_paths.size()) && (filter_paths.size() == layers.size()))) return;

  int n_maps = property_paths.size();

  prop_paths.insert(prop_paths.end(), property_paths.begin(), property_paths.end());


  for (int i = 0; i < filter_paths.size(); i++)
    fltr_paths.push_back(filter_paths[i]);

  for (int i = 0; i < layers.size(); i++)
    lyrs_array.push_back(layers[i]);

  double max_value = -99999999;
  double min_value = 99999999;
  for (int t = 0; t < n_maps; t++ )
  {
    cv::Mat map = cv::Mat::zeros(j_size, i_size, cv::DataType<double>::type);
    
    std::ifstream propfile;
    propfile.open(prop_paths[t]);

    int skip = i_size * j_size * (lyrs_array[t] - 1);

    double val;
    for (int j = 0; j < j_size; j++)
    {
      for (int i = 0; i < i_size && propfile >> val; i++)
      {
        map.at<double>(j, i) = val;
        if (val > -1)
        {
          max_value = MAX(max_value, val);
          min_value = MIN(min_value, val);
        }
      }
    }

    propfile.close();

    propty_maps.push_back(map);
  }
  data_limits[0] = min_value;
  data_limits[1] = max_value;
}

void DistanceProp::GetDistance (std::vector<std::vector<double>> &distMat)
{
  if (environment_type == 1)
  {
    GetMultiPropertyDistance(distMat);
    return;
  }

  if (prop_paths.size() == 0) return;

  int n = propty_maps.size();
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
      {
        for (int w = 0; w < s_i; w++)
        {
          if (propty_maps[i].at<double>(k, w) > -1 && propty_maps[j].at<double>(k, w) > -1)
          {
            sum += pow(propty_maps[i].at<double>(k, w) - propty_maps[j].at<double>(k, w), 2);
          }
        }
      }
      
      sum = sqrt(sum);

      if (max < sum) max = sum;
      if (min > sum) min = sum;
      if (max == min){
        min -= 1;
        max += 1;
      }

      d.push_back(sum);

    }
    distMat.push_back(d);
  }

  /*for (int i = 0; i < distMat.size(); i++){
    for (int j = 0; j < distMat[i].size(); j++){
     
      double z = (distMat[i][j] - min) / (max - min);

      distMat[i][j] = z;
      
      printf("%g ", z);
    }
    printf("\n ");
  }*/
}

void DistanceProp::SetEnvironmentType (int env_type)
{
  environment_type = env_type;
  Clear();
}

void DistanceProp::SetNumberOfPropertiesAndCases (int props, int cases)
{
  env_props = props;
  env_cases = cases;
}

void DistanceProp::AddMultiPropPaths (std::vector<std::string> property_paths, double inp_min, double inp_max, int type)
{
  int n_maps = property_paths.size();
  prop_paths.insert(prop_paths.end(), property_paths.begin(), property_paths.end());

  MinMaxDistanceMP mm_values;
  if (inp_min == inp_max)
  {
    mm_values.max = -99999999;
    mm_values.min = 99999999;
  }
  else
  {
    mm_values.min = inp_min;
    mm_values.max = inp_max;
  }
  
  for (int t = 0; t < n_maps; t++)
  {
    cv::Mat map = cv::Mat::zeros(j_size, i_size, cv::DataType<double>::type);
    cv::Mat filter = cv::Mat::zeros(j_size, i_size, cv::DataType<int>::type);

    std::ifstream propfile;
    propfile.open(property_paths[t]);

    if (type == 1)
    {
      int x,y;
      double val;
      while (propfile >> x && propfile >> y && propfile >> val)
      {
        map.at<double>(x, y) = val;
        filter.at<int>(x, y) = 1;
        mm_values.max = MAX(mm_values.max, val);
        mm_values.min = MIN(mm_values.min, val);
      }
    }
    else
    {
      double val;
      for (int j = 0; j < j_size; j++)
      {
        for (int i = 0; i < i_size && propfile >> val; i++)
        {
          map.at<double>(j, i) = val;
          
          if (val > -1)
          {
            filter.at<int>(j, i) = 1;
            mm_values.max = MAX(mm_values.max, val);
            mm_values.min = MIN(mm_values.min, val);
          }
        }
      }
    }

    propfile.close();

    propty_maps.push_back(map);
    filter_maps.push_back(filter);
  }

  mp_min_max_values.push_back(mm_values);
}

void DistanceProp::Clear ()
{
  prop_paths.clear();
  fltr_paths.clear();
  lyrs_array.clear();
  propty_maps.clear();
  filter_maps.clear();
  mp_min_max_values.clear();
}

void DistanceProp::GetMultiPropertyDistance(std::vector<std::vector<double>> &distMat)
{
  int n_p = env_props;
  int n = env_cases;
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
      {
        for (int w = 0; w < s_i; w++)
        {
          // Para todas as propriedades
          // Soma tudo
           for (int kprop = 0; kprop < n_p; kprop++)
          {
            if (filter_maps[i + kprop * n].at<int>(k, w) && filter_maps[j + kprop * n].at<int>(k, w))
            {
              //Normaliza cada propriedade, baseado no mínimo e máximo calculado ao definir os arquivos.
              sum += pow(
              ((propty_maps[i + kprop * n].at<double>(k, w) - mp_min_max_values[kprop].min) / (mp_min_max_values[kprop].max - mp_min_max_values[kprop].min))
              -
              ((propty_maps[j + kprop * n].at<double>(k, w) - mp_min_max_values[kprop].min) / (mp_min_max_values[kprop].max - mp_min_max_values[kprop].min))
              , 2);
            }
          }
        }
      }

      sum = sqrt(sum);
      d.push_back(sum);
    }
    distMat.push_back(d);
  }

}

void DistanceProp::GetMinMaxPropValue(int prop, double* min, double* max)
{
  (*min) = mp_min_max_values[prop].min;
  (*max) = mp_min_max_values[prop].max;
}
