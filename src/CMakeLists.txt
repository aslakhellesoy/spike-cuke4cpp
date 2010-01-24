project(cuke)

include_directories(${Boost_INCLUDE_DIR} ${GTEST_INCLUDE_DIR}
                    ${JSON_INCLUDE_DIR} ${CUKE_INCLUDE_DIR})

add_library(cuke cuke cuke_tcp_main)

target_link_libraries(cuke json ${GTEST_LIBRARIES} ${Boost_LIBRARIES})

install(TARGETS cuke LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

