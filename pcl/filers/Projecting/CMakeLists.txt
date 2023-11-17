cmake_minimum_required(VERSION 3.23)

project(project_inliers)

set(CMAKE_CXX_FLAGS "-std=c++17")

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
add_definitions( ${PCL_DEFINITIONS} )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} -lpthread -lboost_thread -DCMAKE_EXPORT_COMPILE_COMMANDS=1)