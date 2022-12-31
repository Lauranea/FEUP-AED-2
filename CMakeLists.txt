cmake_minimum_required(VERSION 3.10)

project(transportes_aerios)

include_directories(src)

set(SOURCE
src/main.cpp
src/Read.cpp
src/Read.h
src/Airport.cpp
src/Airport.h
src/Airline.cpp
src/Airline.h
src/Flight.cpp
src/Flight.h
src/FlightManager.cpp
src/FlightManager.h
src/Graph.cpp
src/Graph.h
)

add_executable(${PROJECT_NAME} ${SOURCE})

add_definitions("-g")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)