/*
 *    ___                        ____                                   __
 *   / _ \__ _____  ___  __ __  / __/______ ___ _  ___ _    _____  ____/ /__
 *  / ___/ // / _ \/ _ \/ // / / _// __/ _ `/  ' \/ -_) |/|/ / _ \/ __/  '_/
 * /_/   \_,_/ .__/ .__/\_, / /_/ /_/  \_,_/_/_/_/\__/|__,__/\___/_/ /_/\_\
 *          /_/  /_/   /___/
 * Copyright (c) 2023 TarobeWanwanLand.
 * Released under the MIT license. see http://opensource.org/licenses/MIT
 */

#ifndef _PUPPY_STRING_VIEW_HPP
#define _PUPPY_STRING_VIEW_HPP

#include "common.hpp"
#include "contracts.hpp"
#include <numeric>
#include <utility>

namespace puppy
{
	/// @brief 文字列を参照するためのクラス
	/// @tparam TChar 文字列の文字型
	/// @tparam TTraits 文字列の文字型の特性
	template<class TChar, class TTraits = std::char_traits<TChar>>
	requires (!std::is_array_v<TChar>
	       && std::is_trivial_v<TChar>
	       && std::is_standard_layout_v<TChar>
	       && std::is_same_v<TChar, typename TTraits::char_type>)
	class basic_string_view final
	{
	public:
		// --- 型エイリアス定義
		using traits_type            = TTraits;
		using value_type             = TChar;
		using pointer                = value_type*;
		using const_pointer          = const value_type*;
		using reference              = value_type&;
		using const_reference        = const value_type&;
		using iterator               = value_type*;
		using const_iterator         = const value_type*;
		using reverse_iterator       = std::reverse_iterator<value_type*>;
		using const_reverse_iterator = std::reverse_iterator<const value_type*>;
		using size_type              = size_t;
		using difference_type        = ptrdiff_t;

		// --- 定数定義

		/// @brief 文字列の末尾を表す値
		static constexpr size_type npos = size_type(-1);

		// --- コンストラクタ

		/// @brief デフォルトコンストラクタ
		/// @details 文字列を持たない状態で初期化する
		PUPPY_NODISCARD_CTOR
		constexpr basic_string_view() noexcept
			: _str{nullptr}, _size{0}
		{}

		/// @brief 文字列を指定して初期化する
		/// @param str 文字列
		PUPPY_NODISCARD_CTOR
		constexpr basic_string_view(const value_type* str) noexcept
			: _str{PUPPY_EXPECTS(str, str != nullptr)}
			, _size{traits_type::length(str)}
		{}

		/// @brief 文字列と長さを指定して初期化する
		/// @param str 文字列
		/// @param size 文字列の長さ
		PUPPY_NODISCARD_CTOR
		constexpr
		basic_string_view(const value_type* str, size_type size) noexcept
			: _str{str}, _size{size}
		{}

		/// @brief 文字列の範囲を指定して初期化する
		/// @param first 文字列の範囲の先頭
		/// @param last 文字列の範囲の末尾
		template<
		    std::contiguous_iterator TItrator,
			std::sized_sentinel_for<TItrator> TEnd>
		requires std::same_as<std::iter_value_t<TItrator>, value_type>
		    && (!std::convertible_to<TEnd, size_type>)
		PUPPY_NODISCARD_CTOR
		constexpr basic_string_view(TItrator first, TEnd last)
		noexcept(noexcept(last - first))
			: _str{std::to_address(first)}
			, _size{last - first}
		{}

		/// @brief 文字列の範囲を指定して初期化する
		/// @param range 文字列の範囲
		template<
		    class TRange,
			class TDanglingRange = std::remove_cvref_t<TRange>>
		requires (!std::is_same_v<TDanglingRange, basic_string_view>)
			&& std::ranges::contiguous_range<TRange>
			&& std::ranges::sized_range<TRange>
			&& std::is_same_v<std::ranges::range_value_t<TRange>, value_type>
			&& (!std::is_convertible_v<TRange, const value_type*>)
			&& (!requires (TDanglingRange& d) {
				d.operator basic_string_view<value_type, traits_type>();
			})
			&& (!requires { typename TDanglingRange::traits_type; }
				|| std::is_same_v<typename TDanglingRange::traits_type, traits_type>)
		PUPPY_NODISCARD_CTOR
		constexpr explicit basic_string_view(TRange&& range)
		noexcept(noexcept(std::ranges::size(range)) && noexcept(std::ranges::data(range)))
			: _str{std::ranges::data(range)}, _size{std::ranges::size(range)}
		{}

