#pragma once

#include<vector>
#include <string>
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <math.h>

class distpixel
{
public:
  distpixel();
  ~distpixel(){};
  void SetPaths(std::vector<std::string> image_paths,int channel);
  void getDist(std::vector<std::vector<double>> &distMat);
  void teste();
  void clear();
private:
  std::vector<std::string> paths;
  std::vector<cv::Mat> srcs;
  std::vector<cv::Mat> hsvs;
  int ch;
};

