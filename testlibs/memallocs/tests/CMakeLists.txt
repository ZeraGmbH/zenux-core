function(SETUP_OPENFILE_TESTS)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname} COMMAND ${_testname})
        add_executable(${_testname} ${_testname}.h ${_testname}.cpp)
        target_include_directories(${_testname}
            PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
            ${PROJECT_SOURCE_DIR}/src
            )
        target_link_libraries(${_testname}
            PUBLIC
            -Wl,--whole-archive
            testlib-memallocs
            -Wl,--no-whole-archive
            Qt5::Test
            testlib-memallocs
            )
    endforeach()
endfunction()

SETUP_OPENFILE_TESTS(
    test_memallocs_atomic
    test_backtrace_converter
    test_backtrace_tree_generator
    )
