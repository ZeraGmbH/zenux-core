file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

add_library(zera-log-statistics SHARED
    ${HEADER}
    ${SOURCES}
)

target_link_libraries(zera-log-statistics
    PUBLIC
    ${QTX}::Core
    zera-timers
    )

target_include_directories(zera-log-statistics
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/log-statistics>
    )

set_target_properties(zera-log-statistics PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-log-statistics PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(zera-log-statistics)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-log-statistics_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/log-statistics
    )

export(TARGETS zera-log-statistics FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-log-statistics
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/log-statistics
    )

