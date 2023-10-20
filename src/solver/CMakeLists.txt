set(SOLVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/NetworkBuilder.cpp)

add_library(Solver ${SOLVER_SOURCES})
target_include_directories(Solver PRIVATE ${CMAKE_HOME_DIRECTORY}/inc)