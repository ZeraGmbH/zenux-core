file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

add_library(zera-tasks-base SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-tasks-base
    PUBLIC
    ${QTX}::Core
    zera-timers
    )

target_include_directories(zera-tasks-base
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/tasks-base>
    )

set_target_properties(zera-tasks-base PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-tasks-base PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(zera-tasks-base)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-tasks-base_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/tasks-base
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/tasks-base
    )


add_library(zera-tasks-base-static STATIC
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-tasks-base-static
    PUBLIC
    ${QTX}::Core
    zera-timers-static
    )

target_include_directories(zera-tasks-base-static
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/tasks-base>
    )

set_target_properties(zera-tasks-base-static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-tasks-base-static PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS zera-tasks-base zera-tasks-base-static FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-tasks-base
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(TARGETS zera-tasks-base-static
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
