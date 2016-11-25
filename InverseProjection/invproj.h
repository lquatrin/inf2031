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
  void testLU (void);

  void GenInverseProjection (
    int n_sets,
    int n_points_per_set,
    int dimension,
    double** set_points,
    double** input_points,
    std::vector<std::string> image_paths);

  void CalcInverseProjection01(
    int n_sets,
    int n_points_per_set,
    int dimension, 
    double** set_points,
    double** input_points,
    std::vector<std::string> image_paths);

public:
  InverseProjection ();
  ~InverseProjection ();

  void ReadImages (std::vector<std::string> paths,int channel);

  void CalcInverseProjection (void);

  void Clear ();
  
  double RadialBasisKernel(double* X1, double* X2);
  //void getDistMatrix(std::vector<std::vector<double>> &vec);

  int input_colorspace;

  cv::Mat LUDecomp(cv::Mat& A);
  cv::Mat PLUDecomp (cv::Mat& A);
  cv::Mat LUSolve (cv::Mat A, cv::Mat P, cv::Mat b);
  cv::Mat LUEvalB (cv::Mat A, cv::Mat P, cv::Mat X);



  void CalcInverseProjection02(
    int n_sets,
    int n_points_per_set,
    int dimension,
    double** set_points,
    double** input_points,
    std::vector<std::string> image_paths);

private:
  cv::Mat ConvertBGRToInputColorSpace (cv::Mat ipt, int type);
  cv::Mat ConvertInputColorSpaceToBGR (cv::Mat ipt, int type);

  double rad_kernel_gama;

  std::vector<cv::Mat> srcs;
  std::vector<cv::Mat> hsvs;
};

