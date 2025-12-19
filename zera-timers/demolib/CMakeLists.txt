file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(zera-timers-demolib STATIC
    ${SOURCES}
    ${HEADER}
)

target_include_directories(zera-timers-demolib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-timers-demolib>
    )

target_link_libraries(zera-timers-demolib
    PUBLIC
    ${QTX}::Core
)

set_target_properties(zera-timers-demolib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-timers-demolib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(zera-timers-demolib)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-timers-demolib_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-timers-demolib
    )

export(TARGETS zera-timers-demolib NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-timers-demolib
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-timers-demolib
    )
