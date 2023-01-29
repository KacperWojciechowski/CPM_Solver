cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

project(CPM_solver)

set(SolverSources src/Network.cpp
                  src/CostMatrixTextFileParser.cpp
                  src/NetBuilder.cpp)
add_library(Solver ${SolverSources})
target_include_directories(Solver PUBLIC inc)

add_executable(Exec src/main.cpp)

target_link_libraries(Exec
                      Solver)

set_target_properties(Exec PROPERTIES CXX_STANDARD 20)
target_compile_features(Exec PUBLIC cxx_std_20)
target_include_directories(Exec PUBLIC inc)

target_compile_options(Exec PUBLIC -Wall -Wextra -pedantic -Werror)

add_custom_target(run_solver COMMAND ./Exec DEPENDS Exec)
