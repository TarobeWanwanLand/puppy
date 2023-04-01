/*
 *  assert.hpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#ifndef PUPPY_ASSERT_HPP
#define PUPPY_ASSERT_HPP

#include <iostream>
#include "common.hpp"

#if PUPPY_DEBUG
	#define PUPPY_ASSERT(expr, ...) \
        ((expr) ? (void)0 : ::puppy::detail::assertion_failed(#expr, __FILE__, __func__, __LINE__, ##__VA_ARGS__))

namespace puppy
{
	inline void
	assertion_failed(const char8* expr, const char8* file, const char8* func, uint64 line, const char8* msg = nullptr)
	{
		std::cerr << "Assertion failed: " << expr << '\n';
		std::cerr << "File: " << file << '\n';
		std::cerr << "Func: " << func << '\n';
		std::cerr << "Line: " << line << '\n';
		if (msg != nullptr)
			std::cerr << "Message: " << msg << '\n';
		std::abort();
	}
}
#else
	#define PUPPY_ASSERT(expr, ...) (void)0
#endif

#endif // PUPPY_ASSERT_HPP
