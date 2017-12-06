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

set(TESING_REGEX "function lock doesn't work properly: ")
add_test( caesar crypt_test caesar.xml)
set_tests_properties( caesar PROPERTIES FAIL_REGULAR_EXPRESSION ${TESING_REGEX})

add_test( affine crypt_test affine.xml)
set_tests_properties( affine PROPERTIES FAIL_REGULAR_EXPRESSION  ${TESING_REGEX})

add_test( portabellaso crypt_test portabellaso.xml)
set_tests_properties( portabellaso PROPERTIES FAIL_REGULAR_EXPRESSION  ${TESING_REGEX})
add_test( vigenere_txt crypt_test vigenere_txt.xml)
set_tests_properties( vigenere_txt PROPERTIES FAIL_REGULAR_EXPRESSION  ${TESING_REGEX})

add_test( transposition1 crypt_test transposition1.xml)
set_tests_properties( transposition1 PROPERTIES FAIL_REGULAR_EXPRESSION  ${TESING_REGEX})

add_test( transposition2 crypt_test transposition2.xml)
set_tests_properties( transposition2 PROPERTIES FAIL_REGULAR_EXPRESSION  ${TESING_REGEX})