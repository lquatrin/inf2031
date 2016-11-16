#pragma once

#include "header.h"

#include <vector>

#include <opencv2/core/core_c.h>

computingClass::computingClass (int* pInt, int arrSize)
{
  for (int i = 0; i < arrSize; i++)
  {
    vec.push_back(pInt[i]);
  }
}

double computingClass::SumArray ()
{
  int sum = 0;
  for (int i = 0; i < vec.size(); i++)
  {
    sum += vec[i];
  }
  return (double)sum;
}

static bool s_CheckInputErrorsLAMP(const cv::Mat& X, const std::vector<int> cp_index, const cv::Mat& Ys)
{
  if (X.rows < 3) {
    fprintf(stderr, "ERROR: s_CheckInputErrorsLAMP - Input matrix too small to execute the projection [%d, %d]\n", X.rows, X.cols);
    return false;
  }

  if (cp_index.size() <= 1) {
    fprintf(stderr, "ERROR: s_CheckInputErrorsLAMP - To few control points. Must have at least 2.\n");
    return false;
  }

  if (Ys.rows != cp_index.size()) {
    fprintf(stderr, "ERROR: s_CheckInputErrorsLAMP - Number of control points and number of control points' projections is different. %d control points given and %d samples provided.\n", cp_index.size(), Ys.rows);
    return false;
  }

  if (X.cols < Ys.cols) {
    fprintf(stderr, "ERROR: s_CheckInputErrorsLAMP - Projections have more dimensions than original data. Original data has %d dimensions and projection data has %d dimensions.\n", X.cols, Ys.cols);
    return false;
  }

  return true;
}

cv::Mat computingClass::lamp(const cv::Mat& X, const std::vector<int> cp_index, const cv::Mat& Ys)
{
  if (!s_CheckInputErrorsLAMP(X, cp_index, Ys)) {
    fprintf(stderr, "ERROR: lamp - Invalid input.\n");
    return cv::Mat::zeros(1, 1, CV_8UC1);
  }

  double tol = 1E-003;

  // Building an array with the indices of the points to be projected.
  std::vector<int> proj_idx(X.rows);
  for (int i = 0; i < X.rows; ++i)
    proj_idx[i] = i;
  for (int i = 0; i < cp_index.size(); ++i)
    proj_idx[cp_index[i]] = -1;

  // Building the control points and projected points matrices.
  cv::Mat Xs = cv::Mat::zeros(cp_index.size(), X.cols, X.depth());
  cv::Mat Y = cv::Mat::zeros(X.rows, Ys.cols, Ys.depth());
  for (int i = 0; i < Xs.rows; ++i) {
    X.row(cp_index[i]).copyTo(Xs.row(i));
    Ys.row(i).copyTo(Y.row(cp_index[i]));
  }

  cv::Mat alpha = cv::Mat::zeros(1, cp_index.size(), CV_32FC1);
  for (int i = 0; i < X.rows; ++i) {
    if (proj_idx[i] == -1)
      continue;

    // Building the weights of each control point over the current point.
    for (int j = 0; j < cp_index.size(); ++j)
      alpha.at<float>(0, j) = 1 / cv::max(cv::norm(Xs.row(j), X.row(proj_idx[i])), tol);

    float sum_alpha = cv::sum(alpha)[0];

    cv::Mat T = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
    for (int k = 0; k < Xs.cols; ++k)
      T.col(k) = Xs.col(k).mul(alpha.t());

    // Building the x-tilde and y-tilde variables (Eq. 3).
    cv::Mat Xtil;
    cv::reduce(T, Xtil, 0, CV_REDUCE_SUM);
    Xtil = Xtil * (1 / sum_alpha);

    T = cv::Mat::zeros(Ys.rows, Ys.cols, Ys.depth());
    for (int k = 0; k < Ys.cols; ++k)
      T.col(k) = Ys.col(k).mul(alpha.t());

    cv::Mat Ytil;
    cv::reduce(T, Ytil, 0, CV_REDUCE_SUM);
    Ytil = Ytil * (1 / sum_alpha);

    // Building the x-hat and y-hat variables (Eq. 4).
    cv::Mat Xhat = cv::Mat::zeros(Xs.rows, Xs.cols, Xs.depth());
    for (int k = 0; k < Xs.rows; ++k)
      Xhat.row(k) = Xs.row(k) - Xtil;

    cv::Mat Yhat = cv::Mat::zeros(Ys.rows, Ys.cols, Ys.depth());
    for (int k = 0; k < Ys.rows; ++k)
      Yhat.row(k) = Ys.row(k) - Ytil;

    // Building the A and B matrices (Eq. 6) and calculating the SVD of t(A) * B.
    cv::Mat sqrt_alpha;
    cv::sqrt(alpha, sqrt_alpha);
    sqrt_alpha = sqrt_alpha.t();

    cv::Mat A;
    Xhat.copyTo(A);
    for (int k = 0; k < A.cols; ++k)
      A.col(k) = A.col(k).mul(sqrt_alpha);

    cv::Mat B;
    Yhat.copyTo(B);
    for (int k = 0; k < B.cols; k++)
      B.col(k) = B.col(k).mul(sqrt_alpha);

    cv::SVD udv(A.t() * B);

    // Calculating the affine transform matrix (Eq. 7).
    cv::Mat M = udv.u * udv.vt;

    // Projecting X[i] using the matrix M (Eq 8)
    Y.row(proj_idx[i]) = (X.row(proj_idx[i]) - Xtil) * M + Ytil;
  }

  return Y;
}

void computingClass::lampTest ()
{
  float d[10][3] = {
    { 1, 2, 3 },
    { 3, 2, 1 },
    { 4, 5, 6 },
    { 2, 3, 4 },
    { 4, 3, 2 },
    { 6, 8, 9 },
    { 2, 4, 6 },
    { 1, 9, 5 },
    { 1, 3, 9 },
    { 9, 8, 7 },
  };

  std::vector<int> idx = { 1, 5, 9 };

  float ys[3][2] = {
    { 4, 9 },
    { 1, 1 },
    { 9, 6 },
  };

  cv::Mat X = cv::Mat(10, 3, CV_32FC1, d);
  cv::Mat Ys = cv::Mat(3, 2, CV_32FC1, ys);
  
  cv::Mat P = lamp(X, idx, Ys);

  printf("Result of LAMP:\n - Matrix P: [%d, %d]\n", P.rows, P.cols);

  for (int k = 0; k < P.rows; ++k)
  {
    for (int c = 0; c < P.cols; ++c)
    {
      printf("%.2f ", P.at<float>(k, c));
    }
    printf("\n");
  }
}
