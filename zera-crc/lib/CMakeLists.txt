file(GLOB HEADER
    *.h
    )
file(GLOB SOURCES
    *.cpp
    )

add_library(zera-crc SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-crc
    PUBLIC
    ${QTX}::Core
    )

target_include_directories(zera-crc
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-crc>
    )

set_target_properties(zera-crc PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-crc PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS zera-crc
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

generate_export_header(zera-crc)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-crc_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-crc
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-crc
    )
