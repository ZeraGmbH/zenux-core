file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(zera-timers-testlib STATIC
    ${SOURCES}
    ${HEADER}
)

target_include_directories(zera-timers-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-timers-testlib>
    )

target_link_libraries(zera-timers-testlib
    PUBLIC
    Qt5::Core
    zera-timers
)

set_target_properties(zera-timers-testlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-timers-testlib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(zera-timers-testlib)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-timers-testlib_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-timers-testlib
    )

export(TARGETS zera-timers-testlib NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-timers-testlib
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-timers-testlib
    )
