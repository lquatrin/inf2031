#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

class LAMPClass
{
public:
  LAMPClass();
  LAMPClass(int* pInt, int arrSize);
  LAMPClass(double** pInt, int arrSize);
  ~LAMPClass() {}

  double SumArray();

  cv::Mat lamp(const cv::Mat& X, const std::vector<int> cp_index, const cv::Mat& Ys);

  std::vector<std::vector<double>> calcLAMP(void);

  void lampTest();
  void PrintCVMAT(cv::Mat m);
  cv::Mat ilamp (const cv::Mat& X, const cv::Mat& Y, const unsigned int k, const cv::Mat& p);

private:
  std::vector<int> vec;
};