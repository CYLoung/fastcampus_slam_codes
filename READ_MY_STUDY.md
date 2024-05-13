# SLAM COURSE
- 목적 : 부족한 부분을 채우기 위함 

<details>
<summary>240514</summary>

<!-- summary 아래 한칸 공백 두어야함 -->
# 4_2강
- Goals : PCL 라이브러리를 이용해 기본적인 포인트 클라우드 자료구조를 다뤄보고, 시각화 해보기



1. 2개의 포인트 클라우드를 시각화
- KITTIT 데이터셋에서 추출한 1개의 Lidar Point Cloud data 를 읽음
- 5m 이동 시킨 포인트 클라우드 생성
- 두개의 포인트 클라우드를 각각 다른색으로 시각화 

2. KITTI 데이터셋 시각화
- KITTI 데이터셋에 있는 LiDAR Point cloud 시각화


### PCL code 설명
- [PCL lib](http://pointclouds.org/documentation/index.html)
- [PCL documentation](https://pcl.readthedocs.io/projects/tutorials/en/master/)
- #include <pcl/visualization/pcl_visualizer.h> // cloud_visualizer 
- 두개 있는데 ! cloud visualizaer 가 좀 더 빠르다고 알려져 있지만 1.8이상 pcl version 이어야 함 
- apt 를 통해 libpcl-dev 를 깔면 현재 자동 1.13 깔림 
- but... cloud 는 호환성이 떨어짐

- Ptr => boot::shared_pt 로 되어있음 ! 사이즈가 달라지고 변경될 수도 있고, memory 를 효율적으로 사용하기 위해서! 
- new, delete 가 아닌 smart pointer 를 쓰는 것이 좋지만, 여기서는 boost::shared_ptr 이기 때문에 new 사용
- Stack ! 정적, Heap 동적!


# CMakeLists.txt
```shell
add_executable(visualization examples/visualization.cpp)
target_link_libraries(visualization ${PCL_LIBRARIES} ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES})
```
- 위에서 특정라이브러리만 쓰고 싶다! 할 때  ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES} ${PCL_VISUALIZATION_LIBRARIES}
- 아니라면  ${PCL_LIBRARIES}


## TODO 
- 실험 해볼 수 있게 local folder mount 할 수 있도록 변경하기

</details>
