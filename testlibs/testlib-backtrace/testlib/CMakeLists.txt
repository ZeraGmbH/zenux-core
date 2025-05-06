file(GLOB SRCS
    *.c
    *.cpp
)

file(GLOB HEADERS
    *.h
)

add_library(testlib-backtrace STATIC
    ${SRCS}
    ${HEADERS}
    )

target_include_directories(testlib-backtrace
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/testlib-backtrace>
    )

target_link_libraries(testlib-backtrace
    PUBLIC
    Qt5::Core
    PRIVATE
    dl
)

set_target_properties(testlib-backtrace PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(testlib-backtrace PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(testlib-backtrace)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/testlib-backtrace_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-backtrace
    )

export(TARGETS testlib-backtrace NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS testlib-backtrace
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-backtrace
    )
