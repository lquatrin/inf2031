#pragma once

#include "invproj.h"

#define MAX_UCHAR_IMAGE_VALUE 255.0

InverseProjection::InverseProjection () {}

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
void InverseProjection::CalcInverseProjection (void)
{
  if (srcs.size() == 0) return;

  int n = srcs.size();
  int s_w, s_h;
  s_w = srcs[0].rows;
  s_h = srcs[1].cols;

  printf("Image Size: %d %d %d\n", s_w, s_h, srcs[0].channels());

  int chnls = 0;

  //for (int chnls = 0; chnls < srcs[0].channels(); chnls++)
  //{
  for (int pcol = 0; pcol < s_w; pcol++)
  {
    for (int prow = 0; prow < s_h; prow++)
    {
      //Coeficientes
      cv::Mat A = cv::Mat::zeros(n, n, cv::DataType<double>::type);
      A.at<double>(1, 0) = 1.0;
      A.at<double>(2, 0) = 1.0;
      A.at<double>(0, 1) = 1.0;
      A.at<double>(0, 2) = 1.0;
      
      cv::Mat B = cv::Mat::zeros(n, 1, cv::DataType<double>::type);

      for (int i_imgs = 0; i_imgs < n; i_imgs++)
        B.at<double>(i_imgs, 0) = ((double)srcs[i_imgs].at<cv::Vec3b>(prow, pcol).val[chnls]) / MAX_UCHAR_IMAGE_VALUE;
      
      cv::Cholesky(A.ptr<double>(), A.step, A.rows, B.ptr<double>(), B.step, B.cols);
        
      return;
    }
  }
  //}
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
  
  //CalcInverseProjection();

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