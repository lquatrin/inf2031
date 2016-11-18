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

  cv::Mat ilamp (const cv::Mat& X, const cv::Mat& Y, const unsigned int k, const cv::Mat& p);

private:
  std::vector<int> vec;
};