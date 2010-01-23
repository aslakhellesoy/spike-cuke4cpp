cmake_minimum_required(VERSION 2.6)
project(jsoncpp)

include_directories(include)

add_library(json src/lib_json/json_reader.cpp
                 src/lib_json/json_value.cpp
                 src/lib_json/json_writer.cpp)

install(TARGETS json ARCHIVE DESTINATION lib)

install(DIRECTORY include/json DESTINATION include)


