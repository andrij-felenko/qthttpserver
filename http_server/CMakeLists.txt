cmake_minimum_required(VERSION 3.14)
project(qt_http_server)

set (qt_http_server_h
    include/QtHttpServer/qthttpserverglobal.h
    include/QtHttpServer/qabstracthttpserver.h
    include/QtHttpServer/qhttpserver.h
    include/QtHttpServer/qhttpserverrequest.h
    include/QtHttpServer/qhttpserverresponder.h
    include/QtHttpServer/qhttpserverresponse.h
    include/QtHttpServer/qhttpserverrouter.h
    include/QtHttpServer/qhttpserverrouterrule.h
    include/QtHttpServer/qhttpserverrouterviewtraits.h
    )

set (qt_http_server_private
    qabstracthttpserver_p.h
    qhttpserver_p.h
    qhttpserverliterals_p.h
    qhttpserverrequest_p.h
    qhttpserverresponder_p.h
    qhttpserverresponse_p.h
    qhttpserverrouter_p.h
    qhttpserverrouterrule_p.h
    )

set (qt_http_server_cpp
    qabstracthttpserver.cpp
    qhttpserver.cpp
    qhttpserverliterals.cpp
    qhttpserverrequest.cpp
    qhttpserverresponder.cpp
    qhttpserverresponse.cpp
    qhttpserverrouter.cpp
    qhttpserverrouterrule.cpp
    )

set (CMAKE_AUTOMOC ON)
find_package(Qt6Core)
find_package(Qt6Network)

add_library(qt_http_server ${qt_http_server_h} ${qt_http_server_cpp} ${qt_http_server_private})

target_link_libraries(qt_http_server qt_ssl_server http_parser Qt6::Core Qt6::Network)
target_include_directories(qt_http_server
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC $<TARGET_PROPERTY:qt_ssl_server,INTERFACE_INCLUDE_DIRECTORIES>
    PUBLIC $<TARGET_PROPERTY:http_parser,INTERFACE_INCLUDE_DIRECTORIES>
    PRIVATE include/QtHttpServer
    PRIVATE ${Qt6Core_PRIVATE_INCLUDE_DIRS})
