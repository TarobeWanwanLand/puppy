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

#define PUPPY_EXPECTS(...) _PUPPY_CONTRACTS("pre-condition", __VA_ARGS__)
#define PUPPY_ASSERT(...)  _PUPPY_CONTRACTS("assertion", __VA_ARGS__)
#define PUPPY_ENSURES(...) _PUPPY_CONTRACTS("post_condition", __VA_ARGS__)

#define _PUPPY_CONTRACTS(kind, ...) ::puppy::detail::contracts(                     \
	::puppy::detail::matches_bool(__VA_ARGS__),                                     \
	__FILE__ ":" PUPPY_TO_STRING(__LINE__) ": " kind " `" #__VA_ARGS__ "` failed",  \
	PUPPY_PRETTY_FUNCTION)

namespace puppy::detail
{
	constexpr void contracts(bool result, const char* msg, const char* func) noexcept
	{
		if (!result) PUPPY_UNLIKELY
		{
#if PUPPY_DEBUG
			if (!std::is_constant_evaluated())
			{
				std::cerr << msg << " in `" << func << "`" << std::endl;
			}
#endif
			std::abort();
		}
	}

	template<class T>
	requires std::is_same_v<std::remove_cvref_t<T>, bool>
	constexpr bool matches_bool(T&& value) noexcept
	{
		return value;
	}
}

#endif // _PUPPY_CONTRACTS_HPP