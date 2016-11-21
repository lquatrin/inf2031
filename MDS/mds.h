#include <vector>
#include <opencv2/core/core.hpp>


#pragma once
class MDSClass
{
public:
  MDSClass(double** pInt, int arrSize);
  ~MDSClass() {}
  std::vector<std::vector<double>> calcMDS(void);
  cv::Mat cmdscale(const cv::Mat& dist, const int k, const cv::Mat* eigenvals = NULL, const cv::Mat* eigenvecs = NULL);
  void mdsTest();
  void Clear();
private:
  std::vector<int> vec;
  cv::Mat mdists;
};