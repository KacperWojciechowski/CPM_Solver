set(SOLVER_SOURCES solver/NetworkBuilder.cpp)

add_library(Solver ${SOLVER_SOURCES})
target_include_directories(Solver PRIVATE inc)