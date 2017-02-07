#pragma once

/**
 * https://www.siam.org/students/siuro/vol4/S01084.pdf
**/

#include "invproj.h"

#include <fstream>

#include <Windows.h>

#define MAX_UCHAR_IMAGE_VALUE 255.0

double InverseProjection::RadialBasisKernel(double* X1, double* X2)
{
  double err = 1.0;
  double sed = sqrt(pow(X2[0] - X1[0], 2) + pow(X2[1] - X1[1], 2));
  double c = 0.0;

  double kbf = 
    //C^0 Matern
    exp(-err*sed)
    
    //RBF
    //exp(-pow(err*sed, 2.0))

	//Multiquadratic
    //sqrt(c + pow(err * sed, 2.0));
    ;

  return kbf;
}

InverseProjection::InverseProjection ()
{
  tf_1D.AddRGBControlPoint(vr::TransferControlPoint(1, 0, 0, 0));
  tf_1D.AddRGBControlPoint(vr::TransferControlPoint(0, 1, 0, 128));
  tf_1D.AddRGBControlPoint(vr::TransferControlPoint(0, 0, 1, 256));

  tf_1D.Build();

  input_colorspace = 0;
  rad_kernel_gama = 2.0;
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
// TODO: receber a matriz de distâncias correta em relação a cada pixel.
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
  arrayResps.clear();
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

      //double sum_dist = 0;
      //for (int c = 0; c < n_points_per_set; c++)
      //{
      //  sum_dist += A.at<double>(r, c);
      //}
      //
      //double sum = 0;
      //for (int c = 0; c < n_points_per_set; c++)
      //{
      //  A.at<double>(r, c) = A.at<double>(r, c) / sum_dist;
      //  sum += A.at<double>(r, c);
      //}
    }

    cv::Mat P = LUDecomp(A);

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

