cmake_minimum_required(VERSION 3.22)

project(CPMSolver CXX)

SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
endif()

set(GTEST_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include")

add_subdirectory(lib)

if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wformat -Werror -Wunused -Wattributes")
endif()

add_subdirectory(src)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE inc)
target_link_libraries(${PROJECT_NAME} INTERFACE
                      Data
                      Solver
                      pugixml)

add_executable(${PROJECT_NAME}-UT src/ut/empty.cpp)
target_link_libraries(${PROJECT_NAME}-UT
                      gtest
                      gmock
                      gtest_main
                      UTs
                      ${PROJECT_NAME})

add_custom_target(ut COMMAND ./${PROJECT_NAME}-UT DEPENDS ${PROJECT_NAME}-UT)
enable_testing()

add_test(
	NAME allTests
	COMMAND tests
)
