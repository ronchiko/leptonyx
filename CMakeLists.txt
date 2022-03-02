cmake_minimum_required(VERSION 3.21)

project(LeptonyxHttpServer)

include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)
list(FILTER SOURCES EXCLUDE REGEX "test_.*\.c")
list(FILTER SOURCES  EXCLUDE REGEX "main\.c")

add_library(LeptonyxLib STATIC ${SOURCES})

add_executable(Leptonyx src/main.c)
target_link_libraries(Leptonyx PRIVATE 
	LeptonyxLib
)

enable_testing()

file(GLOB_RECURSE TESTS CONFIGURE_DEPENDS src/test_*.c)
foreach(FILE ${TESTS})
	string(REGEX REPLACE "${CMAKE_SOURCE_DIR}/src" "" TEST ${FILE})
	string(REPLACE "/" "_" TEST ${TEST})

	add_executable(test${TEST} ${FILE})
	target_link_libraries(test${TEST} PRIVATE LeptonyxLib)
	target_include_directories(test${TEST} PRIVATE include)

	add_test(test${TEST} test${TEST} ${CMAKE_CURRENT_LIST_DIR})
endforeach()

