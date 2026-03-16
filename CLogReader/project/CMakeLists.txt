cmake_minimum_required(VERSION 3.10)

project(CLogReader LANGUAGES CXX)

add_library(CLogReader_lib STATIC
        clogreader.cpp
        clogreader.h
        search.h
)

target_include_directories(CLogReader_lib PUBLIC
     ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(CLogReader
    main.cpp
)

target_link_libraries(
    CLogReader
    CLogReader_lib)
