#pragma once

#include "invproj.h"

#define MAX_UCHAR_IMAGE_VALUE 255.0

double InverseProjection::RadialBasisKernel(double* X1, double* X2)
{
  return exp((-(pow(X2[0] - X1[0], 2) + pow(X2[1] - X1[1], 2))) / (2.0*rad_kernel_gama));
}

InverseProjection::InverseProjection ()
{
  input_colorspace = 0;
  rad_kernel_gama = 0.5;
}

InverseProjection::~InverseProjection ()
{
  Clear();
}

void InverseProjection::ReadImages (std::vector<std::string> paths, int channel)
{

  for (int i = 0; i < paths.size(); i++)
    srcs.push_back(cv::imread(paths[i], 1));

  for (int i = 0; i < srcs.size(); i++){
    // Separa a imagem em 3 componentes H S e V
    std::vector<cv::Mat> s_hsv;
    cv::Mat t_hsv;
    cv::cvtColor(srcs[i], t_hsv, cv::COLOR_BGR2HSV);
    cv::split(t_hsv, s_hsv);

    hsvs.push_back(s_hsv[channel]);
  }

}

// A * x = b
// A: matriz 'mdists'
// x: coeficientes
// b: resultados
// TODO: receber a matriz de dist�ncias correta em rela��o a cada pixel.
void InverseProjection::CalcInverseProjection (void)
{
  if (srcs.size() == 0) return;

  int n = srcs.size();
  int s_w, s_h;
  s_w = srcs[0].rows;
  s_h = srcs[1].cols;


  int chnls = 0;
  for (int chnls = 0; chnls < srcs[0].channels(); chnls++)
  {
    for (int pcol = 0; pcol < s_w; pcol++)
    {
      for (int prow = 0; prow < s_h; prow++)
      {
        //Coeficientes
        //TODO: GERAR A MATRIZ CORRETA PARA CADA PIXEL / CHANNEL
        cv::Mat A = cv::Mat::zeros(n, n, cv::DataType<double>::type);
        A.at<double>(1, 0) = 1.0;
        A.at<double>(2, 0) = 1.0;
        A.at<double>(0, 1) = 1.0;
        A.at<double>(0, 2) = 1.0;
        
        cv::Mat C = cv::Mat::zeros(n, 1, cv::DataType<double>::type);

        for (int i_imgs = 0; i_imgs < n; i_imgs++)
          C.at<double>(i_imgs, 0) = ((double)srcs[i_imgs].at<cv::Vec3b>(prow, pcol).val[chnls]) / MAX_UCHAR_IMAGE_VALUE;
        
        cv::Cholesky(A.ptr<double>(), A.step, A.rows, C.ptr<double>(), C.step, C.cols);
      }
    }
  }
}

void InverseProjection::test ()
{
  std::vector<std::string> paths;
  paths.push_back("images\\blue.png");
  paths.push_back("images\\green.png");
  paths.push_back("images\\red.png");

  ReadImages(paths,0);
  
  for (int i = 0; i < srcs.size(); i++)
  {
    cv::Vec3b intensity = srcs[i].at<cv::Vec3b>(0, 0);
    uchar blue = intensity.val[0];
    uchar green = intensity.val[1];
    uchar red = intensity.val[2];
    
    printf("%d [%s]:\n", i, paths[i].c_str());
    printf(" - %.03d %.03d %.03d\n", blue, green, red);
  }
  printf("\n");
  
  CalcInverseProjection();

  //std::vector<std::vector<double>> m_vec;
  //getDistMatrix(m_vec);

}

