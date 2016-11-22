#pragma once

#include "invproj.h"

InverseProjection::InverseProjection(){ }


void InverseProjection::ReadImages(std::vector<std::string> paths, int channel){

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

void InverseProjection::CalcInverseProjection(void){
  int h_bins = 180;
  int s_bins = 256;
  int v_bins = 256;
  int histSize[] = { h_bins, s_bins, v_bins };

  float h_ranges[] = { 0, 180 };
  float s_ranges[] = { 0, 256 };
  float v_ranges[] = { 0, 256 };

  const float* ranges[] = { h_ranges, s_ranges, v_ranges };

  /// InverseProjections
  for (int i = 0; i < hsvs.size(); i++){
    cv::MatND s_hist;
    calcHist(&hsvs[i], 1, 0, cv::Mat(), s_hist, 1, histSize, ranges, true, false);
    //normalize(s_hist, s_hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    hists.push_back(s_hist);
  }
}

void InverseProjection::getDistMatrix(std::vector<std::vector<double>> &vec){

  // cria matriz de diferen�as nos InverseProjectionas baseando-se no m�todo de correla��o 

  for (int i = 0; i < hists.size(); i++){
    std::vector<double> s_vec;
    for (int j = 0; j < hists.size(); j++){
      s_vec.push_back(cv::compareHist(hists[i], hists[j], 3));
    }
    vec.push_back(s_vec);
  }
}

void InverseProjection::test(){

  std::vector<std::string> paths;
  paths.push_back("images\\fusca\\fusca1.jpg");
  paths.push_back("images\\fusca\\fusca2.jpg");
  paths.push_back("images\\fusca\\fusca3.jpg");
  paths.push_back("images\\fusca\\fusca4.jpg");

  ReadImages(paths,0);
  //CalcInverseProjection();
  //std::vector<std::vector<double>> m_vec;
  //
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

void InverseProjection::Clear(){
  srcs.clear();
  hsvs.clear();
  hists.clear();
}

