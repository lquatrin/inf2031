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

  void SetPaths (std::vector<std::string> property_paths, std::vector<std::string> filter_paths, std::vector<int> layers);

  void GetDistance (std::vector<std::vector<double>> &distMat);
  
  void Clear ();
private:
  std::vector<std::string> prop_paths;
  std::vector<std::string> fltr_paths;
  std::vector<int> lyrs_array;

  std::vector<cv::Mat> prop_maps;

  unsigned int i_size, j_size;
};