void InverseProjection::testCholesky(void)
{
  //Cholesky test with only the A matrix
  {
    cv::Mat m1 = (cv::Mat_<double>(3, 3) << 4,  12, -16,
                                           12,  37, -43,
                                          -16, -43,  98);

    std::cout << "Matrix A:\n" << m1 << std::endl << std::endl;

    // Call Cholesky function
    cv::Cholesky((double*)m1.ptr(), m1.step, m1.rows, NULL, 0, 0);
    // Correct diagonal part of the matrix
    for (int i = 0; i < m1.rows; i++)
      m1.at<double>(i, i) = 1 / m1.at<double>(i, i);
    // Remove upper triangle region
    m1.at<double>(0, 1) = 0; m1.at<double>(0, 2) = 0; m1.at<double>(1, 2) = 0;
    

    std::cout << "---------------" << std::endl;

    std::cout << "Matrix L:\n" << m1 << std::endl << std::endl;
    std::cout << "Matrix L':\n" << m1.t() << std::endl << std::endl;
    std::cout << "Matrix LL':\n" << m1*m1.t() << std::endl << std::endl;
  }

  {
    cv::Mat m1 = (cv::Mat_<double>(4, 4) <<
       5, 1.2, 0.3, -0.6,
       1.2, 6, -0.4, 0.9,
       0.3, -0.4, 8, 1.7,
       -0.6, 0.9, 1.7, 10);

    std::cout << "Matrix A:\n" << m1 << std::endl << std::endl;

    // Call Cholesky function
    cv::Cholesky((double*)m1.ptr(), m1.step, m1.rows, NULL, 0, 0);
    // Correct diagonal part of the matrix
    for (int i = 0; i < m1.rows; i++)
      m1.at<double>(i, i) = 1 / m1.at<double>(i, i);
    // Remove upper triangle region
    for (int i = 0; i < m1.rows; i++)
      for (int j = i + 1; j < m1.cols; j++)
        m1.at<double>(i, j) = 0.0;

    std::cout << "---------------" << std::endl;

    std::cout << "Matrix L:\n" << m1 << std::endl << std::endl;
    std::cout << "Matrix L':\n" << m1.t() << std::endl << std::endl;
    std::cout << "Matrix LL':\n" << m1*m1.t() << std::endl << std::endl;
  }

  {
    cv::Mat m1 = (cv::Mat_<double>(4, 4) <<
      9.0000, 0.6000, -0.3000, 1.5000,
      0.6000, 16.0400, 1.1800, -1.5000,
      -0.3000, 1.1800, 4.1000, -0.5700,
      1.5000, -1.5000, -0.5700, 25.4500);

    std::cout << "Matrix A:\n" << m1 << std::endl << std::endl;

    cv::Mat B = (cv::Mat_<double>(4, 1) <<
      2.49,
      0.566,
      0.787,
      -2.209);

    std::cout << "Matrix B:\n" << B << std::endl << std::endl;

    // Call Cholesky function
    cv::Cholesky((double*)m1.ptr(), m1.step, m1.rows, (double*)B.ptr(), B.step, B.cols);
    // Correct diagonal part of the matrix
    for (int i = 0; i < m1.rows; i++)
      m1.at<double>(i, i) = 1 / m1.at<double>(i, i);
    // Remove upper triangle region
    for (int i = 0; i < m1.rows; i++)
      for (int j = i + 1; j < m1.cols; j++)
        m1.at<double>(i, j) = 0.0;

    std::cout << "---------------" << std::endl;

    std::cout << "Matrix L:\n" << m1 << std::endl << std::endl;
    std::cout << "Matrix L':\n" << m1.t() << std::endl << std::endl;
    std::cout << "Matrix LL':\n" << m1*m1.t() << std::endl << std::endl;

    std::cout << "Matrix X:\n" << B << std::endl << std::endl;
  }
}

