#pragma once

#include "OrpheanAssert.hpp"



#include <QMap>


#ifdef ORPHEAN_DEBUG

#include <iostream>
template <typename T>
void OrpheanLog(T arg) {
	std::cout << arg;
}

template <typename T, typename ...Ts>
void OrpheanLog(T arg, Ts... args) {
	std::cout << arg;
	OrpheanLog(args...);
}

#else

template <typename ...>
void OrpheanLog(...) {}

#endif

