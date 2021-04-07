cmake_minimum_required(VERSION 3.19)
project(http_parser)

set (http_parser_h
    include/http_parser.h
    )

set (http_parser_cpp
    http_parser.c
    )

add_library(http_parser ${http_parser_h} ${http_parser_cpp})

target_link_libraries(http_parser)
target_include_directories(http_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
