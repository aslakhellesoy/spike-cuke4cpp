cmake_minimum_required(VERSION 2.8)
project(cuke4cpp)

#enable_testing(true)
#include(CTest)

set(Boost_USE_STATIC_LIBS   OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS regex thread system REQUIRED)

find_package(GTest REQUIRED)

set(CUKE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(DIRECTORY ${CUKE_INCLUDE_DIR}/cuke DESTINATION include)

add_subdirectory(3rd_party)
add_subdirectory(src)
add_subdirectory(examples)

