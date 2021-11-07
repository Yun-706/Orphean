#pragma once
#include <cassert>
#include <string>

#ifdef YUN_NO_ASSERT

#define YUN_INFO_ASSERT(exp, info)

#else

#define YUN_INFO_ASSERT(assertExp, info) _ASSERT_EXPR(assertExp, (std::wstring(L#assertExp)+L"\nMessage: "+std::wstring(info)).data())

#endif // YUN_NO_ASSERT


