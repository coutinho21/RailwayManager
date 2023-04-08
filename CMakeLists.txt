cmake_minimum_required(VERSION 3.24)
project(RailwayManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(RailwayManager main.cpp src/StationTrip.cpp src/StationTrip.h src/Graph.cpp src/Graph.h src/AuxMain.cpp src/AuxMain.h src/Tripaux.cpp)
