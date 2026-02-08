file(GLOB HEADER
    *.h
    )
file(GLOB SOURCES
    *.cpp
    )

add_library(zera-jsonobject-to-string SHARED
    ${HEADER}
    ${SOURCES}
    )

target_link_libraries(zera-jsonobject-to-string
    PUBLIC
    ${QTX}::Core
    )

target_include_directories(zera-jsonobject-to-string
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-jsonobject-to-string>
    )

set_target_properties(zera-jsonobject-to-string PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-jsonobject-to-string PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

install(TARGETS zera-jsonobject-to-string
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

generate_export_header(zera-jsonobject-to-string)
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/zera-jsonobject-to-string_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-jsonobject-to-string
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-jsonobject-to-string
    )
