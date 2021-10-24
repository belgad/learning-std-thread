cmake_minimum_required(VERSION 3.17)
project(learning_std_thread)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(pi)
add_subdirectory(matrix)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} learning_std_thread_pi learning_std_thread_matrix)