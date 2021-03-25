cmake_minimum_required(VERSION 3.0.0)
project(zonecounter VERSION 0.1.0)


add_library(zonecount SHARED zonecount_impl.cpp)

add_executable(zonecounter zonecount_impl.cpp
                            main.cpp)                       


set_target_properties(zonecount PROPERTIES
                                LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                                CXX_STANDARD 17
                                CXX_EXTENSIONS OFF
                                CXX_STANDARD_REQUIRED YES)                   

set_target_properties(zonecounter PROPERTIES
                                RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
                                CXX_STANDARD 17
                                CXX_EXTENSIONS OFF
                                CXX_STANDARD_REQUIRED YES)    