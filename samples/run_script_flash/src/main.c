/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include <zephyr/logging/log.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

LOG_MODULE_REGISTER(main);

const char lua_script_bin[] = {
#include "main.lua.inc"
};

static int lua_run_script(const char *script_str)
{
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);

    luaL_dostring(L, script_str);

    lua_close(L);
    return 0;
}

void main(void)
{
	lua_run_script(lua_script_bin);
}
