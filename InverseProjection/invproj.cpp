#pragma once

#include "invproj.h"

#define MAX_UCHAR_IMAGE_VALUE 255.0

InverseProjection::InverseProjection ()
{
  input_colorspace = 0;
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

#ifdef _DEBUG
  for (int i = 0; i < m_vec.size(); i++){
    for (int j = 0; j < m_vec[i].size(); j++){
      printf("%.5g ", m_vec[i][j]);
    }
    printf("\n");
  }
#endif
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

void InverseProjection::Clear ()
{
  srcs.clear();
  hsvs.clear();
}

/*
void InverseProjection::getDistMatrix(std::vector<std::vector<double>> &vec){

// cria matriz de diferenças nos InverseProjectionas baseando-se no método de correlação

for (int i = 0; i < hists.size(); i++){
std::vector<double> s_vec;
for (int j = 0; j < hists.size(); j++){
s_vec.push_back(cv::compareHist(hists[i], hists[j], 3));
}
vec.push_back(s_vec);
}
}
*/

double InverseProjection::RadialBasisKernel (double* X1, double* X2, double sigma)
{
  return exp((-(pow(X2[0] - X1[0], 2) + pow(X2[1] - X1[1], 2))) / (2.0*sigma*sigma));
}

void InverseProjection::CalcInverseProjection01(
  int number_of_charts,
  int n_points_per_chart,
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

  for (int chnls = 0; chnls < number_of_charts; chnls++)
  {
    cv::Mat A = cv::Mat::zeros(n_points_per_chart, n_points_per_chart, cv::DataType<double>::type);
    for (int r = 0; r < n_points_per_chart; r++)
    {
      A.at<double>(r, r) = RadialBasisKernel(points[r + chnls*n_points_per_chart], points[r + chnls*n_points_per_chart], 0.75);;
      for (int c = r + 1; c < n_points_per_chart; c++)
      {
        double dist = RadialBasisKernel(points[r + chnls*n_points_per_chart], points[c + chnls*n_points_per_chart], 0.75);

        A.at<double>(r, c) = dist;
        A.at<double>(c, r) = dist;
      }
    }

    cv::Mat Ar = cv::Mat::zeros(1, n_points_per_chart, cv::DataType<double>::type);
    for (int r = 0; r < n_points_per_chart; r++)
      Ar.at<double>(0, r) = RadialBasisKernel(input[chnls], points[r + chnls*n_points_per_chart], 0.75);

    for (int pcol = 0; pcol < fimage.cols; pcol++)
    {
      for (int prow = 0; prow < fimage.rows; prow++)
      {
        cv::Mat C = cv::Mat::zeros(n_points_per_chart, 1, cv::DataType<double>::type);
        for (int i_imgs = 0; i_imgs < hsvs.size(); i_imgs++)
          C.at<double>(i_imgs, 0) = ((double)hsvs[i_imgs].at<cv::Vec3b>(prow, pcol).val[chnls]);

        cv::Mat M;
        A.copyTo(M);

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



