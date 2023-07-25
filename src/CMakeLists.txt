add_subdirectory(ut)

set(DATA_SOURCES data/AttributeTree.cpp
                 data/JobList.cpp)

add_library(Data ${DATA_SOURCES})
target_include_directories(Data PRIVATE inc)


set(SOLVER_SOURCES solver/NetworkBuilder.cpp)

add_library(Solver ${SOLVER_SOURCES})
target_include_directories(Solver PRIVATE inc)