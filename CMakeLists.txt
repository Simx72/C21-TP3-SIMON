cmake_minimum_required(VERSION 3.23)

project(TP3 VERSION 0.1.0 LANGUAGES CXX)

add_executable(TP3)

target_sources(TP3
  PRIVATE
    src/principal.cpp
    src/liste.cpp
    src/stats.cpp
)
