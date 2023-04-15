/*
 *    ___                        ____                                   __
 *   / _ \__ _____  ___  __ __  / __/______ ___ _  ___ _    _____  ____/ /__
 *  / ___/ // / _ \/ _ \/ // / / _// __/ _ `/  ' \/ -_) |/|/ / _ \/ __/  '_/
 * /_/   \_,_/ .__/ .__/\_, / /_/ /_/  \_,_/_/_/_/\__/|__,__/\___/_/ /_/\_\
 *          /_/  /_/   /___/
 * Copyright (c) 2023 TarobeWanwanLand.
 * Released under the MIT license. see http://opensource.org/licenses/MIT
 */

#ifndef _PUPPY_TYPES_HPP
#define _PUPPY_TYPES_HPP

#include <cstddef>

namespace puppy
{
#ifdef PUPPY_USE_DOUBLE
	using float_t = double;
#else
	using float_t = float;
#endif

	using size_t = std::size_t;
	using ptrdiff_t = std::ptrdiff_t;
	using nullptr_t = std::nullptr_t;
}

#endif // _PUPPY_TYPES_HPP
