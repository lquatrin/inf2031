#include <vector>
#include <opencv2/core/core.hpp>


#pragma once
class MDSClass
{
public:
  MDSClass(int* pInt, int arrSize);
  ~MDSClass() {}

  cv::Mat cmdscale(const cv::Mat& dist, const int k, const cv::Mat* eigenvals = NULL, const cv::Mat* eigenvecs = NULL);
  void mdsTest();

private:
  std::vector<int> vec;
};