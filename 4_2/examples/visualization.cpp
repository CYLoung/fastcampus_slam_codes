// 출처: 임형태님 pcl_tutorial 코드
// https://github.com/LimHyungTae/pcl_tutorial

#include <pcl/PCLPointCloud2.h>
#include <pcl/common/transforms.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h> // cloud_visualizer 

#include <iostream>

// 파일을 받아서 ConstPtr을 return 함 
pcl::PointCloud<pcl::PointXYZ>::ConstPtr load_bin(const std::string &filename) {
  // 1. 파일을 열어서 유효성을 체크
  std::ifstream file(filename, std::ios::binary);
  if (!file) {
    std::cerr << "Error: failed to load " << filename << std::endl;
    return nullptr;
  }
  // 2. 빈 cloud 생성
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

  // 3. point 좌표 생성과 파일의 point 값을 읽어줌 
  pcl::PointXYZ point;
  while (file) {
    // Read x, y and z coordinates
    std::cout << "START" << std::endl;
    file.read((char *)&point.x, sizeof(point.x));
    file.read((char *)&point.y, sizeof(point.y));
    file.read((char *)&point.z, sizeof(point.z));
    // Ignore the intensity value if there is one
    file.ignore(sizeof(float));
    std::cout << (char *)&point.x, sizeof(point.x) << std::endl;
    if (file) // If the reads above were successful
      cloud->push_back(point);
  }

  return cloud;
}

void colorize(const pcl::PointCloud<pcl::PointXYZ> &pc,
              pcl::PointCloud<pcl::PointXYZRGB> &pc_colored,
              const std::vector<int> &color) {
  int N = pc.points.size();
  pc_colored.clear();

  pcl::PointXYZRGB pt_rgb;
  for (int i = 0; i < N; ++i) {
    const auto &pt = pc.points[i];
    pt_rgb.x = pt.x;
    pt_rgb.y = pt.y;
    pt_rgb.z = pt.z;
    pt_rgb.r = color[0];
    pt_rgb.g = color[1];
    pt_rgb.b = color[2];
    pc_colored.points.emplace_back(pt_rgb);
  }
}

int main(int argc, char **argv) {
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr shifted_cloud(
      new pcl::PointCloud<pcl::PointXYZ>);
  *cloud = *load_bin("./000000.bin");
  std::cout << "why"<< std::endl;
  Eigen::Matrix4f tf;
  // clang-format off
  tf << 1.0, 0.0, 0.0, 5.0,
        0.0, 1.0, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0;
  // clang-format on
  pcl::transformPointCloud(*cloud, *shifted_cloud, tf);

  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_colored(
      new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr shifted_cloud_colored(
      new pcl::PointCloud<pcl::PointXYZRGB>);

  // Point cloud XYZ에 RGB 칼라 추가하기
  colorize(*cloud, *cloud_colored, {255, 0, 0});
  colorize(*shifted_cloud, *shifted_cloud_colored, {0, 255, 0});

  pcl::visualization::PCLVisualizer viewer1("Simple Cloud Viewer");
  // viewer 가 어떻게 보여줬으면 좋겠니~!
  viewer1.addPointCloud<pcl::PointXYZRGB>(cloud_colored, "src_red");
  viewer1.addPointCloud<pcl::PointXYZRGB>(shifted_cloud_colored, "tgt_green");

  // 한 바퀴만 돌고 다음 코드 실행!
  // == waitKey 똑같이 1 넣으면 1 millis 기다리고 그럼 
  while (!viewer1.wasStopped()) {
    viewer1.spinOnce();
  }

  return 0;
}