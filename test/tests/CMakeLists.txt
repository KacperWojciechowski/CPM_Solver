set(UT_SOURCES data/AttributeTreeTests.cpp
               data/JobListTests.cpp)

add_executable(Tests ${UT_SOURCES})
target_include_directories(Tests PUBLIC ${CMAKE_HOME_DIRECTORY}/inc)
target_link_libraries(Tests PUBLIC gtest gmock gtest_main ${PROJECT_NAME})
set_target_properties(Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)