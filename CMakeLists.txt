cmake_minimum_required(VERSION 3.24)
project(RailwayManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(RailwayManager main.cpp src/Station.cpp src/Station.h src/Graph.cpp src/Graph.h src/Trip.cpp src/Trip.h)
