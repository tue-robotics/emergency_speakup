cmake_minimum_required(VERSION 3.0.2)
project(emergency_speakup)

add_compile_options(-Wall -Werror=all)
add_compile_options(-Wextra -Werror=extra)

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
