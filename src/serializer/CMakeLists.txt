set(SERIALIZER_SOURCES XmlSerializer.cpp)

add_library(Serializer ${SERIALIZER_SOURCES})
target_include_directories(Serializer PRIVATE ${CMAKE_HOME_DIRECTORY}/inc ${CMAKE_HOME_DIRECTORY}/lib)
