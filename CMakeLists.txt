cmake_minimum_required(VERSION 3.0.0)
project(zonecounter VERSION 0.1.0)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

#The library will be used for python.
add_library(zonecount SHARED src/zonecount_impl.cpp)

add_executable(zonecounter src/zonecount_impl.cpp
                            src/main.cpp)                       


set_target_properties(zonecount PROPERTIES
                                LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib
                                CXX_STANDARD 17
                                CXX_EXTENSIONS OFF
                                CXX_STANDARD_REQUIRED YES)                   

set_target_properties(zonecounter PROPERTIES
                                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin
                                CXX_STANDARD 17
                                CXX_EXTENSIONS OFF
                                CXX_STANDARD_REQUIRED YES)    