void InverseProjection::testLU ()
{  
  int n = 3;
  {
    cv::Mat A = (cv::Mat_<double>(3, 3) <<
      2, -2,   4,
      -5, -4,  -4,
      3, -4, -4);
  
    cv::Mat M = A;
    cv::Mat P = PLUDecomp(A);

    cv::Mat L = cv::Mat::zeros(n, n, cv::DataType<double>::type);
    cv::Mat U = cv::Mat::zeros(n, n, cv::DataType<double>::type);
    for (int i = 0; i < n; i++)
      for (int j = i; j < n; j++)
        U.at<double>(i, j) = A.at<double>(i, j);

    for (int i = 0; i < n; i++)
    {
      L.at<double>(i, i) = 1.0;
      for (int j = i + 1; j < n; j++)
      {
        L.at<double>(j, i) = A.at<double>(j, i);
      }
    }

    std::cout << "Matrix LU:\n" << A << std::endl << std::endl;

    std::cout << "Matrix P:\n" << P << std::endl << std::endl;

    std::cout << "Matrix PLU:\n" << (P.t()*(L*U)) << std::endl << std::endl;
  }
  
  {
    cv::Mat A = (cv::Mat_<double>(3, 3) <<
      1, 2,  4,
      3, 8, 14,
      2, 6, 13);
    cv::Mat b = (cv::Mat_<double>(3, 1) << 3, 13, 4);

    cv::Mat P = PLUDecomp(A);
    cv::Mat X = LUSolve(A, P, b);
    std::cout << "Solution:\n" << LUEvalB(A, P, X) << std::endl << std::endl;
  }
}

void InverseProjection::Clear ()
{
  srcs.clear();
  hsvs.clear();
}

void InverseProjection::CalcInverseProjection01(
  int n_sets,
  int n_points_per_set,
  int dimension,
  double** points,
  double** input,
  std::vector<std::string> image_paths)
{
  printf(" - Init CalcInverseProjection with LU decomp\n");

  std::vector<cv::Mat> srcs;
  std::vector<cv::Mat> hsvs;

  for (int i = 0; i < image_paths.size(); i++)
    srcs.push_back(cv::imread(image_paths[i], 1));

  for (int i = 0; i < srcs.size(); i++)
  {
    hsvs.push_back(ConvertBGRToInputColorSpace(srcs[i], input_colorspace));
  }

  cv::Mat fimage = hsvs[0];

  cv::Mat Res = cv::Mat::zeros(fimage.rows, fimage.cols, cv::DataType<cv::Vec3b>::type);

  for (int chnls = 0; chnls < n_sets; chnls++)
  {
    //printf("Channel %d\n", chnls);
    //for (int i = 0 ; i < n_points_per_set; i++)
    //{
    //  printf("points: [%.4lf, %.4lf]\n", points[i + chnls*n_points_per_set][0], points[i + chnls*n_points_per_set][1]);
    //}
    //printf("\n");
    cv::Mat A = cv::Mat::zeros(n_points_per_set, n_points_per_set, cv::DataType<double>::type);
    for (int r = 0; r < n_points_per_set; r++)
    {
      A.at<double>(r, r) = RadialBasisKernel(points[r + chnls*n_points_per_set], points[r + chnls*n_points_per_set]);;
      for (int c = r + 1; c < n_points_per_set; c++)
      {
        double dist = RadialBasisKernel(points[r + chnls*n_points_per_set], points[c + chnls*n_points_per_set]);

        A.at<double>(r, c) = dist;
        A.at<double>(c, r) = dist;
      }
    }

    //std::cout << "Matrix  A:\n" << A << std::endl << std::endl;
    cv::Mat P = LUDecomp(A);
    //std::cout << "Matrix LU:\n" << A << std::endl << std::endl;

    cv::Mat Ar = cv::Mat::zeros(1, n_points_per_set, cv::DataType<double>::type);
    for (int r = 0; r < n_points_per_set; r++)
      Ar.at<double>(0, r) = RadialBasisKernel(input[chnls], points[r + chnls*n_points_per_set]);

    for (int pcol = 0; pcol < fimage.cols; pcol++)
    {
      for (int prow = 0; prow < fimage.rows; prow++)
      {
        cv::Mat b = cv::Mat::zeros(n_points_per_set, 1, cv::DataType<double>::type);
        for (int i_imgs = 0; i_imgs < hsvs.size(); i_imgs++)
          b.at<double>(i_imgs, 0) = ((double)hsvs[i_imgs].at<cv::Vec3b>(prow, pcol).val[chnls]);

        cv::Mat X = LUSolve(A, P, b);
        cv::Mat_<double> value_r = Ar * X;
        
        Res.at<cv::Vec3b>(prow, pcol).val[chnls] = (uchar)(value_r.at<double>(0, 0));
      }
    }
  }

  cv::Mat Res_w = ConvertInputColorSpaceToBGR(Res, input_colorspace);
  cv::imwrite("result.jpg", Res_w);

  printf(" - End CalcInverseProjection with LU decomp\n");
}