void InverseProjection::CalcInverseProjectionValBased (int n_ref_points
  , double** ref_points
  , std::vector<std::string> image_paths
  , double* input_point
  )
{
  //printf("%d points:\n", n_ref_points);
  //for (int i = 0; i < n_ref_points; i++)
  //  printf(". %.2lf %.2lf - %s\n", ref_points[i][0], ref_points[i][1], image_paths[i].c_str());
  //printf("Input Point: %.2lf %.2lf\n", input_point[0], input_point[1]);

  std::vector<cv::Mat> srcs;
  for (int i = 0; i < image_paths.size(); i++)
    srcs.push_back(cv::imread(image_paths[i], 1));
  
  std::vector<cv::Mat> hsvs;
  for (int i = 0; i < srcs.size(); i++)
    hsvs.push_back(ConvertBGRToInputColorSpace(srcs[i], input_colorspace));
  
  cv::Mat fimage = hsvs[0];

  //for (int i = 0; i < hsvs.size(); i++)
  //{
  //  for (int pcol = 0; pcol < hsvs[i].cols; pcol++)
  //  {
  //    for (int prow = 0; prow < hsvs[i].rows; prow++)
  //    {
  //      std::cout << hsvs[i].at<cv::Vec3b>(prow, pcol) << std::endl;
  //      break;
  //    }
  //    break;
  //  }
  //}

  cv::Mat Res = cv::Mat::zeros(fimage.rows, fimage.cols, cv::DataType<cv::Vec3b>::type);

  // Matriz de dissimilaridade
  cv::Mat A = cv::Mat::zeros(n_ref_points, n_ref_points, cv::DataType<double>::type);
  for (int r = 0; r < n_ref_points; r++)
  {
    A.at<double>(r, r) = RadialBasisKernel(ref_points[r], ref_points[r]);
    for (int c = r + 1; c < n_ref_points; c++)
    {
      double dist = RadialBasisKernel(ref_points[r], ref_points[c]);
  
      A.at<double>(r, c) = dist;
      A.at<double>(c, r) = dist;
    }
  }
  
  cv::Mat P = LUDecomp(A);
  
  // Vetor de dissimilaridade entre o ponto de entrada e os pontos de referência
  cv::Mat Ar = cv::Mat::zeros(1, n_ref_points, cv::DataType<double>::type);
  for (int r = 0; r < n_ref_points; r++)
    Ar.at<double>(0, r) = RadialBasisKernel(input_point, ref_points[r]);
 
  for (int pcol = 0; pcol < fimage.cols; pcol++)
  {
    for (int prow = 0; prow < fimage.rows; prow++)
    {
      cv::Mat b = cv::Mat::zeros(n_ref_points, 1, cv::DataType<double>::type);
      for (int i_imgs = 0; i_imgs < hsvs.size(); i_imgs++)
        b.at<double>(i_imgs, 0) = ((double)hsvs[i_imgs].at<cv::Vec3b>(prow, pcol).val[0] / 255.0);
      
      cv::Mat X = LUSolve(A, P, b);
      cv::Mat_<double> value_r = Ar * X;
      
      Res.at<cv::Vec3b>(prow, pcol).val[0] = (uchar)(value_r.at<double>(0, 0) * 255.0);
    }
  }

  for (int pcol = 0; pcol < Res.cols; pcol++)
  {
    for (int prow = 0; prow < Res.rows; prow++)
    {
      Res.at<cv::Vec3b>(prow, pcol).val[1] = 205;
      Res.at<cv::Vec3b>(prow, pcol).val[2] = 255;
    }
  }

  cv::Mat Res_w = ConvertInputColorSpaceToBGR(Res, input_colorspace);
  cv::imwrite("result_ip_val.png", Res_w);
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


void InverseProjection::ClearInverseArray(){
  arrayResps.clear();
}

void InverseProjection::CalcInverseProjectionPropBased (
  int n_ref_points
  , double** ref_points
  , std::vector<std::string> prop_paths
  , double* input_point
  , int layer_i_size
  , int layer_j_size
  , double* limits_pro_val
  )
{

  printf("%d points:\n", n_ref_points);
  for (int i = 0; i < n_ref_points; i++)
    printf(". %d %.5lf %.5lf - %s\n", i, ref_points[i][0], ref_points[i][1], prop_paths[i].c_str());
  printf("Input Point: %.5lf %.5lf\n", input_point[0], input_point[1]);
  printf("MinMax = %.5lf %.5lf\n", limits_pro_val[0], limits_pro_val[1]);

  limits_pro_val[1] = limits_pro_val[1] + (limits_pro_val[1] - limits_pro_val[0]) * 0.05;
  limits_pro_val[0] = limits_pro_val[0] - (limits_pro_val[1] - limits_pro_val[0]) * 0.05;
  
  printf("Recalculated MinMax = %.5lf %.5lf\n", limits_pro_val[0], limits_pro_val[1]);

  std::vector<cv::Mat> f_maps;

  double max_val = 0;

  {
    for (int t = 0; t < prop_paths.size(); t++)
    {
      cv::Mat map = cv::Mat::zeros(layer_j_size, layer_i_size, cv::DataType<double>::type);
      
      std::ifstream propfile;
      propfile.open(prop_paths[t]);
      
      double val;
      for (int l = 0; l < layer_j_size; l++)
      {
        for (int c = 0; c < layer_i_size && propfile >> val; c++)
        {
          map.at<double>(l, c) = val;
        }
      }

      f_maps.push_back(map);

      propfile.close();

      GenerateImage(layer_j_size, layer_i_size, 15, map, std::to_string(t + 1) + "_file.png", limits_pro_val);
    }
  }

  cv::Mat Res = cv::Mat::zeros(layer_j_size, layer_i_size, cv::DataType<double>::type);

  // Matriz de dissimilaridade

  cv::Mat A = cv::Mat::zeros(n_ref_points, n_ref_points, cv::DataType<double>::type);
  for (int r = 0; r < n_ref_points; r++)
  {
    A.at<double>(r, r) = 1.0;
    for (int c = r + 1; c < n_ref_points; c++)
    {
      double dist = RadialBasisKernel(ref_points[r], ref_points[c]);
      A.at<double>(r, c) = dist;
      A.at<double>(c, r) = dist;
    }
  }
  cv::Mat CA;
  A.copyTo(CA);

  cv::Mat P = PLUDecomp(A);
  
  // Vetor de dissimilaridade entre o ponto de entrada e os pontos de referência
  cv::Mat Ar = cv::Mat::zeros(1, n_ref_points, cv::DataType<double>::type);
  for (int r = 0; r < n_ref_points; r++)
    Ar.at<double>(0, r) = RadialBasisKernel(input_point, ref_points[r]);

  for (int pcol = 0; pcol < layer_i_size; pcol++)
  {
    for (int prow = 0; prow < layer_j_size; prow++)
    {
      double v0 = f_maps[0].at<double>(prow, pcol);
      if (v0 < 0)
        Res.at<double>(prow, pcol) = -1;
      else
      {
        cv::Mat b = cv::Mat::zeros(n_ref_points, 1, cv::DataType<double>::type);
        for (int i_inp = 0; i_inp < f_maps.size(); i_inp++)
          b.at<double>(i_inp, 0) = f_maps[i_inp].at<double>(prow, pcol);

        cv::Mat_<double> X = LUSolve(A, P, b);

        cv::Mat_<double> value_r = Ar *  X;

        Res.at<double>(prow, pcol) = value_r.at<double>(0, 0);
      } 
    }
  }


  arrayResps.push_back(Res);
  ws = layer_j_size;
  hs = layer_i_size;
  //printf("Max Val: %lf\n", max_val);
  GenerateImage(layer_j_size, layer_i_size, 15, Res, "0_result_image.png", limits_pro_val);
}


void InverseProjection::GenerateImage (int j_size, int i_size, int s, cv::Mat map, std::string name, double* limits_pro_val)
{
  cv::Mat ret = cv::Mat::zeros(j_size * s, i_size * s, cv::DataType<cv::Vec3b>::type);
  
  for (int l = 0; l < j_size; l++)
  {
    for (int c = 0; c < i_size; c++)
    {
      double val = map.at<double>(l, c);

      for (int si = 0; si < s; si++)
      {
        for (int sj = 0; sj < s; sj++)
        {
          int local_l = l * s + sj;
          int local_c = c * s + si;
          glm::vec4 colr;
          if (val < 0) colr = glm::vec4(0, 0, 0,0);
          else colr = tf_1D.Get(((val - limits_pro_val[0]) / (limits_pro_val[1] - limits_pro_val[0])) * 255.0);

          ret.at<cv::Vec3b>(local_l, local_c).val[0] = (uchar)(colr.x * 255);
          ret.at<cv::Vec3b>(local_l, local_c).val[1] = (uchar)(colr.y * 255);
          ret.at<cv::Vec3b>(local_l, local_c).val[2] = (uchar)(colr.z * 255);
        }
      }
    }
  }

  cv::imwrite(name, ret);
}


double InverseProjection::dist(std::vector<double> x1, std::vector<double> x2){
  double dist = 0;
  for (int i = 0; i < x1.size(); i++){
    dist += pow(x1[i] - x2[i], 2);
  }
  return sqrt(dist);
}

/* https://pt.wikipedia.org/wiki/Inverso_da_pot%C3%AAncia_das_dist%C3%A2ncias*/
double InverseProjection::Shepard(std::vector<std::vector<double>> u, std::vector<double> x, double value,double p){
  
  std::vector<double> dist_matrix;
  double result = 0;
  double sum = 0;
  for (int i = 0; i < u.size(); i++){
    dist_matrix.push_back(dist(x, u[i]));
    sum += (1 / pow(dist_matrix[i], p));
    if (dist_matrix[i] == 0) return value;
  }

  for (int i = 0; i < dist_matrix.size(); i++){
    result += ((1 / pow(dist_matrix[i], p))*value)/sum;
  }
  
  return result;
}

void InverseProjection::CalcNewPropGridByInverse(void){

  cv::Size s = arrayResps[0].size();

  cv::Mat result = cv::Mat::zeros(ws, hs, cv::DataType<double>::type);
  
  for (int j = 0; j < hs; j++){
    for (int i = 0; i < ws; i++){
      if (arrayResps[0].at<double>(i, j) < 0 || arrayResps[1].at<double>(i, j) < 0 || arrayResps[2].at<double>(i, j) < 0 || arrayResps[3].at<double>(i, j) < 0 )
        result.at<double>(i, j) = -1;
      else
        result.at<double>(i, j) = arrayResps[0].at<double>(i, j) * arrayResps[1].at<double>(i, j) * arrayResps[2].at<double>(i, j) * arrayResps[3].at<double>(i, j);
    }
  }

  double min, max;
  double* vec = (double*)malloc(2 * sizeof(double));
  
  cv::minMaxLoc(result, &min, &max);
  vec[0] = min;
  vec[1] = max;


  vec[1] = vec[1] + (vec[1] - vec[0]) * 0.05;
  vec[0] = (vec[0]-0.5f)-(vec[1] - vec[0]) * 0.05;



  printf("max min da composta %g %g\n max min %g %g", vec[0], vec[1], max,min);
  GenerateImage(ws,hs, 15, result, "novaprop.png", vec);
}