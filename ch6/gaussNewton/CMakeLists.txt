cmake_minimum_required(VERSION 3.23)

project(gaussNewton)

find_package(OpenCV REQUIRED)
# find_package(Eigen REQUIRED)    

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} gaussNewton.cpp )

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} -DCMAKE_EXPORT_COMPILE_COMMANDS=1)
