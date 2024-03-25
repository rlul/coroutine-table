#pragma once
#include <experimental/generator>

template<typename T>
std::experimental::generator<T> Generate(int count);
