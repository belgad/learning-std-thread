cmake_minimum_required(VERSION 3.17)
project(learning_std_thread_pi)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} pi/pi.cc)
