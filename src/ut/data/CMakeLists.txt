set(DATA_UT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/JobListTests.cpp)

add_library(Data_UT ${DATA_UT_SOURCES})
target_include_directories(Data_UT PUBLIC ${CMAKE_HOME_DIRECTORY}/inc ${GTEST_INCLUDE_DIR})