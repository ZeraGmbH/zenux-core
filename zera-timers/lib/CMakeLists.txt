file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

add_library(zera-timers SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-timers
    PUBLIC
    ${QTX}::Core
    )

target_include_directories(zera-timers
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/timers>
    )

set_target_properties(zera-timers PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-timers PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(zera-timers)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-timers_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/timers
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/timers
    )


add_library(zera-timers-static STATIC
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-timers-static
    PUBLIC
    ${QTX}::Core
    )

target_include_directories(zera-timers-static
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/timers>
    )

set_target_properties(zera-timers-static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-timers-static PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})


export(TARGETS zera-timers zera-timers-static FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-timers
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(TARGETS zera-timers-static
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

