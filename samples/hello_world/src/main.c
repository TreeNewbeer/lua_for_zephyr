/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/zephyr.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

typedef int (*lua_CFunction) (lua_State *L);

int c_add(lua_State *L)
{
	int a = luaL_checknumber(L,1); //取 lua 函数栈第1个参数
	int b = luaL_checknumber(L,2); //取 lua 函数栈第2个参数
	lua_pushnumber(L, a + b); // 将返回值继续压栈
	return 1;  //返回值用于告诉 lua 解析器结果压栈个数
}

const char lua_test[] = {
	"g_lua_int_val = 10086\n"
	"g_lua_str_val = '我爱黄老板'\n"

    "function lua_add(a, b)\n"
    "  return a + b\n"
    "end\n"

	"print(\"c_add(10, 20) = \",c_add(10, 20))\n"

};

static int lua_run_script(const char *script_str)
{
    lua_State *L;
    L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_base(L);

	lua_register(L, "c_add", c_add);

    luaL_dostring(L, script_str);

	//获取int变量
	lua_getglobal(L, "g_lua_val");
	int lua_int_val = lua_tointeger(L, -1);
	printk("---------- lua g_lua_val 变量:%d\n", lua_int_val);
	//获取 str 变量
	lua_getglobal(L, "g_lua_str_val");
	char *lua_str = lua_tostring(L, -1);
	printk("---------- lua g_lua_str_val 变量:%s\n", lua_str);

	//调用 lua_add 函数
	lua_getglobal(L, "lua_add");
    lua_pushnumber(L, 10);
    lua_pushnumber(L, 20);
	int ret = lua_pcall(L, 2, 1, 0);
	if (ret != 0) {
        printf("error %s\n", lua_tostring(L, -1));
        return -1;
    }
	int sum = lua_tonumber(L, -1);
    lua_pop(L, 1);
	printk("lua_add(10, 20) = %d\n", sum);

    lua_close(L);
    return 0;
}

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);
	lua_run_script(lua_test);

	
}
