
#include <iostream>
#include "mds.h"

#pragma once
using cv::Mat;


static bool s_CheckInpuErrorsMDS(const Mat& dist)
{
  const char* msg_prefix = "ERROR: s_CheckInpuErrorsMDS -";
  if (dist.rows != dist.cols) {
    fprintf(stderr, "%s Matrix is not square [%d, %d].\n", msg_prefix, dist.rows, dist.cols);
    return false;
  }

  if (dist.rows < 3) {
    fprintf(stderr, "%s Too few samples provided (%d). Must have 3 or more samples.\n", msg_prefix, dist.rows);
    return false;
  }

  Mat cmpop = dist != dist.t();
  if (cv::sum(cmpop)[0] != 0) {
    fprintf(stderr, "%s Matrix is not symmetric.\n", msg_prefix);
    return false;
  }
  return true;
}


MDSClass::MDSClass(int* pInt, int arrSize){
  for (int i = 0; i < arrSize; i++)
  {
    vec.push_back(pInt[i]);
  }
}


Mat MDSClass::cmdscale(const Mat& dist, const int k, const Mat* eigenvals, const Mat* eigenvecs)
{
  if (!s_CheckInpuErrorsMDS(dist)) {
    fprintf(stderr, "ERROR: cmdscale - Invalid input.\n");
    return Mat::zeros(1, 1, CV_8UC1);
  }

  int sz = dist.total();
  Mat pow_dist;

  cv::pow(dist, 2, pow_dist);
  Mat centering = Mat::eye(dist.cols, dist.cols, dist.depth()) - Mat::ones(dist.cols, dist.cols, dist.depth()) * (1.f / dist.cols);
  Mat B = centering * pow_dist * centering * 0.5f;

  Mat evals;
  Mat evecs;
  cv::eigen(B, evals, evecs);

  if (eigenvals != NULL)
    eigenvals = new Mat(evals);

  if (eigenvecs != NULL)
    eigenvecs = new Mat(evecs);

  Mat sqrt_evals = Mat::diag(evals.rowRange(evals.rows - k, evals.rows));
  cv::sqrt(cv::abs(sqrt_evals), sqrt_evals);
  evecs = evecs.rowRange(evecs.rows - k, evecs.rows);
  Mat mds_points = evecs.t() * sqrt_evals;
  cv::flip(mds_points, mds_points, 1);

  return mds_points;
}


void MDSClass::mdsTest()
{
  float d[4][4] = {
    { 0, 93, 82, 133 },
    { 93, 0, 52, 60 },
    { 82, 52, 0, 111 },
    { 133, 60, 111, 0 }
  };

  Mat dist = Mat(4, 4, CV_32FC1, d);
  Mat evals;
  Mat evecs;
  Mat P = cmdscale(dist, 2, &evals, &evecs);

  printf("Result of MDS:\n - Matrix P: [%d, %d]\n", P.rows, P.cols);

  for (int k = 0; k < P.rows; ++k)
  {
    for (int c = 0; c < P.cols; ++c)
    {
      printf("%.2f ", P.at<float>(k, c));
    }
    printf("\n");
  }

}
