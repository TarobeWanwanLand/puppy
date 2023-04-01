/*
 *  unicode_convert.hpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#ifndef PUPPY_UNICODE_CONVERT_HPP
#define PUPPY_UNICODE_CONVERT_HPP

#include <type_traits>
#include <vector>
#include "../common.hpp"

namespace puppy
{
	// UTF-8 -> UTF-32
	inline std::vector<> utf8_to_utf32(const char8* src)
	{
		static_assert(std::is_same_v<TChar32, char32_t>, "TChar32 must be char32_t.");

		if (src == nullptr)
		{
			return;
		}
	}
}

#endif //PUPPY_UNICODE_CONVERT_HPP
