# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_CRC)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            )
        target_link_libraries(${_testname}
            PUBLIC
            ${QTX}::Test
            zera-crc
            testlib-common
        )
    endforeach()
endfunction()

SETUP_QTESTS_CRC(
    test_crc8_maxim
    test_crc32_iso_hdlc
    test_pseudo_crc_buffer
)