		// nullptr_tを受け取るコンストラクタを削除
		basic_string_view(nullptr_t) = delete;

		// --- デストラクタ

		constexpr ~basic_string_view() noexcept = default;

		// --- コピーコンストラクタ / コピー代入演算子

		constexpr basic_string_view(const basic_string_view&) noexcept = default;
		constexpr basic_string_view& operator=(const basic_string_view&) noexcept = default;

		// --- ムーブコンストラクタ / ムーブ代入演算子

		constexpr basic_string_view(basic_string_view&&) noexcept = default;
		constexpr basic_string_view& operator=(basic_string_view&&) noexcept = default;

		// --- スワップ
		constexpr void swap(basic_string_view& sv) noexcept
		{
			auto temp = std::move(*this);
			*this = std::move(sv);
			sv = std::move(temp);
		}

		// --- ゲッターメソッド

		/// @brief 文字列の先頭を指すイテレータを返す
		/// @return 文字列の先頭を指すイテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_iterator begin() const noexcept
		{
			return _str;
		}

		/// @brief 文字列の末尾を指すイテレータを返す
		/// @return 文字列の末尾を指すイテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_iterator end() const noexcept
		{
			return _str + _size;
		}

		/// @brief 文字列の先頭を指すconstイテレータを返す
		/// @return 文字列の先頭を指すconstイテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_iterator cbegin() const noexcept
		{
			return _str;
		}

		/// @brief 文字列の末尾を指すconstイテレータを返す
		/// @return 文字列の末尾を指すconstイテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_iterator cend() const noexcept
		{
			return _str + _size;
		}

		/// @brief 文字列の末尾を指す逆イテレータを返す
		/// @return 文字列の末尾を指す逆イテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator{end()};
		}

		/// @brief 文字列の先頭を指す逆イテレータを返す
		/// @return 文字列の先頭を指す逆イテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator{begin()};
		}

		/// @brief 文字列の末尾を指すconst逆イテレータを返す
		/// @return 文字列の末尾を指すconst逆イテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_reverse_iterator crbegin() const noexcept
		{
			return const_reverse_iterator{end()};
		}

		/// @brief 文字列の先頭を指すconst逆イテレータを返す
		/// @return 文字列の先頭を指すconst逆イテレータ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_reverse_iterator crend() const noexcept
		{
			return const_reverse_iterator{begin()};
		}

		/// @brief 文字列の要素数を返す
		/// @return 文字列の要素数
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr size_type size() const noexcept
		{
			return _size;
		}

		/// @brief 文字列の最大長を返す
		/// @return 文字列の最大長
		/// @note この関数は、コンテナのインターフェースとの互換性を保つために存在する
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr size_type max_size() const noexcept
		{
			return (npos - sizeof(size_type) - sizeof(void*)) / sizeof(value_type) / 4;
		}

		/// @brief 文字列が空であるかを返す
		/// @return 文字列が空であるか
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr bool empty() const noexcept
		{
			return _size == 0;
		}

		// --- 要素アクセスメソッド

		/// @brief 任意の位置の文字を返す
		/// @param index 文字の位置
		/// @return 任意の位置の文字
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_reference operator[](size_type index) const noexcept
		{
			PUPPY_ASSERT(index < _size);
			return _str[index];
		}
		
//		[[nodiscard]]
//		constexpr const_reference at(size_type index) const
//		{
//			if (index >= _size)
//			{
//				throw std::out_of_range("basic_string_view::at");
//			}
//			return _str[index];
//		}

		/// @brief 文字列の先頭の文字を返す
		/// @return 文字列の先頭の文字
		[[nodiscard]]
		constexpr const_reference front() const noexcept
		{
			return _str[0];
		}

		/// @brief 文字列の末尾の文字を返す
		/// @return 文字列の末尾の文字
		[[nodiscard]]
		constexpr const_reference back() const noexcept
		{
			return _str[_size - 1];
		}

		/// @brief 文字列の先頭を指すポインタを返す
		/// @return 文字列の先頭を指すポインタ
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr const_pointer data() const noexcept
		{
			return _str;
		}

