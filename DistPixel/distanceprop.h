#pragma once

#include<vector>
#include <string>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>

class DistanceProp
{
public:
  DistanceProp ();
  ~DistanceProp ();

  void SetMapSize (int is, int js);

  void SetPaths (std::vector<std::string> property_paths, std::vector<std::string> filter_paths, std::vector<int> layers, double* data_limits);

  void GetDistance (std::vector<std::vector<double>> &distMat);
  
  void SetEnvironmentType (int env_type);
  void SetNumberOfPropertiesAndCases (int props, int cases);
  void AddMultiPropPaths (std::vector<std::string> props);

  void Clear ();
private:
  void GetMultiPropertyDistance (std::vector<std::vector<double>> &distMat);
  std::vector<std::string> prop_paths;
  std::vector<std::string> fltr_paths;
  std::vector<int> lyrs_array;

  std::vector<cv::Mat> prop_maps;

  // 0 -> Single Property
  // 1 -> Multi Properties
  int environment_type;

  class MinMaxDistanceMP
  {
  public:
    double min;
    double max;
  };
  std::vector<MinMaxDistanceMP> mp_min_max_values;

  int env_props;
  int env_cases;

  unsigned int i_size, j_size;
};

