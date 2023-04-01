/*
 *  types.hpp is part of the puppy project.
 *  Copyright (C) 2023 TarobeWanwanLand.
 *
 *  Released under the MIT license.
 *  see http://opensource.org/licenses/MIT
 */

#ifndef PUPPY_TYPES_HPP
#define PUPPY_TYPES_HPP

#include <cstddef>
#include <cstdint>

namespace puppy
{
	using int8 = int8_t;
	using int16 = int16_t;
	using int32 = int32_t;
	using int64 = int64_t;

	using uint8 = uint8_t;
	using uint16 = uint16_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;

	using char8 = char8_t;
	using char16 = char16_t;
	using char32 = char32_t;

	using size_t = std::size_t;

	inline std::ostream& operator<<(std::ostream& os, const char8* str)
	{
		return os << reinterpret_cast<const char*>(str);
	}
}

#endif //PUPPY_TYPES_HPP
