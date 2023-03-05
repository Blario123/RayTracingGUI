cmake_minimum_required(VERSION 3.23)

project(RayTracingGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(ray-tracer)
add_subdirectory(GUI)

include_directories(GUI)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} GUI RayTracer)

