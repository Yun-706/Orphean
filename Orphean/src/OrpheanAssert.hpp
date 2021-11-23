#pragma once
#include <cassert>
#include <string>

#if defined(ORPHEAN_DEBUG)
	#define ORPHEAN_ASSERT_INFO(assertExp, info) _ASSERT_EXPR(assertExp, (std::wstring(L#assertExp)+L"\nMessage: "+std::wstring(info)).data())
	#define ORPHEAN_ASSERT(assertExp) assert(assertExp)
#else
	#define ORPHEAN_ASSERT_INFO(assertExp, info)
	#define ORPHEAN_ASSERT(assertExp)
#endif


