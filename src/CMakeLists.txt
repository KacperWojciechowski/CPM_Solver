add_subdirectory(ut)
add_subdirectory(data)
add_subdirectory(solver)

add_library(UTs INTERFACE)
target_link_libraries(UTs INTERFACE Data_UT)