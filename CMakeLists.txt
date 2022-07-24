cmake_minimum_required(VERSION 3.20)

file(STRINGS VERSION VERSION LIMIT_COUNT 1)
project("osmchinaoffset" VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 14)

enable_testing()

message("[***] CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message("[***] CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")
message("[***] CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")


# =============================================================================
# Sources
# =============================================================================
file(GLOB_RECURSE HEADERS "src/*.hh")
file(GLOB_RECURSE SRCS "src/*.cc")


# =============================================================================
# 3rd libraries
# =============================================================================
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(Osmium 2.18.0 REQUIRED COMPONENTS io)


set(INCLUDE_DIRS
    src
    )

set(LIBS
	${OSMIUM_LIBRARIES}
    )


# =============================================================================
# define exec target
# =============================================================================
add_executable(${PROJECT_NAME} ${HEADERS} ${SRCS})
set_pthread_on_target(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS} ${OSMIUM_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBS})

include(CMakePackageConfigHelpers)
configure_file(src/version.hh.cmake.in
    ${CMAKE_CURRENT_SOURCE_DIR}/src/version.hh)


# =============================================================================
# define install
# =============================================================================
install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION bin
    )


# =============================================================================
# Tests
# =============================================================================
find_package(GTest REQUIRED)
message("GTest_VERSION=${GTest_VERSION}")

file(GLOB_RECURSE TESTS "test/*.test.cc")

add_executable(${PROJECT_NAME}_test ${TESTS})
target_include_directories(${PROJECT_NAME}_test PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}_test PRIVATE ${LIBS})
target_link_libraries(${PROJECT_NAME}_test PRIVATE GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_add_tests(TARGET ${PROJECT_NAME}_test)
