cmake_minimum_required(VERSION 3.23)

project(TP3 VERSION 0.1.0 LANGUAGES CXX)

add_executable(TP3)

target_compile_options(TP3 PRIVATE -finput-charset=UTF-8 -fexec-charset=UTF-8)

if(MINGW)
  message(STATUS "Building with MinGW")
endif()

# Define tests path
target_compile_definitions(TP3 PRIVATE
  PROJECT_TEST_FILE="${CMAKE_SOURCE_DIR}/src/tests.txt"
)

target_sources(TP3
  PRIVATE
    src/principal.cpp
    src/liste.cpp
    src/stats.cpp
)
