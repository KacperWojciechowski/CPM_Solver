set(DATA_UT_SOURCES AttributeTreeTests.cpp
                    JobListTests.cpp)

add_executable(DATA_UT ${DATA_UT_SOURCES})
target_include_directories(DATA_UT PUBLIC ${CMAKE_HOME_DIRECTORY}/inc)
target_link_libraries(DATA_UT PUBLIC gtest gmock gtest_main ${PROJECT_NAME})
set_target_properties(DATA_UT PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build/ut_runtimes)