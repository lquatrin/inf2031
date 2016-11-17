#pragma once

#include "lamp.h"

#include <vector>

#include <opencv2/core/core_c.h>

LAMPClass::LAMPClass(int* pInt, int arrSize)
{
  for (int i = 0; i < arrSize; i++)
  {
    vec.push_back(pInt[i]);
  }
}

double LAMPClass::SumArray()
{
  int sum = 0;
  for (int i = 0; i < vec.size(); i++)
  {
    sum += vec[i];
  }
  return (double)sum;
}


// iLAMP maps a point 'p' on the screen (usually R^2) into a high-dimensional vector 'q' (R^m).
// Find affine transformation f(p) = pM + t that minimizes SUM_{i=1, k} alpha_i * abs(f(y_i) - x_i)^2
// \param X dataset X C R^m with the original instances in the high dimensional space.
// \param Y dataset Y C R^n with the instances projected into the visual space.
// \param k neigbors around the point 'p' that will be used to generate the inverse projection.
// \param p instance in the visual space
// \param p_dimension dimension space of 'p' instance
cv::Mat LAMPClass::ilamp (const cv::Mat& X, const cv::Mat& Y, const unsigned int k, float* p, int p_dimension)
{
  // Steps:
  // 1 - Find k closest neighbors to p among the instances in Y, named as Ys = {y1, ... , yk}.
  //     Also Xs = {x1, ... , xk} is dataset containing the correspondent high-dimensional instances on X.

  // 2 - Evaluate for each neighbor: alpha_i = (1 / abs(y_i - p)^2)

  // 3 - t = x~ - y~ * M, with: x~ = (SUM_{i=1, k} alpha_i * x_i) / (SUM_{i=1, k} alpha_i), y~ = (SUM_{i=1, k} alpha_i * y_i) / (SUM_{i=1, k} alpha_i)

  // 4 - Evaluate x^_i = x_i - x~ and y^_i = y_i - y~

  // 5 - Build A and B

  // 6 - SVD of At*B to compute M as M = U*V

  // 7 - q = f(p) = (p - y~) * M + x~
}