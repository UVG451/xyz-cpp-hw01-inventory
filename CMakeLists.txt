cmake_minimum_required(VERSION 3.18)
project(BallInventory LANGUAGES CXX)
add_executable(BallInventory main.cpp)
target_compile_features(BallInventory PRIVATE cxx_std_17)
