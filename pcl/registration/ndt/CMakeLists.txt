cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(normal_distributions_transform)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (normal_distributions_transform main.cpp)
target_link_libraries (normal_distributions_transform ${PCL_LIBRARIES} -lpthread)