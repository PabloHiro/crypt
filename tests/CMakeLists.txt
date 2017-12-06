cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project(crypt_tests)

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static-libgcc -static-libstdc++")

add_executable(crypt_test crypt_test.cpp custom_xml_parser.cpp)
target_include_directories(crypt_test PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(crypt_test crypt)
target_compile_options(crypt_test PRIVATE -std=c++11 -Wall -static-libgcc -static-libstdc++)

#Copy the data test
# add_custom_command(TARGET crypt_test PRE_BUILD
   # COMMAND ${CMAKE_COMMAND} -E copy_directory
   # ${CMAKE_CURRENT_SOURCE_DIR}/data $<TARGET_FILE_DIR:crypt_test>)

#Call tests with make test
add_test(
    NAME caesar
    COMMAND crypt_test caesar.xml 2>> crypt.log
)
add_test(
    NAME affine
    COMMAND crypt_test affine.xml 2>> crypt.log
)
add_test(
    NAME portabellaso
    COMMAND crypt_test portabellaso.xml 2>> crypt.log
)
add_test(
    NAME vigenere_txt
    COMMAND crypt_test vigenere_txt.xml 2>> crypt.log
)
add_test(
    NAME transposition1
    COMMAND crypt_test transposition1.xml 2>> crypt.log
)
add_test(
    NAME transposition2
    COMMAND crypt_test transposition2.xml 2>> crypt.log
)