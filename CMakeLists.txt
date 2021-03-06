if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	    MESSAGE(FATAL_ERROR "Prevented in-tree built. This is bad practice.")
endif()

cmake_minimum_required(VERSION 2.8.4)
project(jsmn)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(LIBRARY_NAME ${PROJECT_NAME})

function(MAKE_TEST ARG_TEST_NAME)
    add_executable(${ARG_TEST_NAME} ${ARGN})
    target_link_libraries(${ARG_TEST_NAME} ${LIBRARY_NAME})
    add_test(NAME ${ARG_TEST_NAME} COMMAND ${ARG_TEST_NAME})
endfunction()

set(JSMN_SOURCES "jsmn.c" "jsmn_extras.c")
set(JSMN_PUBLIC_INCLUDES "jsmn.h" "jsmn_extras.h")

add_definitions(-DJSMN_PARENT_LINKS)

add_library(${LIBRARY_NAME} STATIC ${JSMN_SOURCES})
add_executable(simple_example example/simple.c ${LIBRARY_NAME} ${JSMN_PUBLIC_INCLUDES})
add_executable(jsondump example/jsondump.c ${LIBRARY_NAME} ${JSMN_PUBLIC_INCLUDES})

if(NOT DEFINED NO_TESTS)
    MAKE_TEST(jsmn_test test/tests.c)
    MAKE_TEST(extras_test test/extras_tests.c)
    enable_testing()
endif()

install(TARGETS ${LIBRARY_NAME} ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(FILES ${JSMN_PUBLIC_INCLUDES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include)