cmake_minimum_required(VERSION 3.11 )
project(test)
set(CMAKE_CXX_FLAGS "-std=c++17")

find_package(PCL REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
add_definitions( ${PCL_DEFINITIONS} )

add_executable(AddPointStyle_test main.cpp)

target_link_libraries(AddPointStyle_test ${PCL_LIBRARIES} -lpthread -lboost_thread -DCMAKE_EXPORT_COMPILE_COMMANDS=1)