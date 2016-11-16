#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

class LAMPClass
{
public:
  LAMPClass(int* pInt, int arrSize);
  ~LAMPClass() {}

  double SumArray();

  cv::Mat lamp(const cv::Mat& X, const std::vector<int> cp_index, const cv::Mat& Ys);

  void lampTest();

private:
  std::vector<int> vec;
};