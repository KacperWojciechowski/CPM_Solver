set (DataSrc JobList.cpp)

add_library(Data ${DataSrc})
target_include_directories(Data PRIVATE ${PROJECT_SOURCE_DIR}/inc)