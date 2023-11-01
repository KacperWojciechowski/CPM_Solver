set(DATA_SOURCES JobList.cpp)

add_library(Data ${DATA_SOURCES})
target_include_directories(Data PRIVATE ${CMAKE_HOME_DIRECTORY}/inc ${CMAKE_HOME_DIRECTORY}/lib)
