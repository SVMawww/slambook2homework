cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(voxel_grid)

find_package(PCL 1.2 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (${PROJECT_NAME} main.cpp)
target_link_libraries (${PROJECT_NAME} ${PCL_LIBRARIES} -DCMAKE_EXPORT_COMPILE_COMMANDS=1)