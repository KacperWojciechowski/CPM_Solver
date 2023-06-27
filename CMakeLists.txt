cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

project(CPMSolver)

add_executable(${PROJECT_NAME} src/main.cpp)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME}
                      Solver)
                      #pugixml)

target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Wextra -pedantic -Werror)

add_custom_target(run_solver COMMAND ./${PROJECT_NAME} DEPENDS ${PROJECT_NAME})
