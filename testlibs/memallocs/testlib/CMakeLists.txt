file(GLOB SRCS
    *.c
    *.cpp
)

file(GLOB HEADERS
    *.h
)

add_library(testlib-memallocs STATIC
    ${SRCS}
    ${HEADERS}
    )


target_include_directories(testlib-memallocs
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/testlib-memallocs>
    )

target_link_libraries(testlib-memallocs
    PUBLIC
    ${QTX}::Core
    PRIVATE
    dl
)

set_target_properties(testlib-memallocs PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(testlib-memallocs PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(testlib-memallocs)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/testlib-memallocs_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-memallocs
    )

export(TARGETS testlib-memallocs NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS testlib-memallocs
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-memallocs
    )
