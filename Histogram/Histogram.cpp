
#pragma once
#include "Histogram.h"


Histogram::Histogram(){ }


void Histogram::ReadImages(std::vector<std::string> paths){

  for (int i = 0; i < paths.size(); i++)
    srcs.push_back(cv::imread(paths[i], 1));

  for (int i = 0; i < srcs.size(); i++){
    cv::Mat s_hsv;
    cv::cvtColor(srcs[i], s_hsv, cv::COLOR_BGR2HSV);
    hsvs.push_back(s_hsv);
  }

}


void Histogram::CalcHistogram(void){
  /// Using 16 bins for hue and 16 for saturation
  int h_bins = 16; int s_bins = 16;
  int histSize[] = { h_bins, s_bins };

  // hue varies from 0 to 179, saturation from 0 to 255
  float h_ranges[] = { 0, 180 };
  float s_ranges[] = { 0, 256 };

  const float* ranges[] = { h_ranges, s_ranges };

  // Use the o-th and 1-st channels
  int channels[] = { 0, 1};


  /// Histograms
  for (int i = 0; i < hsvs.size(); i++){
    cv::MatND s_hist;
    calcHist(&hsvs[i], 1, channels, cv::Mat(), s_hist, 2, histSize, ranges, true, false);
    normalize(s_hist, s_hist, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    hists.push_back(s_hist);
  }

}

void Histogram::getDistMatrix(std::vector<std::vector<double>> &vec){

  // cria matriz de diferenças nos histogramas baseando-se no método de correlação 

  for (int i = 0; i < hists.size(); i++){
    std::vector<double> s_vec;
    for (int j = 0; j < hists.size(); j++){
      s_vec.push_back(cv::compareHist(hists[i], hists[j], 0));
    }
    vec.push_back(s_vec);
  }
}

void Histogram::test(){

  std::vector<std::string> paths;
  paths.push_back("C:\\Users\\schirmer\\Documents\\GitHub\\inf2031\\Histogram\\images\\fusca1.png");
  paths.push_back("C:\\Users\\schirmer\\Documents\\GitHub\\inf2031\\Histogram\\images\\fusca2.png");
  paths.push_back("C:\\Users\\schirmer\\Documents\\GitHub\\inf2031\\Histogram\\images\\fusca3.png");

  ReadImages(paths);
  CalcHistogram();
  std::vector<std::vector<double>> m_vec;

  getDistMatrix(m_vec);

  for (int i = 0; i < m_vec.size(); i++){
    for (int j = 0; j < m_vec[i].size(); j++){
      printf("%.5g ", m_vec[i][j]);
    }
    printf("\n");
  }
}

