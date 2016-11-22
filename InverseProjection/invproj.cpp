#pragma once

#include "invproj.h"

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

void InverseProjection::CalcInverseProjection (void)
{
  //Number of C's
  std::vector<double> C;


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
    
    printf("[%s] %d:\n", paths[i].c_str(), i);
    printf(" - %.03d %.03d %.03d\n", blue, green, red);
  }
  
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