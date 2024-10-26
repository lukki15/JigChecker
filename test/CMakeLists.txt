cmake_minimum_required(VERSION 3.14...3.22)

project(JigCheckerTests LANGUAGES CXX)

# ---- Options ----

option(ENABLE_TEST_COVERAGE "Enable test coverage" OFF)
option(TEST_INSTALLED_VERSION "Test the version found by find_package" OFF)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage("gh:google/googletest@1.15.2")
CPMAddPackage("gh:TheLartians/Format.cmake@1.7.3")

if(TEST_INSTALLED_VERSION)
  find_package(JigChecker REQUIRED)
else()
  CPMAddPackage(NAME JigChecker SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
endif()

# ---- Create binary ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)
add_executable(${PROJECT_NAME} ${sources})

# GTest::gmock GTest::gmock_main
target_link_libraries(${PROJECT_NAME} PRIVATE JigChecker::JigChecker GTest::gtest GTest::gtest_main)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# enable compiler warnings
if(NOT TEST_INSTALLED_VERSION)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(JigChecker PUBLIC -Wall -Wpedantic -Wextra -Werror)
  elseif(MSVC)
    target_compile_options(JigChecker PUBLIC /W4 /WX)
  endif()
endif()

# ---- Add JigCheckerTests ----

enable_testing()

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# ---- code coverage ----

if(ENABLE_TEST_COVERAGE)
  target_compile_options(JigChecker PUBLIC -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(JigChecker PUBLIC -fprofile-arcs -ftest-coverage)
endif()
