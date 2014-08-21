cmake_minimum_required(VERSION 2.8.3)
project(emergency_speakup)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(emergency_speakup src/emergency_speakup.cpp)
target_link_libraries(emergency_speakup ${catkin_LIBRARIES})



