cmake_minimum_required(VERSION 3.1)

project(zenux-core LANGUAGES C CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_VERSION_MAJOR "0")
set(PROJECT_VERSION_MINOR "0")
set(PROJECT_VERSION_PATCH "1")
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

include(FeatureSummary)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

find_package(Qt5 COMPONENTS Core Xml XmlPatterns Test CONFIG REQUIRED)

enable_testing()

# Inspired by
# https://github.com/KDAB/kdabtv/blob/master/Qt-Widgets-and-more/UnitTests/Tests/CMakeLists.txt
function(SETUP_QTESTS)
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
            Qt5::Xml
            zera-timers-testlib
            zera-log-statistics
            tasks-base-testlib
            zera-xmlconfig
            xml-config-test-data
            xml-compare-testlib
            )
    endforeach()
endfunction()

add_subdirectory(zera-tasks-base)
add_subdirectory(zera-timers)
add_subdirectory(zera-log-statistics)
add_subdirectory(zera-xmlconfig)
add_subdirectory(testlibs)

write_basic_package_version_file(
    ZenuxCoreConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )
configure_file(ZenuxCoreConfig.cmake.in ZenuxCoreConfig.cmake @ONLY)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ZenuxCoreConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ZenuxCoreConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZenuxCore
    )

install(EXPORT ZenuxCoreExport
    FILE ZenuxCoreTargets.cmake
    NAMESPACE Zera::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ZenuxCore
    )

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
