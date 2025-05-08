function(SETUP_MEMORY_ALLOC_BACKTRACE)
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
            Qt5::Test
            testlib-backtrace
            )
    endforeach()
endfunction()

SETUP_MEMORY_ALLOC_BACKTRACE(
    test_memory_alloc_backtrace_generator
    )