//		[[nodiscard]]
//		constexpr const_pointer c_str() const noexcept
//		{
//			return _str;
//		}

		/// @brief 文字列の先頭から指定した文字数を削除した文字列を返す
		/// @param pos 削除する文字列の先頭の位置
		/// @return 文字列の先頭から指定した文字数を削除した文字列
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr basic_string_view substr(size_type pos) const noexcept
		{
			PUPPY_ASSERT(pos <= _size);
			return {_str + pos, _size - pos};
		}

		/// @brief 文字列の先頭から指定した文字数を削除した文字列を返す
		/// @param pos 削除する文字列の先頭の位置
		/// @param count 残す文字数
		/// @return 文字列の先頭から指定した文字数を削除した文字列
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr basic_string_view
		substr(size_type pos, size_type count) const noexcept
		{
			PUPPY_ASSERT(pos + count <= _size);
			return {_str + pos, count};
		}

		// --- 操作メソッド

		/// @brief 文字列の先頭から指定した文字数を削除する
		/// @param count 削除する文字数
		PUPPY_FORCE_INLINE
		constexpr void remove_prefix(size_type count) noexcept
		{
			PUPPY_ASSERT(count <= _size);
			_str += count;
			_size -= count;
		}

		/// @brief 文字列の末尾から指定した文字数を削除する
		/// @param count 削除する文字数
		PUPPY_FORCE_INLINE
		constexpr void remove_suffix(size_type count) noexcept
		{
			PUPPY_ASSERT(count <= _size);
			_size -= count;
		}

		// --- 比較メソッド

		/// @brief 文字列同士を比較する
		/// @param sv 比較する文字列
		/// @return 比較結果 比較対象より大きければ1以上、小さければ1以下、同じであれば0
		[[nodiscard]]
		PUPPY_FORCE_INLINE
		constexpr int compare(basic_string_view sv) const noexcept
		{
			return compare(sv._str, sv._size);
		}

		/// @brief 文字列同士を比較する
		/// @param str 比較する文字列
		/// @return 比較結果 比較対象より大きければ1以上、小さければ1以下、同じであれば0
		[[nodiscard]]
		constexpr int compare(const value_type* str) const noexcept
		{
			PUPPY_ASSERT(str != nullptr);
			return compare(str, traits_type::length(str));
		}

		/// @brief 文字列同士を比較する
		/// @param str 比較対象の文字列
		/// @param size 比較対象の文字列長
		/// @return 比較結果 比較対象より大きければ1以上、小さければ1以下、同じであれば0
		[[nodiscard]]
		constexpr int
		compare(const value_type* str, size_type size) const noexcept
		{
			const auto min_len = std::min(_size, size);
			auto result = traits_type::compare(_str, str, min_len);
			if (result == 0) PUPPY_UNLIKELY
			{
				using limits = std::numeric_limits<int>;
				const difference_type diff = _size - size;
				result = diff < limits::min() ? limits::min()
				       : diff > limits::max() ? limits::max()
					   : static_cast<int>(diff);
			}
			return result;
		}
	private:
		// --- メンバ変数定義

		const value_type* _str;
		size_type _size;
	};

	// --- 三方比較演算子の定義
	template<typename TChar, typename TCharTraits>
	[[nodiscard]]
	PUPPY_FORCE_INLINE
	constexpr std::weak_ordering operator<=>(
		const basic_string_view<TChar, TCharTraits>& lhs,
		const basic_string_view<TChar, TCharTraits>& rhs) noexcept
	{
		return static_cast<std::weak_ordering>(lhs.compare(rhs));
	}

	// --- 導入子定義
	template<std::contiguous_iterator TItrator, std::sized_sentinel_for<TItrator> TEnd>
	basic_string_view(TItrator, TEnd) -> basic_string_view<std::iter_value_t<TItrator>>;

	template<std::ranges::contiguous_range TRange>
	basic_string_view(TRange&&)
		-> basic_string_view<std::ranges::range_value_t<TRange>>;

	// --- 型エイリアス定義
	using string_view = basic_string_view<char32_t>;

	// --- リテラル定義
	inline namespace literals
	{
		inline namespace string_view_literals
		{
			[[nodiscard]]
			inline constexpr
			string_view operator""_sv(const char32_t* str,
				const size_t size) noexcept
			{
				return {str, size};
			}
		}
	}
}

namespace std
{
	// --- std::swapの特殊化
	template<typename TChar, typename TCharTraits>
	void swap(puppy::basic_string_view<TChar, TCharTraits>& lhs,
		puppy::basic_string_view<TChar, TCharTraits>& rhs) noexcept
	{
		lhs.swap(rhs);
	}

	// --- std::hashの特殊化
	template<typename TChar, typename TCharTraits>
	struct hash<puppy::basic_string_view<TChar, TCharTraits>>
	{
		[[nodiscard]]
		size_t operator()(
			const puppy::basic_string_view<TChar, TCharTraits>& sv) const noexcept
		{
			return hash_range(sv.begin(), sv.end());
		}
	};
}


#endif // _PUPPY_STRING_VIEW_HPP
