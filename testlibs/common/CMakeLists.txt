file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(testlib-common STATIC
    ${SOURCES}
    ${HEADER}
)

target_include_directories(testlib-common
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/testlib-common>
    )

target_link_libraries(testlib-common
    PUBLIC
    Qt5::Core
    Qt5::Test
    zera-timers
    zera-timers-testlib
)

set_target_properties(testlib-common PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(testlib-common PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(testlib-common)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/testlib-common_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-common
    )

export(TARGETS testlib-common NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS testlib-common
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/testlib-common
    )
