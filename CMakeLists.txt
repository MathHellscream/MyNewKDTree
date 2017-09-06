cmake_minimum_required(VERSION 3.8)
project(KDTree)

set(CMAKE_CXX_STANDARD 14)

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag(-Wall temp)
if(temp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
check_cxx_compiler_flag(-pedantic temp)
if(temp)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
endif()

set(SOURCE_FILES
        CSVHandler.h
        KDTree.h
        KDTreeNode.h
        main.cpp
        cmake-build-debug/newTestData.csv)

add_executable(KDTree ${SOURCE_FILES})