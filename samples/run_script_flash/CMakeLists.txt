# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(run_script_flash)

target_sources(app PRIVATE src/main.c)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../../common/lua  ${CMAKE_CURRENT_BINARY_DIR}/lua)

target_link_libraries(app PRIVATE lua)

set(gen_dir ${ZEPHYR_BINARY_DIR}/include/generated/)
generate_inc_file_for_target(
    app
    ${CMAKE_CURRENT_SOURCE_DIR}/script/main.lua
    ${gen_dir}/main.lua.inc
)
