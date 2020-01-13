// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++

#pragma lib "/$M/lib/ape/liblua.a"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
