#pragma once

#include <vector>

#include <opencv2/core/core.hpp>

class CppLAMP
{
public:
  CppLAMP ();
  ~CppLAMP ();

  cv::Mat lamp(const cv::Mat& X, const std::vector<int> cp_index, const cv::Mat& Ys);

  void testLAMP();

private:
  std::vector<int> vec;
};