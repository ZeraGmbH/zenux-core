file(GLOB HEADER
    *.h
    )
file(GLOB SOURCES
    *.cpp
    )

add_library(zera-file-io-extensions SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-file-io-extensions
    PUBLIC
    ${QTX}::Core
    )

target_include_directories(zera-file-io-extensions
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-file-io-extensions>
    )

set_target_properties(zera-file-io-extensions PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-file-io-extensions PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS zera-file-io-extensions FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-file-io-extensions
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

generate_export_header(zera-file-io-extensions)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-file-io-extensions_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-file-io-extensions
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-file-io-extensions
    )
