#pragma once
#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>



class Histogram
{
public:
  Histogram();
  ~Histogram(){}
  void ReadImages(std::vector<std::string> paths);
  void CalcHistogram(void);
  void getDistMatrix(std::vector<std::vector<double>> &vec);
  void test(void);

private:
  std::vector<cv::Mat> srcs;
  std::vector<cv::Mat> hsvs;
  std::vector<cv::MatND> hists;
};

