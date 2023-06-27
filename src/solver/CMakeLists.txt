set(SolverSrc solver.cpp)

add_library(Solver ${SolverSrc})
target_include_directories(Solver PRIVATE ${PROJECT_SOURCE_DIR}/inc)