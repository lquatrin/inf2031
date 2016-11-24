#pragma once

#include <opencv2/core/core.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>
#include <stdio.h>

class InverseProjection
{
public:
  void test (void);
  void testCholesky (void);

  void CalcInverseProjection01(int number_of_charts, int n_points_per_chart, int dimension, double** points, double** input, std::vector<std::string> image_paths);

public:
  InverseProjection ();
  ~InverseProjection ();

  void ReadImages (std::vector<std::string> paths,int channel);

  void CalcInverseProjection (void);

  void Clear ();
  
  double RadialBasisKernel(double* X1, double* X2, double sigma);
  //void getDistMatrix(std::vector<std::vector<double>> &vec);

private:
  std::vector<cv::Mat> srcs;
  std::vector<cv::Mat> hsvs;
};

