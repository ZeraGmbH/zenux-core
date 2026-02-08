# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS_JSON)
    foreach(_testname ${ARGN})
        add_test(NAME ${_testname}
                 COMMAND ${_testname})
        add_executable(${_testname}
            ${_testname}.h
            ${_testname}.cpp
            test-data.qrc
            )
        target_link_libraries(${_testname}
            PUBLIC
            ${QTX}::Test
            zera-jsonobject-to-string
            testlib-common
        )
    endforeach()
endfunction()

SETUP_QTESTS_JSON(
    test_convert_value
    test_convert_array
    test_convert_object
)
