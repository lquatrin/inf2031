#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

class computingClass
{
public:
  computingClass(int* pInt, int arrSize);
  ~computingClass() {}

  double SumArray();

  cv::Mat lamp(const cv::Mat& X, const std::vector<int> cp_index, const cv::Mat& Ys);

  void lampTest();

private:
  std::vector<int> vec;
};