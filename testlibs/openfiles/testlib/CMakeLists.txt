file(GLOB SRCS
    *.c
    *.cpp
)

file(GLOB HEADERS
    *.h
)

add_library(testlib-openfiles STATIC
    ${SRCS}
    ${HEADERS}
    )


target_include_directories(testlib-openfiles
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/testlib-openfiles>
    )

target_link_libraries(testlib-openfiles
    PUBLIC
    Qt5::Core
    PRIVATE
    dl
)

set_target_properties(testlib-openfiles PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(testlib-openfiles PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(testlib-openfiles)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/testlib-openfiles_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-openfiles
    )

export(TARGETS testlib-openfiles NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS testlib-openfiles
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-openfiles
    )
