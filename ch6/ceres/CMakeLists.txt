cmake_minimum_required(VERSION 3.23)

project(fitting)

find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)

set(CMAKE_CXX_STANDARD 17)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CERES_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ceresCurveFitting.cpp )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} Ceres::ceres -DCMAKE_EXPORT_COMPILE_COMMANDS=1)