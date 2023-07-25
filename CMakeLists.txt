cmake_minimum_required(VERSION 3.22)

project(CPMSolver CXX)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20 /permissive-")
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wformat -Werror -Wunused -Wattributes")
endif ()

set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include")

add_subdirectory(src)
add_subdirectory(lib)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} INTERFACE
                      Data
                      Solver
                      pugixml)

add_executable(${PROJECT_NAME}-UT src/ut/empty.cpp)
target_include_directories(${PROJECT_NAME}-UT PUBLIC inc ${GTEST_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}-UT
                      gtest
                      gmock
                      gtest_main
                      ${PROJECT_NAME})

add_custom_target(ut COMMAND ./${PROJECT_NAME}-UT DEPENDS ${PROJECT_NAME}-UT)
enable_testing()

add_test(
	NAME allTests
	COMMAND tests
)