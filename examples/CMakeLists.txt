cmake_minimum_required(VERSION 3.27)
project(Soc_Example)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(EXAMPLE_SOURCES 
  main.cpp
)

add_executable(${PROJECT_NAME} ${EXAMPLE_SOURCES})

target_include_directories(${PROJECT_NAME} BEFORE PUBLIC ../)

target_compile_options(${PROJECT_NAME} PUBLIC -lm -Wall)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
