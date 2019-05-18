cmake_minimum_required(VERSION 2.8.3)
project(cap_limit)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

catkin_package(
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)

## Declare a C++ executable
add_executable(cap_limit src/cap_limit_node.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(cap_limit
  ${catkin_LIBRARIES}
  wiringPi
)

