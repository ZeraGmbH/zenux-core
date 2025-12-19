file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(tasks-base-testlib STATIC
    ${SOURCES}
    ${HEADER}
)

target_include_directories(tasks-base-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/tasks-base-testlib>
    )

target_link_libraries(tasks-base-testlib
    PUBLIC
    ${QTX}::Core
    zera-tasks-base
    zera-timers-testlib
)

generate_export_header(tasks-base-testlib)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/tasks-base-testlib_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tasks-base-testlib
    )

export(TARGETS tasks-base-testlib NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS tasks-base-testlib
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/tasks-base-testlib
    )
