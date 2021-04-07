project(test_qhttp_server)

find_package(Qt6Core)
add_executable(test_qhttp_server main.cpp)
target_link_libraries(test_qhttp_server qt_http_server Qt6::Core)
target_include_directories(test_qhttp_server
    PUBLIC $<TARGET_PROPERTY:qt_http_server,INTERFACE_INCLUDE_DIRECTORIES>)
add_definitions( -DMY_RC_PATH="${CMAKE_CURRENT_SOURCE_DIR}" )
