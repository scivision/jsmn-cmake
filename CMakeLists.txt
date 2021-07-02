cmake_minimum_required(VERSION 3.11...3.21)

project(JSMNdemo LANGUAGES C)

enable_testing()

include(FetchContent)


# --- auto-ignore build directory
if(NOT EXISTS ${PROJECT_BINARY_DIR}/.gitignore)
  file(WRITE ${PROJECT_BINARY_DIR}/.gitignore "*")
endif()

include(cmake/jsmn.cmake)

set(json_fn ${CMAKE_CURRENT_SOURCE_DIR}/test_data/simple.json)

add_executable(simple simple.c)
target_include_directories(simple PRIVATE ${jsmn_SOURCE_DIR})
target_compile_features(simple PRIVATE c_std_99)

add_test(NAME Simple COMMAND $<TARGET_FILE:simple> ${json_fn})
set_tests_properties(Simple PROPERTIES
  TIMEOUT 5
  PASS_REGULAR_EXPRESSION "Power: 11")
