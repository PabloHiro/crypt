cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project(crypt_tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static-libgcc -static-libstdc++")

add_definitions(-LOG_ERR)

add_executable(crypt_test crypt_test.cpp custom_xml_parser.cpp)
target_link_libraries(crypt_test PRIVATE crypt)


#Call tests with make test
add_test(
    NAME caesar
    COMMAND crypt_test "${CMAKE_CURRENT_SOURCE_DIR }/data/caesar.xml" > "caesar.log"
)
