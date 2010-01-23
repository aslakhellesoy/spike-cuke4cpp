cmake_minimum_required(VERSION 2.8)
project(cuke4cpp)

enable_testing(true)
include(CTest)

find_package(Boost COMPONENTS regex thread system REQUIRED)
find_package(GTest REQUIRED)

include_directories(${BOOST_INCLUDE_DIR} ${GTEST_INCLUDE_DIR} include)

add_library(cuke src/cuke.cpp src/cuke_tcp_main.cpp)

install(TARGETS cuke ARCHIVE DESTINATION lib)
install(DIRECTORY include/cuke DESTINATION include)


