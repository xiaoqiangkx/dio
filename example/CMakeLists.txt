cmake_minimum_required(VERSION 3.5)

PROJECT(example)

add_subdirectory(simple)

target_compile_options(dio PUBLIC -std=c++11)
