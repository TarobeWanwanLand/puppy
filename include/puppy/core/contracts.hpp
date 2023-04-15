/*
 *    ___                        ____                                   __
 *   / _ \__ _____  ___  __ __  / __/______ ___ _  ___ _    _____  ____/ /__
 *  / ___/ // / _ \/ _ \/ // / / _// __/ _ `/  ' \/ -_) |/|/ / _ \/ __/  '_/
 * /_/   \_,_/ .__/ .__/\_, / /_/ /_/  \_,_/_/_/_/\__/|__,__/\___/_/ /_/\_\
 *          /_/  /_/   /___/
 * Copyright (c) 2023 TarobeWanwanLand.
 * Released under the MIT license. see http://opensource.org/licenses/MIT
 */

#ifndef _PUPPY_CONTRACTS_HPP
#define _PUPPY_CONTRACTS_HPP

#include <type_traits>
#include <iostream>
#include "common.hpp"

#if PUPPY_DEBUG

#define PUPPY_EXPECTS(...) _PUPPY_CONTRACT("pre-condition", __VA_ARGS__)
#define PUPPY_ASSERT(...)  _PUPPY_CONTRACT("assertion", __VA_ARGS__)
#define PUPPY_ENSURES(...) _PUPPY_CONTRACT("post_condition", __VA_ARGS__)

#define _PUPPY_CONTRACT(kind, ...) ::puppy::detail::contract(                       \
	::puppy::detail::matches_bool(__VA_ARGS__),                                     \
	__FILE__ ":" PUPPY_TO_STRING(__LINE__) ": " kind " `" #__VA_ARGS__ "` failed",  \
	PUPPY_PRETTY_FUNCTION)

namespace puppy::detail
{
	constexpr void contract(bool result, const char* msg, const char* func) noexcept
	{
		if (!result) PUPPY_UNLIKELY
		{
			if (!std::is_constant_evaluated())
			{
				std::cerr << msg << " in `" << func << "`" << std::endl;
			}
			std::abort();
		}
	}

	template<class T>
	requires std::is_same_v<std::remove_cvref_t<T>, bool>
	constexpr bool matches_bool(T t) noexcept
	{
		return t;
	}
}

#else

#define PUPPY_EXPECTS(...) (void)0
#define PUPPY_ASSERT(...)  (void)0
#define PUPPY_ENSURES(...) (void)0

#endif

#endif // _PUPPY_CONTRACTS_HPP