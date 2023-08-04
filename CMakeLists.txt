cmake_minimum_required(VERSION 3.26)
project(FileSearcher)

set(CMAKE_CXX_STANDARD 17)

add_library(FileSearcher file_search_library/file_search.h
        file_search_app/main.c)

add_executable(Searcher file_search_app/main.c
        file_search_library/file_search.c)

target_link_libraries(Searcher PRIVATE FileSearcher)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)