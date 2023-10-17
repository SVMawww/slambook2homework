cmake_minimum_required(VERSION 3.23)

project(fitting)

find_package(OpenCV REQUIRED)
find_package(g2o REQUIRED)
if(NOT g2o_FOUND)
   message(FATAL_ERROR "G2O not found.")
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${G2O_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} g2oCurveFitting.cpp )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} g2o::core -DCMAKE_EXPORT_COMPILE_COMMANDS=1)