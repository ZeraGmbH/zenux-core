file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )
file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

add_library(zenux-device-info SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zenux-device-info
    PUBLIC
    Qt5::Core
    )

target_include_directories(zenux-device-info
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/zenux-device-info>
    )

set_target_properties(zenux-device-info PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zenux-device-info PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

generate_export_header(zenux-device-info)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zenux-device-info_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/zenux-device-info
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/zenux-device-info
    )


add_library(zenux-device-info-static STATIC
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zenux-device-info-static
    PUBLIC
    Qt5::Core
    )

target_include_directories(zenux-device-info-static
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zenux-core/zenux-device-info>
    )

set_target_properties(zenux-device-info-static PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zenux-device-info-static PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})


export(TARGETS zenux-device-info zenux-device-info-static FILE ZenuxCoreTargets.cmake)
install(TARGETS zenux-device-info
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(TARGETS zenux-device-info-static
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

