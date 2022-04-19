cmake_minimum_required(VERSION 2.8)
project(opencv_demo)

set(CMAKE_CXX_STANDARD 11)
set(INCLUDE_DIR /usr/local/include/opencv4)

include_directories(${INCLUDE_DIR})
link_directories(/usr/local/lib)

add_executable(opencv_demo answer_1.cpp)
target_link_libraries(opencv_demo opencv_core opencv_imgproc opencv_highgui
                                    opencv_video opencv_videoio opencv_imgcodecs)