cv::Mat InverseProjection::ConvertBGRToInputColorSpace(cv::Mat ipt, int type)
{
  cv::Mat ret;
  if (type == 0)
    cv::cvtColor(ipt, ret, cv::COLOR_BGR2HSV);
  else if (type == 1)
    ret = ipt;
  return ret;
}

cv::Mat InverseProjection::ConvertInputColorSpaceToBGR(cv::Mat ipt, int type)
{
  cv::Mat ret;
  if (type == 0)
    cv::cvtColor(ipt, ret, cv::COLOR_HSV2BGR);
  else if (type == 1)
    ret = ipt;
  return ret;
}

cv::Mat InverseProjection::LUDecomp (cv::Mat& A)
{
  int n = A.rows;
  cv::Mat P = cv::Mat::zeros(n, n, cv::DataType<double>::type);
  for (int i = 0; i < n; i++)
    P.at<double>(i, i) = 1;

  for (int curr_row = 0; curr_row < n - 1; curr_row++)
  {
    for (int i = curr_row + 1; i < n; i++)
    {
      double factor = A.at<double>(i, curr_row) / A.at<double>(curr_row, curr_row);
      for (int k = curr_row; k < n; k++)
        A.at<double>(i, k) -= A.at<double>(curr_row, k) * factor;
      A.at<double>(i, curr_row) = factor;
    }
  }
  return P;
}

//Performs LU Decomposition
cv::Mat InverseProjection::PLUDecomp(cv::Mat& A)
{
  int n = A.rows;
  cv::Mat P = cv::Mat::zeros(n, n, cv::DataType<double>::type);
  for (int i = 0; i < n; i++)
    P.at<double>(i, i) = 1;

  for (int curr_row = 0; curr_row < n - 1; curr_row++)
  {
    int pivot = curr_row;
    for (int k = curr_row + 1; k < n; k++)
    {
      if (fabs(A.at<double>(k, curr_row)) > fabs(A.at<double>(pivot, curr_row)))
        pivot = k;
    }

    if (pivot != curr_row)
    {
      for (int k = 0; k < n; k++)
      {
        double aux = A.at<double>(curr_row, k);
        A.at<double>(curr_row, k) = A.at<double>(pivot, k);
        A.at<double>(pivot, k) = aux;

        double paux = P.at<double>(curr_row, k);
        P.at<double>(curr_row, k) = P.at<double>(pivot, k);
        P.at<double>(pivot, k) = paux;
      }
    }

    for (int i = curr_row + 1; i < n; i++)
    {
      double factor = A.at<double>(i, curr_row) / A.at<double>(curr_row, curr_row);
      for (int k = curr_row; k < n; k++)
        A.at<double>(i, k) -= A.at<double>(curr_row, k) * factor;
      A.at<double>(i, curr_row) = factor;
    }
  }
  return P;
}

// Compute:
// . L * U * x = P * b
cv::Mat InverseProjection::LUSolve (cv::Mat LU, cv::Mat P, cv::Mat b)
{
  int n = LU.rows;

  // B = P * b
  cv::Mat B = P * b;

  // Forward Substitution
  // L * y = B, with y = U * x
  for(int i = 0; i < n; i++)
  {
    double sum = 0;
    for(int j = 0; j < i; j++)
      sum += LU.at<double>(i, j) * B.at<double>(j, 0);
    B.at<double>(i, 0) = (B.at<double>(i,0) - sum);
  }

  cv::Mat X = cv::Mat::zeros(n, 1, cv::DataType<double>::type);

  // Backward Substitution
  // U * x = y
  for(int i = n-1; i >= 0; i--)
  {
    double sum = 0;
    for(int j = i + 1; j < n; j++)
    {
      sum += LU.at<double>(i, j) * X.at<double>(j, 0);
    }
    X.at<double>(i, 0) = (B.at<double>(i, 0) - sum) / LU.at<double>(i, i);
  }

  return X;
}

