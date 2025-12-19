file(GLOB SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    )

file(GLOB HEADER
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    )

add_library(xml-compare-testlib STATIC
    ${SOURCES}
    ${HEADER}
    )

target_include_directories(xml-compare-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/xml-compare-testlib>
    )

target_link_libraries(xml-compare-testlib
    PUBLIC
    ${QTX}::Core
    ${QTX}::Xml
    )

export(TARGETS xml-compare-testlib NAMESPACE Zera:: FILE ZenuxCoreTargets.cmake)
install(TARGETS xml-compare-testlib
    EXPORT ZenuxCoreExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )

install(
    FILES ${HEADER}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/xml-compare-testlib
    )
