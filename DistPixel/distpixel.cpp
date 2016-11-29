#include "distpixel.h"


distpixel::distpixel(){}

void distpixel::SetPaths(std::vector<std::string> image_paths,int channel){
  for (int i = 0; i < image_paths.size(); i++)
    srcs.push_back(cv::imread(image_paths[i], 1));

  for (int i = 0; i < srcs.size(); i++){
    // Separa a imagem em 3 componentes H S e V
    cv::Mat t_hsv;
    cv::cvtColor(srcs[i], t_hsv, cv::COLOR_BGR2HSV);
    hsvs.push_back(t_hsv);
  }
  ch = channel;
}
void distpixel::getDist(std::vector<std::vector<double>> &distMat){
  if (srcs.size() == 0) return;

  int n = srcs.size();
  int s_w, s_h;
  s_w = srcs[0].rows;
  s_h = srcs[1].cols;

  //to do - reducer a complexidade de O^4 para O^3
  
  double min = 0;
  double max = 0;
  for (int i = 0; i < n; i++){
    std::vector<double> d;
    for (int j = 0; j < n; j++){
      double sum = 0;
      for (int k = 0; k < s_w; k++){
        for (int w = 0; w < s_h; w++)
          sum += pow((((double)srcs[i].at<cv::Vec3b>(k, w).val[ch]) - ((double)srcs[j].at<cv::Vec3b>(k, w).val[ch])), 2);
      }
      sum = sqrt(sum);
      if (max < sum) max = sum;
      if (min > sum) min = sum;
      d.push_back(sum);
    }
    distMat.push_back(d);
  }

  for (int i = 0; i < distMat.size(); i++){
    for (int j = 0; j < distMat[i].size(); j++){
      double z = (distMat[i][j] - min) / (max - min);
      distMat[i][j] = z;
    }
  }

}

void distpixel::clear(){
  srcs.clear();
  hsvs.clear();
}

void distpixel::teste(){
  std::vector<std::string> paths;
  paths.push_back("images\\blue.png");
  paths.push_back("images\\red.png");
  paths.push_back("images\\green.png");
  SetPaths(paths, 0);
  std::vector<std::vector<double>> m_vec;

  getDist(m_vec);

  for (int i = 0; i < m_vec.size(); i++){
    for (int j = 0; j < m_vec[i].size(); j++){
      printf("%.5g ", m_vec[i][j]);
    }
    printf("\n");
  }
  
}