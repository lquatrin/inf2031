#pragma once

#include "lamp.h"

#include <vector>
#include <cmath>

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
cv::Mat LAMPClass::ilamp(const cv::Mat& X, const cv::Mat& Y, const unsigned int k, const cv::Mat& p)
{
  // Steps:
  // 1 - Find k closest neighbors to p among the instances in Y, named as Ys = {y1, ... , yk}.
  //     Also Xs = {x1, ... , xk} is dataset containing the correspondent high-dimensional instances on X.
  std::vector<int> neighbors(k);
  for (int i = 0; i < k; ++i)
    //TODO: REFAZER VIZINHOS
    neighbors[i] = i;

  cv::Mat Ys = cv::Mat::zeros(k, Y.cols, CV_32FC1);
  for (int i = 0; i < k; ++i)
    Ys.row(i) = Y.row(neighbors[i]);

  cv::Mat Xs = cv::Mat::zeros(k, X.cols, CV_32FC1);
  for (int i = 0; i < k; ++i)
    Xs.row(i) = X.row(neighbors[i]);

  // 2 - Evaluate for each neighbor: alpha_i = (1 / abs(y_i - p)^2)
  cv::Mat alpha = cv::Mat::zeros(1, k, CV_32FC1);
  //for (int i = 0; i < k; ++i)
  //  alpha.at<float>(0, i) = (1.0f / (Ys.row(i) - p)*(Ys.row(i) - p));

  // 3 - t = x~ - y~ * M, with: x~ = (SUM_{i=1, k} alpha_i * x_i) / (SUM_{i=1, k} alpha_i), y~ = (SUM_{i=1, k} alpha_i * y_i) / (SUM_{i=1, k} alpha_i)
  cv::Mat x_t;
  cv::Mat y_t;
  
  // 4 - Evaluate x^_i = x_i - x~ and y^_i = y_i - y~
  cv::Mat x_c = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
  for (int i = 0; i < k; i++)
    x_c.row(i) = Xs.row(i) - x_t;

  cv::Mat y_c = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
  for (int i = 0; i < k; i++)
    y_c.row(i) = Ys.row(i) - y_t;

  // 5 - Build A and B
  cv::Mat A;
  y_c.copyTo(A);
  //multiplicar por sqrt(alfai)

  cv::Mat B;
  x_c.copyTo(B);
  //multiplicar por sqrt(alfai)

  // 6 - SVD of At*B to compute M as M = U*V
  // cv::SVD turns a Matrix H into  u*w*vt
  cv::SVD udv(A.t() * B);
  cv::Mat M = udv.u * udv.vt;

  // 7 - q = f(p) = (p - y~) * M + x~
  cv::Mat q = (p - y_t) * M + x_t;

  return q;
}