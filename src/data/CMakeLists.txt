set(DATA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/AttributeTree.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/JobList.cpp)

add_library(Data ${DATA_SOURCES})
target_include_directories(Data PRIVATE ${CMAKE_HOME_DIRECTORY}/inc)