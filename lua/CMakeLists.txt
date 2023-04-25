# SPDX-License-Identifier: Apache-2.0

add_library(lua STATIC)
target_sources(lua PRIVATE
                lua/lapi.c
                lua/lauxlib.c
                lua/lbaselib.c
                lua/lcode.c
                lua/lcorolib.c
                lua/lctype.c
                lua/ldblib.c
                lua/ldebug.c
                lua/ldo.c
                lua/ldump.c
                lua/lfunc.c
                lua/lgc.c
                lua/linit.c
                lua/liolib.c
                lua/llex.c
                lua/lmathlib.c
                lua/lmem.c
                lua/loadlib.c
                lua/lobject.c
                lua/lopcodes.c
                lua/loslib.c
                lua/lparser.c
                lua/lstate.c
                lua/lstring.c
                lua/lstrlib.c
                lua/ltable.c
                lua/ltablib.c
                lua/ltm.c
                lua/lundump.c
                lua/lutf8lib.c
                lua/lvm.c
                lua/lzio.c)

target_include_directories(lua
                INTERFACE lua
                PRIVATE lua
)

target_sources(app PRIVATE port/port.c)

target_link_libraries(lua zephyr_interface)

target_compile_options(lua PRIVATE
                        -Wall -O2 -std=c99
                        -DLUA_USE_READLINE
                        -fno-stack-protector -fno-common)
