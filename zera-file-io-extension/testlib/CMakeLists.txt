file(GLOB HEADER
    *.h
    )
file(GLOB SOURCES
    *.cpp
    )

add_library(zera-file-io-extensions-testlib STATIC
    ${SOURCES}
    ${HEADER}
    )

target_include_directories(zera-file-io-extensions-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/zera-file-io-extensions-testlib>
    )

target_link_libraries(zera-file-io-extensions-testlib
    PUBLIC
    zera-file-io-extensions
    testlib-common
    )

set_target_properties(zera-file-io-extensions-testlib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(zera-file-io-extensions-testlib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

export(TARGETS zera-file-io-extensions-testlib NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS zera-file-io-extensions-testlib
    EXPORT ZenuxCoreExport
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/zera-file-io-extensions-testlib
    )
