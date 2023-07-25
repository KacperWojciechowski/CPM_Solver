set(DATA_SOURCES data/AttributeTree.cpp
                 data/JobList.cpp)

add_library(Data ${DATA_SOURCES})
target_include_directories(Data PRIVATE inc)