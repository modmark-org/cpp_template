cmake_minimum_required(VERSION 3.10)

project(template)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if( NOT CMAKE_BUILD_TYPE )
   SET( CMAKE_BUILD_TYPE Release )
endif()

add_executable(template "template.cpp" "include/nlohmann/json.hpp") 