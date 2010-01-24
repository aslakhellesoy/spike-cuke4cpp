project(jsoncpp)

set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include CACHE INTERNAL "")

include_directories(${JSON_INCLUDE_DIR})

add_library(json src/lib_json/json_reader src/lib_json/json_value src/lib_json/json_writer)

#install(TARGETS json ARCHIVE DESTINATION lib)
#install(DIRECTORY ${JSON_INCLUDE_DIR}/json DESTINATION include)

