file(GLOB SOURCES
    *.h
    *.cpp
)

add_library(zera-file-io-extensions-testlib STATIC
    ${SOURCES}
    )

target_include_directories(zera-file-io-extensions-testlib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    )

target_link_libraries(zera-file-io-extensions-testlib
    PUBLIC
    zera-file-io-extensions
    testlib-common
    )
