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
#include <memory>

namespace puppy
{
	// --- リテラル型

#ifdef PUPPY_USE_DOUBLE
	/// @brief 浮動小数点型
	using float_t = double;
#else
	/// @brief 浮動小数点型
	using float_t = float;
#endif

	/// @brief バイト数や要素数を表す型
	using size_t = std::size_t;
	/// @brief 2つのポインタの差分を表す型
	using ptrdiff_t = std::ptrdiff_t;
	/// @brief nullptrを表すポインタのリテラル型
	using nullptr_t = std::nullptr_t;
	/// @brief バイトを表す型
	using byte_t = std::byte;

	// --- スマートポインタ型

	/// @brief スコープを持つポインタ
	template<class TPtr>
	using scope = std::unique_ptr<TPtr>;

	/// @brief スコープを持つポインタを生成する
	/// @param args 生成するオブジェクトのコンストラクタ引数
	template<class TPtr, class... Args>
	PUPPY_FORCE_INLINE
	constexpr scope<TPtr> make_scope(Args&&... args)
	{
		return std::make_unique<TPtr>(std::forward<Args>(args)...);
	}

	/// @brief スコープを持たないポインタ
	template<class TPtr>
	using ref = std::shared_ptr<TPtr>;

	/// @brief スコープを持たないポインタを生成する
	/// @param args 生成するオブジェクトのコンストラクタ引数
	template<class TPtr, class... Args>
	PUPPY_FORCE_INLINE
	constexpr ref<TPtr> make_ref(Args&&... args)
	{
		return std::make_shared<TPtr>(std::forward<Args>(args)...);
	}
}

#endif // _PUPPY_TYPES_HPP
