# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_FILE_EXT)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            )
        target_link_libraries(${_testname}
            PRIVATE
            ${QTX}::Test
            zera-file-io-extensions
            zera-file-io-extensions-testlib
            zera-timers-testlib
        )
    endforeach()
endfunction()

SETUP_QTESTS_FILE_EXT(
    test_safe_file_loader
    test_utf8_validator
    test_cp1252_validator
)
