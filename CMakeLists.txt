cmake_minimum_required(VERSION 2.8.9)
project(rtklibcpp)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
                        "${gmock_SOURCE_DIR}/include"
    )
endif()

#Bring the headers, such as Student.h into the project
include_directories(include ${CMAKE_SOURCE_DIR}/src ${CMAKE_BINARY_DIR}/)

set(RCVSRC
${CMAKE_SOURCE_DIR}/src/rcv/binex.cpp
${CMAKE_SOURCE_DIR}/src/rcv/cmr.cpp
${CMAKE_SOURCE_DIR}/src/rcv/crescent.cpp
${CMAKE_SOURCE_DIR}/src/rcv/gw10.cpp
${CMAKE_SOURCE_DIR}/src/rcv/javad.cpp
${CMAKE_SOURCE_DIR}/src/rcv/novatel.cpp
${CMAKE_SOURCE_DIR}/src/rcv/nvs.cpp
${CMAKE_SOURCE_DIR}/src/rcv/rcvlex.cpp
${CMAKE_SOURCE_DIR}/src/rcv/rt17.cpp
${CMAKE_SOURCE_DIR}/src/rcv/septentrio.cpp
${CMAKE_SOURCE_DIR}/src/rcv/skytraq.cpp
${CMAKE_SOURCE_DIR}/src/rcv/ss2.cpp
${CMAKE_SOURCE_DIR}/src/rcv/tersus.cpp
${CMAKE_SOURCE_DIR}/src/rcv/ublox.cpp
)
set(rtklibSrc
${CMAKE_SOURCE_DIR}/src/ephemeris.cpp
${CMAKE_SOURCE_DIR}/src/geoid.cpp
${CMAKE_SOURCE_DIR}/src/ionex.cpp
${CMAKE_SOURCE_DIR}/src/lambda.cpp
${CMAKE_SOURCE_DIR}/src/pntpos.cpp
${CMAKE_SOURCE_DIR}/src/postpos.cpp
${CMAKE_SOURCE_DIR}/src/ppp.cpp
${CMAKE_SOURCE_DIR}/src/ppp_ar.cpp
${CMAKE_SOURCE_DIR}/src/ppp_corr.cpp
${CMAKE_SOURCE_DIR}/src/preceph.cpp
${CMAKE_SOURCE_DIR}/src/qzslex.cpp
${CMAKE_SOURCE_DIR}/src/rcvraw.cpp
${CMAKE_SOURCE_DIR}/src/rinex.cpp
${CMAKE_SOURCE_DIR}/src/rtcm.cpp
${CMAKE_SOURCE_DIR}/src/rtcm2.cpp
${CMAKE_SOURCE_DIR}/src/rtcm3.cpp
${CMAKE_SOURCE_DIR}/src/rtcm3e.cpp
${CMAKE_SOURCE_DIR}/src/rtkcmn.cpp
${CMAKE_SOURCE_DIR}/src/rtkpos.cpp
${CMAKE_SOURCE_DIR}/src/sbas.cpp
${CMAKE_SOURCE_DIR}/src/solution.cpp
${CMAKE_SOURCE_DIR}/src/tides.cpp
${CMAKE_SOURCE_DIR}/src/rtklib.h
${CMAKE_SOURCE_DIR}/src/gpstime.h
${CMAKE_SOURCE_DIR}/src/obs_t.h
${CMAKE_SOURCE_DIR}/src/obs_t.cpp
)

set(COMMIT_HASH "")
set(BRANCH_NAME "")
find_package(Git QUIET)
if(GIT_FOUND)
execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
    OUTPUT_VARIABLE COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} symbolic-ref --short -q HEAD
    OUTPUT_VARIABLE BRANCH_NAME
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
endif()
message(STATUS "Git version is ${BRANCH_NAME}:${COMMIT_HASH}")

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/ver.h.ini
  ${CMAKE_BINARY_DIR}/ver.h
  @ONLY
  )

set(SOURCES
# main/main.cpp
main/test.cpp
${CMAKE_BINARY_DIR}/ver.h
)

source_group(main FILES ${SOURCES})
source_group(rtklib FILES ${rtklibSrc})
source_group(rtklib\\rcv FILES ${RCVSRC})

OPTION(TRACE
"Build the project using macro"
OFF)

IF(TRACE)
message("use trace")
add_definitions(-D_USE_RTKLIB_TRACE -DLOW_COST_BOARD)
endif(TRACE)

add_definitions(-DENAGLO)

set(TARGET_BASE_NAME "solve_")
set(TARGET_NAME "${TARGET_BASE_NAME}${BRANCH_NAME}")
add_executable(${TARGET_NAME} ${SOURCES} ${RCVSRC} ${rtklibSrc})

IF (WIN32)
TARGET_LINK_LIBRARIES(${TARGET_NAME} winmm)
ENDIF ()

enable_testing()
# link_directories(/usr/local/lib)
target_link_libraries( ${TARGET_NAME} gtest gtest_main)