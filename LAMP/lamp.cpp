#pragma once

#include "lamp.h"

#include <vector>
#include <cmath>

#include <opencv2/core/core_c.h>

#define TOLERANCE 1E-003

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
  // -> TODO
  // 1 - Find k closest neighbors to p among the instances in Y, named as Ys = {y1, ... , yk}.
  //     Also Xs = {x1, ... , xk} is dataset containing the correspondent high-dimensional instances on X.
  std::vector<int> neighbors(k);
  for (int i = 0; i < k; ++i)
    //TODO: REFAZER VIZINHOS
    neighbors[i] = i;

  // 2 - Create Ys and Xs with the neighbors of the point p
  cv::Mat Ys = cv::Mat::zeros(k, Y.cols, CV_32FC1);
  for (int i = 0; i < k; i++)
    Ys.row(i) = Y.row(neighbors[i]);

  cv::Mat Xs = cv::Mat::zeros(k, X.cols, CV_32FC1);
  for (int i = 0; i < k; ++i)
    Xs.row(i) = X.row(neighbors[i]);

  // 3 - Evaluate for each neighbor: alpha_i = (1 / norm(y_i - p)^2)
  cv::Mat alpha = cv::Mat::zeros(1, k, CV_32FC1);
  for (int i = 0; i < k; ++i)
    alpha.at<float>(0, i) = 1 / cv::max(cv::norm(Ys.row(i), p), TOLERANCE);

  // 4 - t = x~ - y~ * M, with: x~ = (SUM_{i=1, k} alpha_i * x_i) / (SUM_{i=1, k} alpha_i), y~ = (SUM_{i=1, k} alpha_i * y_i) / (SUM_{i=1, k} alpha_i)
  cv::Mat a_xi = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
  for (int i = 0; i < Xs.rows; i++)
    a_xi.row(i) = alpha.at<float>(0, i) * Xs.row(i);

  cv::Mat a_yi = cv::Mat::zeros(Ys.rows, Ys.cols, Ys.depth());
  for (int i = 0; i < Ys.rows; i++)
    a_yi.row(i) = alpha.at<float>(0, i) * Ys.row(i);

  float sum_alpha = 0.0f;
  for (int i = 0; i < alpha.cols; i++)
    sum_alpha += alpha.at<float>(0, i);

  cv::Mat x_t;
  //Sum each component of each alphai*xi, resulting into a single row
  // cv::reduce dim = 0 to reduce into a single row
  cv::reduce(a_xi, x_t, 0, CV_REDUCE_SUM);
  x_t = x_t / sum_alpha;

  cv::Mat y_t;
  //Sum each component of each alphai*yi, resulting into a single row
  // cv::reduce dim = 0 to reduce into a single row
  cv::reduce(a_yi, y_t, 0, CV_REDUCE_SUM);
  y_t = y_t / sum_alpha;

  // 5 - Evaluate x^_i = x_i - x~ and y^_i = y_i - y~
  cv::Mat x_c = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
  for (int i = 0; i < k; i++)
    x_c.row(i) = Xs.row(i) - x_t;

  cv::Mat y_c = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
  for (int i = 0; i < k; i++)
    y_c.row(i) = Ys.row(i) - y_t;

  // 6 - Build A and B
  cv::Mat sqrt_alpha;
  cv::sqrt(alpha, sqrt_alpha);

  cv::Mat A;
  y_c.copyTo(A);
  for (int i = 0; i < y_c.rows; i++)
    y_c.row(i) = sqrt_alpha.at<float>(0, i) * y_c.row(i);

  cv::Mat B;
  x_c.copyTo(B);
  for (int i = 0; i < x_c.rows; i++)
    x_c.row(i) = sqrt_alpha.at<float>(0, i) * x_c.row(i);

  // 7 - SVD of At*B to compute M as M = U*V
  // cv::SVD turns a Matrix H into  u*w*vt
  cv::SVD udv(A.t() * B);
  cv::Mat M = udv.u * udv.vt;

  // 8 - q = f(p) = (p - y~) * M + x~
  cv::Mat q = (p - y_t) * M + x_t;

  return q;
}