// P^t * L * U * X = B
// return B
cv::Mat InverseProjection::LUEvalB (cv::Mat LU, cv::Mat P, cv::Mat X)
{
  int n = LU.rows;
  
  cv::Mat L = cv::Mat::zeros(n, n, cv::DataType<double>::type);
  cv::Mat U = cv::Mat::zeros(n, n, cv::DataType<double>::type);
  
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      U.at<double>(i, j) = LU.at<double>(i, j);

  for (int i = 0; i < n; i++)
  {
    L.at<double>(i, i) = 1.0;
    for (int j = i + 1; j < n; j++)
      L.at<double>(j, i) = LU.at<double>(j, i);
  }

  cv::Mat b = (P.t() * (L * U)) * X;

  return b;
}

void InverseProjection::CalcInverseProjection02(
  int n_sets,
  int n_points_per_set,
  int dimension,
  double** points,
  double** input,
  std::vector<std::string> image_paths)
{
  printf(" - Init CalcInverseProjection01\n");

  std::vector<cv::Mat> srcs;
  std::vector<cv::Mat> hsvs;

  for (int i = 0; i < image_paths.size(); i++)
    srcs.push_back(cv::imread(image_paths[i], 1));

  for (int i = 0; i < srcs.size(); i++)
  {
    hsvs.push_back(ConvertBGRToInputColorSpace(srcs[i], input_colorspace));
  }

  cv::Mat fimage = hsvs[0];

  cv::Mat Res = cv::Mat::zeros(fimage.rows, fimage.cols, cv::DataType<cv::Vec3b>::type);

  for (int chnls = 0; chnls < n_sets; chnls++)
  {
    cv::Mat A = cv::Mat::zeros(n_points_per_set, n_points_per_set, cv::DataType<double>::type);
    for (int r = 0; r < n_points_per_set; r++)
    {
      A.at<double>(r, r) = RadialBasisKernel(points[r + chnls*n_points_per_set], points[r + chnls*n_points_per_set]);;
      for (int c = r + 1; c < n_points_per_set; c++)
      {
        double dist = RadialBasisKernel(points[r + chnls*n_points_per_set], points[c + chnls*n_points_per_set]);

        A.at<double>(r, c) = dist;
        A.at<double>(c, r) = dist;
      }
    }

    cv::Mat M;
    A.copyTo(M);

    cv::Mat Ar = cv::Mat::zeros(1, n_points_per_set, cv::DataType<double>::type);
    for (int r = 0; r < n_points_per_set; r++)
      Ar.at<double>(0, r) = RadialBasisKernel(input[chnls], points[r + chnls*n_points_per_set]);

    for (int pcol = 0; pcol < fimage.cols; pcol++)
    {
      for (int prow = 0; prow < fimage.rows; prow++)
      {
        cv::Mat C = cv::Mat::zeros(n_points_per_set, 1, cv::DataType<double>::type);
        for (int i_imgs = 0; i_imgs < hsvs.size(); i_imgs++)
          C.at<double>(i_imgs, 0) = ((double)hsvs[i_imgs].at<cv::Vec3b>(prow, pcol).val[chnls]);


        cv::Cholesky(M.ptr<double>(), M.step, M.rows, C.ptr<double>(), C.step, C.cols);

        cv::Mat_<double> value_r = Ar * C;

        Res.at<cv::Vec3b>(prow, pcol).val[chnls] = (uchar)(value_r.at<double>(0, 0));
      }
    }
  }

  cv::Mat Res_w = ConvertInputColorSpaceToBGR(Res, input_colorspace);
  cv::imwrite("result.jpg", Res_w);

  printf(" - End CalcInverseProjection01\n");
}

void InverseProjection::GenInverseProjection (
  int n_sets,
  int n_points_per_set,
  int dimension,
  double** set_points,
  double** input_points,
  std::vector<std::string> image_paths)
{

}
